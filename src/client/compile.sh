#! /bin/sh

g++ client.cpp ../../lib/SocketClient.h ../../lib/SocketClient.cpp -o client -std=c++0x -pthread
./client
