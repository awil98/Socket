#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>

#include <arpa/inet.h>//contains a method for converting network addresses

int main(int argc, char *argv[]){
	char *address;
	address = argv[1];

	int clientSocket;
	clientSocket = socket(AF_INET, SOCK_STREAM, 0);

	//connect to an address
	struct sockaddr_in remote_address;
	remote_address.sin_family = AF_INET;
	remote_address.sin_port = htons(80);//port 80 is the port that most web servers run on 
	inet_aton(address, &remote_address.sin_addr.s_addr);//converts string address from command line arg to format for address struct
	
	connect(clientSocket, (struct sockaddr *) &remote_address, sizeof(remote_address));

	char request[] = "GET / HTTP/1.0\r\n\r\n";
	char response[4096];

	send(clientSocket, request, sizeof(request), 0);

	recv(clientSocket, &response, sizeof(response), 0);

	printf("Response from the server: %s\n", response);


	return 0;
}
