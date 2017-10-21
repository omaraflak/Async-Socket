#! /bin/sh

g++ server.cpp ../../lib/SocketServer.cpp  ../../lib/SocketClient.cpp -o server -lpthread
./server
