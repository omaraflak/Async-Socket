#include <iostream>

#include "../../lib/SocketClient.h"
#include "../../lib/SocketServer.h"

using namespace std;

void onMessage(SocketClient *socket, vector<string> messages){
	for(int i=0 ; i<messages.size() ; i++){
		cout << "message[" << i << "] : " << messages[i] << endl;
	}
	socket->send("message", messages);
}

void onDisconnect(SocketClient *socket){
	cout << "client disconnected!" << endl;
}

int main(int argc , char *argv[]){
	SocketServer server(8888);
	if(server.start()){
		cout << "server started. Listening on port 8888..." << endl;
		int sock = server.accept();
		if(sock!=-1){
			cout << "client connected !" << endl << endl;
			SocketClient client(sock);
			client.addListener("message", onMessage);
			client.setDisconnectListener(onDisconnect);
		}
		while (1) {
			/* loop code */
		}
	}
	else{
		cout << "Could not create server" << endl;
	}
	return 0;
}
