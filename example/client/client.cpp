#include <iostream>
#include "../../lib/socketClient.h"

DataInterface INTERFACE([](void* data){
    delete (std::string*) data;
});

void onMessage(SocketClient *sender, std::vector<std::string> messages){
    for(unsigned int i=0 ; i<messages.size() ; i++){
        std::cout << "message[" << i << "] : " << messages[i] << std::endl;
    }
}

void onUid(SocketClient *sender, std::vector<std::string> messages){
    std::string uid = messages[0];
    sender->setTag(new std::string(uid), INTERFACE);
}

void onDisconnect(SocketClient *socket){
    std::string uid = *((std::string*)socket->getTag());
    std::cout << "you have been disconnected : [" << uid << "]" << std::endl;
}

int main(){
    SocketClient client("127.0.0.1", 8888);
    client.addListener("message", onMessage);
    client.addListener("uid", onUid);
    client.setDisconnectListener(onDisconnect);

    if(!client.connect()){
        std::cout << "could not connect to server" << std::endl;
        return 0;
    }
    std::cout << "connected to server." << std::endl;

    std::string line;
    while(1){
        std::cout << "input: ";
        getline(std::cin, line);
        if(!client.send("message", line)){
            std::cout << "failed to send message" << std::endl;
            return 0;
        }
    }

    client.disconnect();

    return 0;
}
