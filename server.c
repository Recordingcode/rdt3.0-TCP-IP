#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/socket.h>
#include <arpa/inet.h>

#include <unistd.h>
#include <assert.h>

void myReceiver(int sock);

void serverOpen(const char* port)
{
	// declare variables about socket.
	int serv_sock, clnt_sock;
	struct sockaddr_in servAddr, clntAddr;
	socklen_t clntAddrSize;

	// create the server-side socket (IPv4, TCP).
	assert(-1 != (serv_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)));
	printf("Socket has been created.\n");

	usleep(500000);

	// set up address information of the server.
	memset((char*)&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAddr.sin_port = htons(atoi(port));

	// bind address information (port).
	assert(-1 != bind(serv_sock, (struct sockaddr*)&servAddr, sizeof(servAddr)));
	printf("The server address information (ANYIP:%s) is bound.\n", port);

	usleep(500000);

	// create the listen queue for incoming TCP connection.
	assert(-1 != listen(serv_sock, 5));
	printf("The listen queue has been created.\n");
	printf("Ready to receive TCP connection request.\n");

	usleep(500000);

	// accept a client requesting TCP connection.
	clntAddrSize = sizeof(clntAddr);
	assert(-1 != (clnt_sock = accept(serv_sock, (struct sockaddr*)&clntAddr, &clntAddrSize)));
	printf("a client (%s:%i) has been connected...\n\n\n",
			inet_ntoa(clntAddr.sin_addr), ntohs(clntAddr.sin_port));

	myReceiver(clnt_sock);

	// close sockets.
	close(clnt_sock);
	close(serv_sock);
}
