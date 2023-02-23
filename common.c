#include "Sim_Engine.h"
#include "common.h"

int checksum(struct pkt *p)
{
  int sum = 0;
  for (int i = 0; i < BUFFER_SIZE; i++)
    sum += (int)(p->payload[i]);
  return sum + p->acknum + p->seqnum;
}

void printPacket(struct pkt *p, char AorB)
{
	printf(
		"\e[0;93m::::PACKET_%c::::\n\tSEQ: %d\n\tACK: %d\n\tCHECKSUM: %d\n\tDATA: %.*s\n::::::::::::::::\e[0m\n",
		AorB,
		p->seqnum, 
		p->acknum, 
		p->checksum, 
		BUFFER_SIZE, p->payload
	);

}

int IsCorruptB(struct pkt *packet)
{
	// Kolla om checksum stämmer
	int sum = checksum(packet);
	//printf("\e[1;33mB: Checking checksums:\t%d\t,\t%d\e[0m\n", packet->checksum, sum);
	if (packet->checksum == sum)
		return 0;
	else
		return 1;
}