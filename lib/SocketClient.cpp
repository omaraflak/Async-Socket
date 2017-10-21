#include "SocketClient.h"

SocketClient::SocketClient(std::string address, int port){
    m_address = address;
    m_port = port;

    m_server.sin_addr.s_addr = inet_addr(address.c_str());
    m_server.sin_family = AF_INET;
    m_server.sin_port = htons(port);

    m_disconnectListener = NULL;
    m_connected = false;
    m_threadStopped = false;
    m_packetSize = 4096;
}

SocketClient::SocketClient(int socket){
    m_socket = socket;
    m_disconnectListener = NULL;
    m_connected = true;
    m_threadStopped = false;
    m_packetSize = 4096;
    pthread_create(&m_thread, NULL, &staticReceiveThread, this);
}

int SocketClient::getSocket(){
    return m_socket;
}

bool SocketClient::connect(){
    m_socket = socket(AF_INET , SOCK_STREAM , 0);
    if(m_socket == -1)
    {
        return false;
    }

    if(::connect(m_socket, (struct sockaddr *)&m_server, sizeof(m_server)) < 0)
    {
        return false;
    }

    m_connected = true;
    pthread_create(&m_thread, NULL, &staticReceiveThread, this);

    return true;
}

void SocketClient::disconnect(){
    close(m_socket);
    m_connected = false;
    m_threadStopped = true;
}

bool SocketClient::send(std::string message){
    uint32_t length = htonl(message.size());
    if(::send(m_socket, &length, sizeof(length), 0) < 0){
        return false;
    }
    if(::send(m_socket, message.c_str(), message.size(), 0) < 0){
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

int SocketClient::receive(std::string &message){
    uint32_t length;
    int code;

    code = ::recv(m_socket, &length, sizeof(length), 0);
    if(code!=-1 && code!=0){
        length = ntohl(length);
        char server_reply[length];
        message = "";

        for(int i=0 ; i<length/m_packetSize ; i++){
            code = ::recv(m_socket, server_reply, m_packetSize, 0);
            if(code!=-1 && code!=0){
                message += std::string(server_reply, m_packetSize);
            }
            else{
                return code;
            }
        }
        if(length%m_packetSize!=0){
            char server_reply_rest[length%m_packetSize];
            code = ::recv(m_socket, server_reply_rest, length%m_packetSize, 0);
            if(code!=-1 && code!=0){
                message += std::string(server_reply_rest, length%m_packetSize);
            }
        }
        return code;
    }
    return code;
}

void SocketClient::addMessageListener(std::string key, void (*messageListener) (SocketClient *sender, std::vector<std::string> messages)){
    m_messageListenerMap[key] = messageListener;
}

void SocketClient::setDisconnectListener(void (*disconnectListener) (void)){
    m_disconnectListener = disconnectListener;
}

void* SocketClient::receiveThread(void*){
    std::string key;
    std::string message;
    int code1, code2;
    while (!m_threadStopped) {
        code1 = receive(key);
        code2 = receive(message);
        if(code1==0 || code2==0){
            m_connected = false;
            if(m_disconnectListener!=NULL){
                (*m_disconnectListener)();
            }
        }
        else if(code1!=-1 && code2!=-1){
            if(m_messageListenerMap[key]!=NULL){
                (*m_messageListenerMap[key])(this, stringToVector(message));
            }
        }
    }
}
