#include <iostream>

#include "../../lib/SocketClient.h"
#include "../../lib/SocketServer.h"

using namespace std;

void onMessage(SocketClient *socket, std::string message){
	cout << "client : " << message << endl;
	socket->send("message", message);
}

int main(int argc , char *argv[]){
	SocketServer server(8888);
	if(server.start()){
		cout << "server started. Listening on port 8888..." << endl;
		int sock = server.accept();
		if(sock!=-1){
			cout << "client connected !" << endl << endl;
			SocketClient client(sock);
			client.addMessageListener("message", onMessage);
		}
		while (1) {
			/* loop code */
		}
	}
	return 0;
}
