CC = g++
ODIR = obj
CXXFLAGS = -Wall -Wextra -std=c++11

all : $(ODIR) $(ODIR)/client.o $(ODIR)/server.o $(ODIR)/Base64.o $(ODIR)/SocketClient.o $(ODIR)/SocketServer.o

$(ODIR)/client.o : ./example/client/client.cpp ./lib/socketClient.h ./lib/base64.h
	$(CC) -c ./example/client/client.cpp -o $@ $(CXXFLAGS)

$(ODIR)/server.o : ./example/server/server.cpp ./example/server/Tools.h ./lib/socketClient.h ./lib/base64.h ./lib/socketServer.h
	$(CC) -c ./example/server/server.cpp -o $@ $(CXXFLAGS)

$(ODIR)/Base64.o : ./lib/Base64.cpp ./lib/base64.h
	$(CC) -c ./lib/Base64.cpp -o $@ $(CXXFLAGS)

$(ODIR)/SocketClient.o : ./lib/SocketClient.cpp ./lib/socketClient.h ./lib/base64.h
	$(CC) -c ./lib/SocketClient.cpp -o $@ $(CXXFLAGS)

$(ODIR)/SocketServer.o : ./lib/SocketServer.cpp ./lib/socketServer.h
	$(CC) -c ./lib/SocketServer.cpp -o $@ $(CXXFLAGS)

$(ODIR) :
	if [ ! -d $(ODIR) ]; then mkdir $(ODIR); fi

.PHONY : clean
clean :
	if [ -d $(ODIR) ]; then rm $(ODIR) -r; fi
