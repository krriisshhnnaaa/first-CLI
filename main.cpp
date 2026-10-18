#include <iostream>
#include "httplib.h"
#include "json.hpp"
#include <bson/bson.h>
#include <mongoc/mongoc.h>

using json = nlohmann::json;

int main() {
    mongoc_init();

    mongoc_uri_t *uri = mongoc_uri_new("mongodb://localhost:27017/");
    mongoc_client_pool_t *pool = mongoc_client_pool_new(uri);
    mongoc_uri_destroy(uri);

    httplib::Server svr;

    svr.set_mount_point("/", "./static");

    svr.Post("/submit", [pool](const httplib::Request &req, httplib::Response &res) {
        mongoc_client_t *client = mongoc_client_pool_pop(pool);
        mongoc_collection_t *collection = mongoc_client_get_collection(client, "testing", "comments");

        try {
            auto j = json::parse(req.body);
            std::string name = j.at("name").get<std::string>();
            std::string comment = j.at("comment").get<std::string>();

            bson_t *doc = bson_new();
            BSON_APPEND_UTF8(doc, "name", name.c_str());
            BSON_APPEND_UTF8(doc, "comment", comment.c_str());

            bson_error_t error;
            if (!mongoc_collection_insert_one(collection, doc, NULL, NULL, &error)) {
                std::cerr << "Insert failed: " << error.message << std::endl;
                json res_json = {{"status", "error"}, {"message", "Database error"}};
                res.set_content(res_json.dump(), "application/json");
            } else {
                json res_json = {{"status", "success"}, {"message", "Comment submitted!"}};
                res.set_content(res_json.dump(), "application/json");
            }

            bson_destroy(doc);
        } catch (const std::exception& e) {
            json res_json = {{"status", "error"}, {"message", "Invalid request"}};
            res.set_content(res_json.dump(), "application/json");
        }

        mongoc_collection_destroy(collection);
        mongoc_client_pool_push(pool, client);
    });

    std::cout << "Server starting on http://localhost:8080" << std::endl;
    svr.listen("0.0.0.0", 8080);

    mongoc_client_pool_destroy(pool);
    mongoc_cleanup();

    return 0;
}
