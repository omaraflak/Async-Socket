#ifndef DEF_SOCKETCLIENT
#define DEF_SOCKETCLIENT

#include <string>
#include <pthread.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <map>

#include "base64.h"
#include "dataInterface.h"

class SocketClient {
    private:
        void *mTag;
        DataInterface mDataInterface;

        struct sockaddr_in mServer;
        std::string mAddress;
        int mPort;
        int mSocket;
        bool mConnected;
        bool mThreadStopped;

        int mPacketSize;

        pthread_t mThread;
        std::map<std::string, void (*)(SocketClient*, std::vector<std::string>)> mMessageListenerMap;
        void (*mDisconnectListener) (SocketClient*);

        void receiveThread();
        static void staticReceiveThread(void* p){
            SocketClient *client = (SocketClient*) p;
            client->receiveThread();
        }
        int receive(std::string &message);
        bool send(std::string message);

    public:
        SocketClient();
        SocketClient(std::string address, int port);
        SocketClient(int socket);
        ~SocketClient();

        int getSocket();
        void* getTag();

        bool connect();
        void disconnect();
        bool send(std::string key, std::vector<std::string> messages);
        void addListener(std::string key, void (*messageListener) (SocketClient*, std::vector<std::string>));
        void setDisconnectListener(void (*disconnectListener) (SocketClient*));
        void setTag(void *tag, DataInterface interface);
};

#endif
