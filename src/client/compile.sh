#! /bin/sh

g++ client.cpp -o client -I ../../lib/ ../../lib/*.cpp -lpthread -std=c++11
./client
