#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>


int main(){
	//create a socket
	int networkSocket;
	networkSocket = socket(AF_INET, SOCK_STREAM, 0);
	//specifiy an address for thhe socket
	struct sockaddr_in server_address;//this is for the server address
	server_address.sin_family = AF_INET;//this defines the address domain
	server_address.sin_port = htons(9002);//this specifies the port to connect to remotely
	server_address.sin_addr.s_addr = INADDR_ANY;//this specifies the ip address to connect to were using this address because it's on our computer
	//it's also worth knowning that this is random?
	int connection = connect(networkSocket, (struct sockaddr*) &server_address, sizeof(server_address));
	if(connection == -1){
		printf("Something went wrong in the connection");

	}
	char buffer[256];
	//recieve data from the server pars: socket, address for data, size of data optional flag
	recv(networkSocket, &buffer, sizeof(buffer), 0);
	//print out the server's response
	printf("The server sent the data: %s\n", buffer);
	//now close the socket
	close(networkSocket);
	return 0;
}
