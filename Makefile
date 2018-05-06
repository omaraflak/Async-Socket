CC = g++
ODIR = obj
CXXFLAGS = -Wall -Wextra -lpthread -std=c++11
CLIENT = client
SERVER = server

OBJS = $(ODIR)/utils.o $(ODIR)/base64.o $(ODIR)/socketClient.o $(ODIR)/socketServer.o
all : $(ODIR) $(OBJS) $(ODIR)/client.o $(ODIR)/server.o
	$(CC) -o $(SERVER) $(OBJS) $(ODIR)/server.o $(CXXFLAGS)
	$(CC) -o $(CLIENT) $(OBJS) $(ODIR)/client.o $(CXXFLAGS)

$(ODIR)/client.o : ./example/client/client.cpp ./lib/socketClient.h ./lib/base64.h ./lib/dataInterface.h
	$(CC) -c ./example/client/client.cpp -o $@ $(CXXFLAGS)

$(ODIR)/server.o : ./example/server/server.cpp ./example/server/utils.h ./lib/socketClient.h ./lib/base64.h ./lib/dataInterface.h ./lib/socketServer.h
	$(CC) -c ./example/server/server.cpp -o $@ $(CXXFLAGS)

$(ODIR)/utils.o : ./example/server/utils.cpp ./example/server/utils.h
	$(CC) -c ./example/server/utils.cpp -o $@ $(CXXFLAGS)

$(ODIR)/base64.o : ./lib/base64.cpp ./lib/base64.h
	$(CC) -c ./lib/base64.cpp -o $@ $(CXXFLAGS)

$(ODIR)/socketClient.o : ./lib/socketClient.cpp ./lib/socketClient.h ./lib/base64.h ./lib/dataInterface.h
	$(CC) -c ./lib/socketClient.cpp -o $@ $(CXXFLAGS)

$(ODIR)/socketServer.o : ./lib/socketServer.cpp ./lib/socketServer.h
	$(CC) -c ./lib/socketServer.cpp -o $@ $(CXXFLAGS)

$(ODIR) :
	if [ ! -d $(ODIR) ]; then mkdir $(ODIR); fi

.PHONY : clean
clean :
	if [ -d $(ODIR) ]; then rm $(ODIR) -r; fi
	if [ -f $(CLIENT) ]; then rm $(CLIENT); fi
	if [ -f $(SERVER) ]; then rm $(SERVER); fi
