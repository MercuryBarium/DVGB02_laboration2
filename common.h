#ifndef COMMON_H
#define COMMON_H
#define BUFFER_SIZE 20
#define INCREMENT 35
int checksum(struct pkt *p);
void printPacket(struct pkt* p, char AorB);
enum fusk
{
	A_f,
	B_f
};
int IsCorruptB(struct pkt *packet);
#endif