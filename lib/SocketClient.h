#ifndef DEF_SOCKETCLIENT
#define DEF_SOCKETCLIENT

#include <string>
#include <pthread.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <map>

class SocketClient {
    private:
        struct sockaddr_in m_server;
        std::string m_address;
        int m_port;
        int m_socket;
        bool m_connected;
        bool m_threadStopped;

        int m_packetSize;

        pthread_t m_thread;
        std::map<std::string, void (*)(SocketClient *sender, std::string message)> m_messageListenerMap;
        void (*m_disconnectListener) (void);

        void* receiveThread(void*);
        static void* staticReceiveThread(void* p){
            SocketClient *client = (SocketClient*) p;
            client->receiveThread(NULL);
        }
        int receive(std::string &message);
        bool send(std::string message);

    public:
        SocketClient(std::string address, int port);
        SocketClient(int socket);

        bool connect();
        void disconnect();
        bool send(std::string key, std::string message);
        void addMessageListener(std::string key, void (*messageListener) (SocketClient *sender, std::string message));
        void setDisconnectListener(void (*disconnectListener) (void));
};

#endif
