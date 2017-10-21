#! /bin/sh

g++ client.cpp ../../lib/SocketClient.cpp -o client -lpthread
./client
