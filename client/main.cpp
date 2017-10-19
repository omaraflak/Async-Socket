#include <iostream>
#include "../lib/SocketClient.h"

using namespace std;

void onMessage(SocketClient *sender, std::string message){
    cout << "message : " << message << endl;
}

void onDisconnect(){
    cout << "you have been disconnected" << endl;
}

int main(int argc , char *argv[])
{
    SocketClient client("127.0.0.1", 8888);
    client.addMessageListener("message", onMessage);
    client.setDisconnectListener(onDisconnect);

    if(!client.connect()){
        cout << "could not connect to server" << endl;
        return 0;
    }
    cout << "connected to server." << endl;

    std::string line;
    while(1){
        cout << "input: ";
        getline(cin, line);
        if(!client.send("message", line)){
            cout << "failed to send message" << endl;
            return 0;
        }
    }
    return 0;
}