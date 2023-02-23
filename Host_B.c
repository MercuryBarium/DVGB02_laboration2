#include "Sim_Engine.h"
#include "common.h"


int lastSeq = -1;

/* Called from layer 5, passed the data to be sent to other side */
void B_output( struct msg message) {
  /* DON'T IMPLEMENT */
}

/* Called from layer 3, when a packet arrives for layer 4 */
void B_input(struct pkt packet) {
  /* TODO */
  if (IsCorruptB(&packet))
  {
    packet.acknum = 0;
    tolayer3(B_f, packet);
  } 
  else 
  {
    packet.acknum = 1;
    if (packet.seqnum > lastSeq)
    {
      lastSeq = packet.seqnum;
      printf("\e[1;32mB: PACKET ACCEPTED -> APP/5\e[0m\n");
      tolayer5(B_f, packet.payload);
    }
    tolayer3(B_f, packet);
  }

}

/* Called when B's timer goes off */
void B_timerinterrupt() {
  /* TODO */
}  

/* The following routine will be called once (only) before any other */
/* Host B routines are called. You can use it to do any initialization */
void B_init() {
  printf("\e[4;33m____INIT__B____\e[0m\n");
}
