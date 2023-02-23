#include <stdio.h>
#include <string.h>
#include "Sim_Engine.h"
#include "common.h"

struct pkt paketz[BUFFER_SIZE];
int seq = 0;
int pos = 0;

int in_convo = 0;

void append(struct msg message)
{
  if (pos < BUFFER_SIZE)
  {
    memcpy(paketz[pos].payload, message.data, BUFFER_SIZE);
    paketz[pos].acknum = 0;
    paketz[pos].seqnum = seq++;
    paketz[pos].checksum = checksum(&paketz[pos]);
    pos++;
  }
}

/* Called from layer 5, passed the data to be sent to other side */
void A_output(struct msg message)
{
  append(message);
  if (!in_convo)
  {
    printf("\e[1;33mSending Packet, SEQ: %d\e[0m\n", paketz[0].seqnum);
    printPacket(&paketz[0], 'A');
    starttimer(A_f, INCREMENT);
    tolayer3(A_f, paketz[0]);
    in_convo = 1;
  }
}


/* Called from layer 3, when a packet arrives for layer 4 */
void A_input(struct pkt packet)
{
  stoptimer(A_f);
  if (packet.acknum == 1 && packet.seqnum == paketz[0].seqnum)
  {
    printf("\e[1;32mACK -> Transmission Successful.\e[0m\n");
    for (int i = 1; i < BUFFER_SIZE; i++)
      memcpy(&paketz[i-1], &paketz[i], sizeof(struct pkt));
    pos--;
    in_convo = 0;
    if (pos)
    {
      printf("Left in Queue: %d\nNext:\n", pos);
      printPacket(&paketz[0], 'A');
      in_convo = 1;
      starttimer(A_f, INCREMENT);
      tolayer3(A_f, paketz[0]);
    }
  }
  else
  {  
    //printf("\e[1;31mNAK -> RESENDING SEQ: %d\e[0m\n", paketz[0].seqnum);
    starttimer(A_f, INCREMENT);
    tolayer3(A_f, paketz[0]);
  }
}

/* Called when A's timer goes off */
void A_timerinterrupt()
{
  //stoptimer(A_f);
  starttimer(A_f, INCREMENT);
  tolayer3(A_f, paketz[0]);
}

/* The following routine will be called once (only) before any other */
/* Host A routines are called. You can use it to do any initialization */
void A_init()
{
  printf("\e[4;33m____INIT__A____\e[0m\n");
}
