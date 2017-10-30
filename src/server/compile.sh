#! /bin/sh

g++ server.cpp -o server Tools.h -I ../../lib/ ../../lib/*.cpp -lpthread -std=c++11
./server
