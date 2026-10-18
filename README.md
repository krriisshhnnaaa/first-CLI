# C++ / MongoDB / HTML / JS Small Website

This is a small website stack that contains:
- HTML / JS (Frontend form)
- C++ (Backend server using `cpp-httplib` and `nlohmann/json`)
- MongoDB (Database via `libmongoc`)

## Prerequisites

On Ubuntu, you need to install the following dependencies:
```bash
sudo apt-get update
sudo apt-get install -y cmake make g++ libmongoc-1.0-0t64 libmongoc-dev libbson-dev pkg-config
```

You also need MongoDB running locally:
```bash
# Example to run MongoDB in background
sudo mkdir -p /data/db
sudo chown -R $(whoami) /data/db
mongod --fork --logpath /tmp/mongodb.log
```

## Running the Application

To run the application, simply execute the `run.sh` script:

```bash
./run.sh
```

Then visit `http://localhost:8080/` in your browser. When you submit the form, it will store the `name` and `content` into the MongoDB `testing` database, inside the `submissions` collection.
