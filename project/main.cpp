#include <iostream>
#include <mongoc/mongoc.h>
#include <bson/bson.h>
#include "httplib.h"
#include "json.hpp"

using namespace httplib;
using json = nlohmann::json;

void insert_document(mongoc_collection_t *collection, const std::string& name, const std::string& content) {
    bson_error_t error;
    bson_t *doc = bson_new();

    BSON_APPEND_UTF8(doc, "name", name.c_str());
    BSON_APPEND_UTF8(doc, "content", content.c_str());

    if (!mongoc_collection_insert_one(collection, doc, NULL, NULL, &error)) {
        std::cerr << "Error inserting document: " << error.message << std::endl;
    } else {
        std::cout << "Document inserted successfully!" << std::endl;
    }

    bson_destroy(doc);
}

int main(int argc, char *argv[]) {
    // Initialize MongoDB
    mongoc_init();

    // Set up MongoDB client
    mongoc_client_t *client = mongoc_client_new("mongodb://localhost:27017/?appname=testing");
    if (!client) {
        std::cerr << "Failed to parse MongoDB URI." << std::endl;
        return EXIT_FAILURE;
    }

    mongoc_database_t *database = mongoc_client_get_database(client, "testing");
    mongoc_collection_t *collection = mongoc_client_get_collection(client, "testing", "submissions");

    // Initialize HTTP server
    Server svr;

    // Serve static files
    auto ret = svr.set_mount_point("/", "./");
    if (!ret) {
        std::cerr << "Failed to mount base directory" << std::endl;
    }

    // Default route serving index.html
    svr.Get("/", [](const Request& req, Response& res) {
        res.set_redirect("/index.html");
    });

    // API endpoint to handle form submission
    svr.Post("/submit", [collection](const Request& req, Response& res) {
        try {
            auto j = json::parse(req.body);
            std::string name = j["name"];
            std::string content = j["content"];

            insert_document(collection, name, content);

            json response_json = {
                {"status", "success"},
                {"message", "Data saved successfully to MongoDB!"}
            };
            res.set_content(response_json.dump(), "application/json");

        } catch (const json::parse_error& e) {
            json error_json = {
                {"status", "error"},
                {"message", "Invalid JSON data"}
            };
            res.status = 400;
            res.set_content(error_json.dump(), "application/json");
        }
    });

    std::cout << "Server starting at http://localhost:8080/" << std::endl;

    svr.listen("localhost", 8080);

    // Cleanup MongoDB resources (unreachable in infinite listen loop, but good practice)
    mongoc_collection_destroy(collection);
    mongoc_database_destroy(database);
    mongoc_client_destroy(client);
    mongoc_cleanup();

    return 0;
}
