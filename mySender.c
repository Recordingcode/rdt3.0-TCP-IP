#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <assert.h>

#define BUFSIZE 4096
#define FILENAME "src.jpg"
#define ERR_PARAM 7
#define TIMEOUT 10000000

#ifndef boolean
#define boolean
typedef enum { false, true } bool;
#endif

typedef struct packet {
	char data[BUFSIZE];
	int dataSize;
	int dataSeq;
	int indicator;
	bool isFinish;
} Packet;

void rdtSend(int sock, Packet packet);
bool isACK(int sock, int indicator);
void udtSend(int sock, Packet packet);

void mySender(int sock)
{
	FILE* fp = NULL;
	size_t fSize;

	Packet sndPkt;
	int sentSize = 0;

	// designate as the file pointer the file to be read.
	assert(fp = fopen(FILENAME, "r"));

	// figure out the size of the file.
	fseek(fp, 0, SEEK_END);
	fSize = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	// initialize sndPkt.
	sndPkt.dataSeq = 0;
	sndPkt.indicator = 0;
	sndPkt.isFinish = false;
	
	// send the file to the server.
	while (    fsize > 0    )
	{
		// less than or equal to maximum length (BUFSIZE)
		sndPkt.dataSize = fsize > BUFSIZE ? BUFSIZE : fsize;

		// if packet to send is last one, set flag of finish.
		sndPkt.isFinish = fsize > BUFSIZE ? false : true;

		// read data from file to packet data.
		fread(sndPkt.data, sndPkt.dataSize, 1, fp);

		// send packet by reliable data transmission.
		rdtSend(sock, sndPkt);

		fSize -= sndPkt.dataSize;
		sentSize += sndPkt.dataSize;
		sndPkt.dataSeq ++;
		sndPkt.indicator = sndPkt.indicator == 1 ? 0 : 1;
		usleep(500000);
	}

	printf("The file (%i Bytes) has been sent.\n", sentSize);
	fclose(fp);
}

void rdtSend(int sock, Packet pkt)
{
	udtSend(sock, pkt);

	// retramsmit packet when Timeout occurs
	while(    isACK(sock,pkt.indicator) == false    )
	{
		printf("TIMEOUT => resent ");
		udtSend(sock,pkt);
	}

	usleep(500000);
	printf("ACK received\n\n");
}

bool isACK(int sock, int idc)
{
	int timer_count = 0;
	Packet ACK;
	memset(&ACK, -1, sizeof(ACK));

	// timer loop
	while (timer_count++ < TIMEOUT)
	{
		
		if(read(sock,&ACK,sizeof(ACK))!=-1)  //Use read()
              if(idc == ACK.indicator)
		         return true;
	}

	return false;
}

void udtSend(int sock, Packet pkt)
{
	// make intentional error
	int err_idc = rand() % ERR_PARAM;

	if (0 == err_idc)	// error occurs (the probability of the packet loss is 1/7)
	{
		printf("%i Bytes data (seq: %i, idc: %i) sent (LOSS)\n",
				pkt.dataSize, pkt.dataSeq, pkt.indicator);
	}
	else
	{
		write(sock,&pkt,sizeof(pkt));             //Use write()
		printf("%i Bytes data (seq: %i, idc: %i) sent (SUCCESS)\n",
				pkt.dataSize, pkt.dataSeq, pkt.indicator);
	}
}
