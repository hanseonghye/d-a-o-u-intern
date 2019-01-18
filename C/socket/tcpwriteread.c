#include <stdio.h>

extern struct Packet_Ack 		err_ack, ok_ack;
extern int 				istart, icheck;
extern int 				icSock[MAX_USER];
extern unsigned int 	iAllCnt;
extern fd_set 			fdRead;

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