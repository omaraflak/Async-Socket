#! /bin/sh

g++ main.cpp ../lib/SocketServer.h ../lib/SocketServer.cpp ../lib/SocketClient.h ../lib/SocketClient.cpp -o main -std=c++0x -pthread
./main
rm main
