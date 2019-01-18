#include 	<stdio.h>

extern struct Packet_Ack 		err_ack, ok_ack;
extern int 				istart, icheck;
extern int 				icSock[MAX_USER];
extern unsigned int 	iAllCnt;
extern fd_set 			fdRead;


void	log_msg (char* msg){
	FILE* fp;
	fp = fopen ("logfile.log", "a+");
	fprintf (fp, "%s", msg);
	fclose (fp);
}

// int	tcpBind (int p_std, int p_port)
// {
// 	int		rt;
// 	struct sockaddr_in sock_addr;
	
// 	bzero (&sock_addr, sizeof (sock_addr));
// 	sock_addr.sin_family = AF_INET;
// 	sock_addr.sin_addr.s_addr = inet_addr(IP);
// 	sock_addr.sin_port = htons (p_port);

// 	rt = bind (p_std, (struct sockaddr *)&sock_addr, sizeof (sock_addr));

// 	return (rt);
// }

// int	tcpAccept(int p_std)
// {
// 	int 				rt;
// 	struct 	sockaddr_in sock_addr;
// 	socklen_t 			addr_len;
// 	char				*host_p, *ip;
// 	struct hostent		*hp;

// 	addr_len = sizeof (struct sockaddr);
// 	memset ((char *)&sock_addr, 0, sizeof (sock_addr));

// 	rt = accept (p_std, (struct sockaddr *)&sock_addr, &addr_len);
// 	if (rt<0){
// 		log_msg("accept err\n");
// 		return rt;
// 	}

// 	log_msg("Incoming Client\n");
// 	log_msg("Client IP : ");
// 	log_msg(inet_ntoa(sock_addr.sin_addr));      //사용자가 접속하면 IP를 출력시켜준다.
// 	log_msg("\n");

// 	return rt;
// }



// int tcpSocket()
// {
// 	int 	rt;
// 	rt = socket (AF_INET, SOCK_STREAM, 0);

// 	return (rt);
// }

// int tcpListen( int p_std, int maxUser)
// {
// 	int 	rt;
// 	rt = listen (p_std, maxUser);
// 	return (rt);
// }

// int tcpSetting(int p_std, int port, int maxUser)
// {
// 	int 	rt;
// 	rt = tcpBind(p_std, port);

// 	if (rt < 0)
// 	{
// 		log_msg("bind err\n");
// 		return 0;
// 	}

// 	rt = tcpListen (p_std, maxUser);

// 	if (rt != 0)
// 	{
// 		log_msg ("listen err\n");
// 		return 0;
// 	}

// 	return 1;
// }

void	tcpCloseClient (int iout)
{
	--iAllCnt;
	icSock[iout] = icSock[iAllCnt];
	icheck = 1;
	istart = 0;
	close (icSock[iout]);
	fclose (fwp);
}


void 	tcpReadWrite ()
{
	int 			icntIndex;
	char 			serialNum[8];
  	char 			textLen[4];
  	struct Packet 	*spacket

	for (icntIndex = 0; icntIndex < iAllCnt; ++icntIndex )
	{
		if ( FD_ISSET (icSock[icntIndex], &fdRead))
		{
			char creceive_str[PACKET_SIZE];
			read (icSock[icntIndex], creceive_str, sizeof (creceive_str));
			spacket = (struct Packet*) creceive_str;

			strncpy (serialNum, spacket->serialNo, 8);
			strncpy (textLen, spacket->strlength, 4);

			// printf("==> %s, %s, %s\n",serialNum, textLen,spacket->record);


			if (istart == 0)
			{
				fwp= fopen (spacket->record, "w+");

				if (fwp == NULL)
					continue;

				printf ("open file %s\n", spacket-> record);

				istart = 1;
				++icheck;
				write (icSock[icntIndex], (char*)&ok_ack, sizeof (struct Packet_Ack));
				continue;
			}

			if (strncmp (spacket->record, MSG_END, strlen(MSG_END)) == 0)
			{
				write (icSock[icntIndex], (char*)&ok_ack, sizeof (struct Packet_Ack));
				tcpCloseClient (icntIndex);
				continue;
			}

			tcpCheckWrite (serialNum, textLen, spacket->record, icntIndex);
		}
	}// end for loop
}	


void	tcpCheckWrite(char serialNo[8], char textLen[4], char record[MAX_LEN], int iCnt)
{
    if(icheck!=atoi(serialNo)){
      printf ("num check err %d %d\n",icheck,atoi(serialNo));
      write (icSock[iCnt],(char*)&err_ack,sizeof(struct Packet_Ack));
      tcpCloseClient (iCnt);
    }
    // else if(atoi(textLen)!=strlen(record)){
    //   printf("len check err  %d %d\n",atoi(textLen),strlen(record));
    //   write(icSock[iCnt],(char*)&err_ack,sizeof(struct Packet_Ack));
    //   tcpCloseClient (iCnt);
    // }
    else{
      write (icSock[iCnt], (char*)&ok_ack, sizeof(struct Packet_Ack));
      fputs (record, fwp);
      ++icheck;
    }

}

// void tcpGetNewCnt ()
// {
// 	int 			icntIndex;
// 	for (icntIndex=0; icntIndex < iAllCnt; ++icntIndex)
// 	{
// 		FD_SET(icSock[icntIndex], &fdRead);
// 		if()
// 	}
// }

// void setOkAck()
// {
// 	memset(&ok_ack,0,sizeof(struct Packet_Ack));
//   	sprintf(ok_ack.strlength,"%d",2);
//   	strncpy(ok_ack.ack,"OK",2);
// }

// void setErrAck(){
// 	memset(&err_ack,0,sizeof(struct Packet_Ack));
// 	sprintf(err_ack.strlength,"%d",3);
// 	strncpy(err_ack.ack,"ERR",3);
// }

// void setAck()
// {
// 	setOkAck();
// 	setErrAck();
// }