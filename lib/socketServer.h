#ifndef DEF_SERVER
#define DEF_SERVER

#include <sys/socket.h>
#include <arpa/inet.h>

class SocketServer {
    private:
        int mPort;
        int mSocket;
        struct sockaddr_in mServer;

    public:
        SocketServer(int port);
        bool start();
        int accept();
};
#endif
