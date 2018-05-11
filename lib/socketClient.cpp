#include "socketClient.h"

SocketClient::SocketClient(){}

SocketClient::SocketClient(std::string address, int port){
    mAddress = address;
    mPort = port;

    mServer.sin_addr.s_addr = inet_addr(address.c_str());
    mServer.sin_family = AF_INET;
    mServer.sin_port = htons(port);

    mTag = NULL;
    mDisconnectListener = NULL;
    mConnected = false;
    mThreadStopped = false;
    mPacketSize = 4096;
}

SocketClient::SocketClient(int socket){
    mSocket = socket;
    mTag = NULL;
    mDisconnectListener = NULL;
    mConnected = true;
    mThreadStopped = false;
    mPacketSize = 4096;
    pthread_create(&mThread, NULL, &staticReceiveThread, this);
}

SocketClient::~SocketClient(){
    if(mTag!=NULL && mDataInterface.mDestroy){
        mDataInterface.mDestroy(mTag);
    }
}

int SocketClient::getSocket(){
    return mSocket;
}

bool SocketClient::connect(){
    mSocket = socket(AF_INET , SOCK_STREAM , 0);
    if(mSocket == -1)
    {
        return false;
    }

    if(::connect(mSocket, (struct sockaddr *)&mServer, sizeof(mServer)) < 0)
    {
        return false;
    }

    mConnected = true;
    pthread_create(&mThread, NULL, &staticReceiveThread, this);

    return true;
}

void SocketClient::disconnect(){
    close(mSocket);
    mConnected = false;
    mThreadStopped = true;
}

bool SocketClient::send(std::string message){
    uint32_t length = htonl(message.size());
    if(::send(mSocket, &length, sizeof(uint32_t), 0) < 0){
        return false;
    }
    if(::send(mSocket, message.c_str(), message.size(), 0) < 0){
        return false;
    }
    return true;
}

bool SocketClient::send(std::string key, std::vector<std::string> messages){
    if(send(key)){
        return send(vectorToString(messages));
    }
    return false;
}

bool SocketClient::send(std::string key, std::string message){
    std::vector<std::string> msg = {message};
    return send(key, msg);
}

int SocketClient::receive(std::string &message){
    uint32_t length;
    int code;

    code = ::recv(mSocket, &length, sizeof(uint32_t), 0);
    if(code!=-1 && code!=0){
        length = ntohl(length);
        char server_reply[length];
        message = "";

        int q = length/mPacketSize;
        int r = length%mPacketSize;

        for(int i=0 ; i<q ; i++){
            code = ::recv(mSocket, server_reply, mPacketSize, 0);
            if(code!=-1 && code!=0){
                message += std::string(server_reply, mPacketSize);
            }
            else{
                return code;
            }
        }
        if(r!=0){
            char server_reply_rest[r];
            code = ::recv(mSocket, server_reply_rest, r, 0);
            if(code!=-1 && code!=0){
                message += std::string(server_reply_rest, r);
            }
        }
    }
    return code;
}

void SocketClient::addListener(std::string key, void (*messageListener) (SocketClient*, std::vector<std::string>)){
    mMessageListenerMap[key] = messageListener;
}

void SocketClient::setDisconnectListener(void (*disconnectListener) (SocketClient*)){
    mDisconnectListener = disconnectListener;
}

void SocketClient::setTag(void *tag, DataInterface interface){
    mTag = tag;
    mDataInterface = interface;
}

void* SocketClient::getTag(){
    return mTag;
}

void SocketClient::receiveThread(){
    std::string key, message;
    int code1, code2;
    while (!mThreadStopped) {
        code1 = receive(key);
        code2 = receive(message);
        if(code1==0 || code2==0){
            disconnect();
            if(mDisconnectListener!=NULL){
                (*mDisconnectListener)(this);
            }
        }
        else if(code1!=-1 && code2!=-1){
            if(mMessageListenerMap[key]!=NULL){
                (*mMessageListenerMap[key])(this, stringToVector(message));
            }
        }
    }
}
