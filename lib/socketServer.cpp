#include "socketServer.h"

SocketServer::SocketServer(int port){
    m_port = port;

    m_server.sin_family = AF_INET;
    m_server.sin_addr.s_addr = INADDR_ANY;
    m_server.sin_port = htons(port);
}

bool SocketServer::start(){
    m_socket = ::socket(AF_INET , SOCK_STREAM , 0);
    if(m_socket!=-1){
        if(::bind(m_socket,(struct sockaddr *)&m_server , sizeof(m_server)) >= 0){
            ::listen(m_socket, 3);
            return true;
    	}
    }
    return false;
}

int SocketServer::accept(){
    int c = sizeof(struct sockaddr_in);
    struct sockaddr_in client;

	int client_sock = ::accept(m_socket, (struct sockaddr *)&client, (socklen_t*)&c);
	if (client_sock < 0){
        return -1;
	}
    return client_sock;
}
