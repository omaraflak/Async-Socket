#! /bin/sh

g++ client.cpp ../../lib/Base64.cpp ../../lib/SocketClient.cpp -o client -lpthread -std=c++11
./client
