#!/bin/bash

# Ensure MongoDB is running (requires sudo if not already started in background)
# mongod --fork --logpath /tmp/mongodb.log

# Compile the C++ server
echo "Compiling server..."
g++ project/main.cpp -o project/server $(pkg-config --cflags --libs libmongoc-1.0) -pthread

# Start the server
echo "Starting server on port 8080..."
cd project && ./server
