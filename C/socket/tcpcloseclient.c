#include 	<stdio.h>

extern int 				istart, icheck;
extern int 				icSock[MAX_USER];
extern unsigned int 	iAllCnt;

void	tcpCloseClient (int iout)
{
	--iAllCnt;
	icSock[iout] = icSock[iAllCnt];
	icheck = 1;
	istart = 0;
	close (icSock[iout]);
	fclose (fwp);
}