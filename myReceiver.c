#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <assert.h>

#define BUFSIZE 4096
#define FILENAME "dst.jpg"
#define ERR_PARAM 7

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

void rdtACK(int sock, Packet packet, int* indicator, int* receved_Size);
void toApp(Packet packet);
void sendACKwithLoss(int sock, int indicator);

void myReceiver(int sock)
{
	Packet rcvPkt;
	int idcRcv = 0;
	int rcvedSize = 0;

	while (1)
	{
		// read data transferred from client.
		assert(read(sock, &rcvPkt, sizeof(rcvPkt)));

		usleep(250000);

		printf("%i Bytes data (seq: %i, idc: %i) received\n",
				rcvPkt.dataSize, rcvPkt.dataSeq, rcvPkt.indicator);
		rdtACK(sock, rcvPkt, &idcRcv, &rcvedSize);

		// stop receiption if finish flag is set.
		if (rcvPkt.isFinish == true)
			break;
	}
	printf("The file (%i Bytes) has been received.\n", rcvedSize);
}


void rdtACK(int sock, Packet pkt, int* idc, int* rcvedSize)
{
	
	// indicator for that server is waiting == indicator from client
	if (*idc == pkt.indicator)
	{
		printf("Acceptable Data\n");
		usleep(250000);

		// send ACK with indicator.
		sendACKwithLoss(sock,*idc);

		// deliver data to app layer.
		toApp(pkt);
		
		*rcvedSize += pkt.dataSize;	// accumulate
		*idc = *idc == 1? 0 : 1;		// toggle idc
	}
	else	// different indicators
	{
		printf("Non-acceptable Data => Data will be thrown away.\n");
		usleep(250000);

		// send ACK with indicator
		sendACKwithLoss(sock, 1-*idc);
	}
}

void toApp(Packet pkt)
{
	static long int offset = 0;
	FILE* fp = NULL;

	if (0 == pkt.dataSeq)
		assert(fp = fopen(FILENAME, "w+"));
	else
		assert(fp = fopen(FILENAME, "a"));

	// copy file data.
	fseek(fp, offset, SEEK_SET);
	fwrite(pkt.data, pkt.dataSize, 1, fp);

	offset += pkt.dataSize;
	fclose(fp);
}

void sendACKwithLoss(int sock, int idc)
{
	Packet ACKPkt;
	// make intentional error
	int err_idc = rand() % ERR_PARAM;

	if (0 == err_idc)
		printf("ACK sent (LOSS)\n\n");
	else
	{
		printf("ACK sent (SUCCESS)\n\n");
		// send [ACK, indicator number] to client.
		strcpy(ACKPkt.data, "ACK");
		ACKPkt.indicator = idc;
		write(sock,&ACKPkt,sizeof(ACKPkt));                         // Use write(). 
	}
}
