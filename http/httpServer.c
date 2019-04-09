#include <stdlib.h>
#include <stdio.h>

#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int main(){
	//Just open the file and store the data in a string
	FILE *htmlData;
	htmlData = fopen("index.html", "r");

	char responseData[1024];
	fgets(responseData, 1024, htmlData);
	
	//create the response
	char httpHeader[2048] = "HTTP/1.1 200 OK\r\n\n";
	strcat(httpHeader, responseData);//Has header and index.html file as one string

	//create a server socket
	int serverSocket;
	serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	//define the address
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(8001);
	server_address.sin_addr.s_addr = INADDR_ANY;

	bind(serverSocket, (struct sockaddr *) &server_address, sizeof(server_address));
	
	listen(serverSocket, 5);

	int clientSocket;//placeholder for the client socket

	while(1){
		clientSocket = accept(serverSocket, NULL, NULL);
		send(clientSocket, httpHeader, sizeof(httpHeader), 0);
		

	}

	return 0;
}
