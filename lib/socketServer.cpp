#include "socketServer.h"

SocketServer::SocketServer(int port){
    mPort = port;

    mServer.sin_family = AF_INET;
    mServer.sin_addr.s_addr = INADDR_ANY;
    mServer.sin_port = htons(port);
}

bool SocketServer::start(){
    mSocket = ::socket(AF_INET , SOCK_STREAM , 0);
    if(mSocket!=-1){
        if(::bind(mSocket,(struct sockaddr *)&mServer , sizeof(mServer)) >= 0){
            ::listen(mSocket, 3);
            return true;
    	}
    }
    return false;
}

int SocketServer::accept(){
    int c = sizeof(struct sockaddr_in);
    struct sockaddr_in client;

	int client_sock = ::accept(mSocket, (struct sockaddr *)&client, (socklen_t*)&c);
	if (client_sock < 0){
        return -1;
	}
    return client_sock;
}
