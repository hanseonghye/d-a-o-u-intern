#include 	<stdio.h>

extern struct Packet_Ack 		err_ack, ok_ack;

void setOkAck()
{
	memset(&ok_ack,0,sizeof(struct Packet_Ack));
  	sprintf(ok_ack.strlength,"%d",2);
  	strncpy(ok_ack.ack,"OK",2);
}

void setErrAck(){
	memset(&err_ack,0,sizeof(struct Packet_Ack));
	sprintf(err_ack.strlength,"%d",3);
	strncpy(err_ack.ack,"ERR",3);
}

void setAck()
{
	setOkAck();
	setErrAck();
}