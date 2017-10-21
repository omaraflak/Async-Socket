#! /bin/sh
g++ -c SocketClient.cpp SocketServer.cpp
ar rvs libSocket.a SocketClient.o SocketServer.o
rm SocketClient.o SocketServer.o
