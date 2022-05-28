#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <fcntl.h>

#include <unistd.h>
#include <assert.h>

#ifndef boolean
#define boolean
typedef enum { false, true } bool;
#endif

void mySender(int sock);
bool askSending(const char* ip, const char* port);

void clientOpen(const char* ip, const char* port)
{
	// declare variables about socket
	int clnt_sock;
	struct sockaddr_in servAddr;

	// create the client-side socket (IPv4, TCP).
	assert(-1 != (clnt_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)));
	printf("Socket has been created.\n");

	usleep(500000);

	// set up address information of the server.
	memset((char*)&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = inet_addr(ip);
	servAddr.sin_port = htons(atoi(port));

	// request TCP connection.
	assert(-1 != connect(clnt_sock, (struct sockaddr*)&servAddr, sizeof(servAddr)));
	printf("TCP connection has been constructed.\n");

	// set socket status to nonblock mode.
	fcntl(clnt_sock, F_SETFL, O_NONBLOCK);

	assert(askSending(ip, port));
	printf("\n\n");

	srand(time(NULL));
	mySender(clnt_sock);

	// close the socket.
	close(clnt_sock);
}

bool askSending(const char* ip, const char* port)
{
	char c;

	// wait for starting to send file.
	printf("Send file to (%s:%s)? [Y/n] ", ip, port);

	do{
		c = getchar();
		while(getchar() != '\n');
		if (('n' == c) || ('N' == c))
			return false;
	} while(('y' != c) && ('Y' != c));

	return true;
}
