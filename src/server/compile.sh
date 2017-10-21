#! /bin/sh

g++ server.cpp ../../lib/Base64.cpp ../../lib/SocketServer.cpp  ../../lib/SocketClient.cpp -o server -lpthread
./server
