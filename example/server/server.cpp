#include <iostream>
#include <vector>

#include "utils.h"
#include "../../lib/socketClient.h"
#include "../../lib/socketServer.h"

std::vector<SocketClient*> clientsVector;

void forward(std::string key, std::vector<std::string> messages, SocketClient *exception){
	std::string *_uid = (std::string*) exception->getTag();
	for(auto x : clientsVector){
		std::string *uid = (std::string*) x->getTag();
		if((*uid)!=(*_uid)){
			x->send(key, messages);
		}
	}
}

void onMessage(SocketClient *socket, std::vector<std::string> messages){
	forward("message", messages, socket);
}

void onDisconnect(SocketClient *socket){
	std::cout << "client disconnected !" << std::endl;
	forward("message", {"Client disconnected"}, socket);
	std::string *_uid = (std::string*) socket->getTag();
	for(unsigned int i=0 ; i<clientsVector.size() ; i++){
		std::string *uid = (std::string*) clientsVector[i]->getTag();
		if((*uid)==(*_uid)){
			clientsVector.erase(clientsVector.begin() + i);
		}
	}
	delete socket;
}

void freeMemory(){
	for(auto x : clientsVector){
		delete x;
	}
}

int main(){
	DataInterface interface([](void* data){
		delete (std::string*) data;
	});

	SocketServer server(8888);
	if(server.start()){
		std::cout << "server started. Listening on port 8888..." << std::endl;
		while (1) {
			int sock = server.accept();
			if(sock!=-1){
				std::cout << "client connected !" << std::endl;
				std::string uid = getUid();
				SocketClient *client = new SocketClient(sock);
				client->addListener("message", onMessage);
				client->setDisconnectListener(onDisconnect);
				client->setTag(new std::string(uid), interface);
				client->send("uid", uid);
				clientsVector.push_back(client);
			}
		}
	}
	else{
		std::cout << "Could not create server" << std::endl;
	}

	freeMemory();
	return 0;
}
