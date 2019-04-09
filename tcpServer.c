#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/socket.h>
#include <sys/types.h>

#include <netinet/in.h>

int main(){
	char serverMSG[256] = "You have reached the server!";
	int serverSocket;
	serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(9002);//has to be the exact same
	server_address.sin_addr.s_addr = INADDR_ANY;

	//bind the socket to our specificed IP and port
	bind(serverSocket, (struct sockaddr*) &server_address, sizeof(server_address));
	
	listen(serverSocket, 5);//number of sockets that can be waiting for this server
	
	int clientSocket;
	
	clientSocket = accept(serverSocket, NULL, NULL);

	send(clientSocket, serverMSG, sizeof(serverMSG), 0);//socket being sent to, whats being sent, size of sent data, optional parameter
	
	close(serverSocket);	
	return 0;
}
