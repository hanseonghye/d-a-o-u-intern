#include 	<sys/types.h>
#include 	<sys/socket.h>
#include 	<netinet/in.h>
#include 	<arpa/inet.h>
#include 	<sys/select.h>
#include 	<sys/time.h>
#include	<unistd.h>
#include	<errno.h>

#include    <stdlib.h>
#include    <string.h>
#include    <strings.h>

#define		PORT		12314
#define		IP			"192.168.103.10"
#define		MSG_END		"END"
#define		MAX_USER	2
#define		MAX_LEN		100

#define		PACKET_SIZE	(MAX_LEN+12)

struct 		Packet{
	char	serialNo [8];
	char	strlength  [4];
	char	record [MAX_LEN];
};

struct 		Packet_Ack
{
	char	strlength [4];
	char	ack [4];
};

void	log_msg (char* msg);
int		tcpBind (int p_std, int p_port);
int		tcpAccept (int p_std);
int 	tcpSocket ();
int 	tcpListen ( int p_std, int maxUser);
int 	tcpSetting (int p_std, int port, int maxUser);
void	tcpCloseClient (int iout);
void 	tcpReadWrite (struct Packet *spacket);
void	tcpCheckWrite (char serialNo[8], char textLen[4], char record[MAX_LEN], int iCnt);
void 	setAck();
void 	setErrAck();
void 	setOkAck();

struct 	Packet_Ack         err_ack, ok_ack;
int                istart, icheck;
int                icSock[MAX_USER];
FILE 			   *fwp;
unsigned int       iAllCnt;
fd_set             fdRead;