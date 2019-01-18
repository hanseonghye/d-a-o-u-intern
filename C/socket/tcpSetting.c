#include 	<stdio.h>

int	tcpBind (int p_std, int p_port)
{
	int		rt;
	struct sockaddr_in sock_addr;
	
	bzero (&sock_addr, sizeof (sock_addr));
	sock_addr.sin_family = AF_INET;
	sock_addr.sin_addr.s_addr = inet_addr(IP);
	sock_addr.sin_port = htons (p_port);

	rt = bind (p_std, (struct sockaddr *)&sock_addr, sizeof (sock_addr));

	return (rt);
}

int	tcpAccept(int p_std)
{
	int 				rt;
	struct 	sockaddr_in sock_addr;
	socklen_t 			addr_len;
	char				*host_p, *ip;
	struct hostent		*hp;

	addr_len = sizeof (struct sockaddr);
	memset ((char *)&sock_addr, 0, sizeof (sock_addr));

	rt = accept (p_std, (struct sockaddr *)&sock_addr, &addr_len);
	if (rt<0){
		log_msg("accept err\n");
		return rt;
	}

	log_msg("Incoming Client\n");
	log_msg("Client IP : ");
	log_msg(inet_ntoa(sock_addr.sin_addr));      //사용자가 접속하면 IP를 출력시켜준다.
	log_msg("\n");

	return rt;
}



int tcpSocket()
{
	int 	rt;
	rt = socket (AF_INET, SOCK_STREAM, 0);

	return (rt);
}

int tcpListen( int p_std, int maxUser)
{
	int 	rt;
	rt = listen (p_std, maxUser);
	return (rt);
}

int tcpSetting(int p_std, int port, int maxUser)
{
	int 	rt;
	rt = tcpBind(p_std, port);

	if (rt < 0)
	{
		log_msg("bind err\n");
		return 0;
	}

	rt = tcpListen (p_std, maxUser);

	if (rt != 0)
	{
		log_msg ("listen err\n");
		return 0;
	}

	return 1;
}
