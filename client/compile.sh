#! /bin/sh

g++ main.cpp ../lib/SocketClient.h ../lib/SocketClient.cpp -o main -std=c++0x -pthread
./main
rm main
