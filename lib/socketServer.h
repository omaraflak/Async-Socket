#ifndef DEF_SERVER
#define DEF_SERVER

#include <sys/socket.h>
#include <arpa/inet.h>

class SocketServer {
    private:
        int m_port;
        int m_socket;
        struct sockaddr_in m_server;

    public:
        SocketServer(int port);
        bool start();
        int accept();
};
#endif
