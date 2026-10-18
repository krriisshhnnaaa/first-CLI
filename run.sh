#!/bin/bash
g++ main.cpp -o server -std=c++11 $(pkg-config --cflags --libs libmongoc-1.0)
./server
