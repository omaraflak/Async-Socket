#! /bin/sh

g++ server.cpp ../../lib/SocketServer.h ../../lib/SocketServer.cpp ../../lib/SocketClient.h ../../lib/SocketClient.cpp -o server -std=c++0x -pthread
./server
