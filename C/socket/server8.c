#include  <stdio.h>
#include  <stdlib.h>
#include  <string.h>
#include  <unistd.h>
#include  <sys/types.h>
#include  <sys/socket.h>
#include  <netinet/in.h>
#include  <arpa/inet.h>
#include  <strings.h>
#include  <errno.h>
#include  <sys/select.h>
#include  <sys/time.h>
#include  <time.h>

#define   PORT      12313
#define   IP        "192.168.103.10"

#define   MSG_SIZE  255
#define   BUF_SIZE  (MSG_SIZE+1)
#define   MSG_END   "END"

#define MAX_USER 30
#define MAX_LEN 100

void log_msg(char* msg);
void log_date();

struct Packet{
  char serialNo [8];
  char strlength  [4];
  char record [MAX_LEN];
};

struct Packet_Ack
{
  char  strlength [4];
  char  ack [4];
};


int  main(void)
{
  int iSock;   //소켓 함수의 반환 값을 받는 변수
  int icSock[MAX_USER];   //accept의 반환 값을 받는 변수
  int iRtn;
  struct sockaddr_in stAddr;
  socklen_t uiSockLen=sizeof(struct sockaddr);
  char cBuf[BUF_SIZE];
  const char * cP;
  fd_set fdRead;
  unsigned int uiUser;
  unsigned int uiCnt, uiCnt2;
  int iMSock;  //store greatest number in file descriptors
  int istart;

  char packet_str [112];
  struct Packet *packet;
  FILE *fwrite;
  int icheck;
  struct Packet_Ack err_ack, ok_ack;

  memset(&ok_ack,0,sizeof(struct Packet_Ack));
  sprintf(ok_ack.strlength,"%d",2);
  strncpy(ok_ack.ack,"OK",2);

  memset(&err_ack,0,sizeof(struct Packet_Ack));
  sprintf(err_ack.strlength,"%d",3);
  strncpy(err_ack.ack,"ERR",3);

  char serialNum[8];
  char textLen[4];


  iSock = socket(AF_INET, SOCK_STREAM, 0);    //AF_INET = 2, 
  if(0 > iSock)
  {
    log_msg("socket init err\n");
    exit(1);
  }

  // stAddr구조체에 socket연결을 위한 필수 정보 입력  setting
  bzero(&stAddr, sizeof(stAddr));            //구조체 비우기(0으로 채우기)
  stAddr.sin_family = AF_INET;               //#define AF_INET 2 /* IP protocol family. */
  stAddr.sin_addr.s_addr = inet_addr(IP);    //IP와 PORT값은 헤더파일에 정의되어 있다.
  stAddr.sin_port = htons((PORT));

  iRtn = bind(iSock, (struct sockaddr *)&stAddr,sizeof(stAddr));
  if(iRtn < 0)
  {
    log_msg("bind err\n");
    close(iSock);
    exit(1);
  }

  iRtn = listen(iSock, 5);

  if(iRtn != 0)
  {
    log_msg("listen err\n");
    close(iSock);
    exit(1);
  }

  uiUser = 0;
  icheck=1;
  istart=0;
// FD_ZERO(&fdRead);    //fdRead 변수 1024byte 전부 0으로 세팅 
//     FD_SET(0, &fdRead);  //키보드 입력 감시
//     FD_SET(iSock, &fdRead);  //접속 소켓 감시
  log_date();
  log_msg("=====================");
  while(1) 
  {
    //setting fd_set
    FD_ZERO(&fdRead);    //fdRead 변수 1024byte 전부 0으로 세팅 
    FD_SET(0, &fdRead);  //키보드 입력 감시
    FD_SET(iSock, &fdRead);  //접속 소켓 감시
    iMSock = iSock;      //소켓의 최대값 저장 -> select함수 첫번째 인자는 감시하는 파일 값 + 1기 때문이 이에 대한 최대값 저장

    for(uiCnt = 0; uiCnt < uiUser; ++uiCnt)  //사용자가 접속하면 해당 Fd를 set해주고 가장 높은 fd값을 저장
    {
      FD_SET(icSock[uiCnt], &fdRead);  //접속한 사용자수만큼의 icSock배열에 소켓 값이 들어있음으로 이를 감시 
      if(iMSock < icSock[uiCnt])
      {
        iMSock = icSock[uiCnt];  //iMSock에 소켓의 최대값 저장
      }      
    }

    select((iMSock+1), &fdRead, 0, 0, 0);//select 함수를 사용하여 감시해준다.(입력이 있을때까지 무한대기)

    if( 0 != FD_ISSET(iSock, &fdRead) ) //랑데뷰 소켓이 set(1)되어 있으면(사람이 접속하면) accept함수를 받아서 대화 소켓을 열어준다.
    {
      icSock[uiUser] = accept(iSock, (struct sockaddr *)&stAddr, &uiSockLen); //대화 소켓 값을 icSock배열에 저장해준다.
      if(icSock[uiUser] < 0)
      {
        log_msg("Accept : ");
        continue;
      }

      log_msg("Incoming Client\n");
      log_msg("Client IP : ");
      log_msg(inet_ntoa(stAddr.sin_addr));      //사용자가 접속하면 IP를 출력시켜준다.
      log_msg("\n");
      ++uiUser;                //사용자 수 +
    }

    for(uiCnt = 0; uiCnt < uiUser; ++uiCnt)          //접속 클라이언트 대화 소켓을 순회하면서 대화내용이 있는지 확인
    {  
      if( 0 != FD_ISSET(icSock[uiCnt], &fdRead))
      {

        read(icSock[uiCnt], packet_str, sizeof(packet_str));          //대화가 있으면 읽어들임
        packet=(struct Packet*)packet_str;
        strncpy(serialNum, packet->serialNo,8);
        strncpy(textLen, packet->strlength,4);
        //printf("uiCnt : %d ==> %s, %s, %s\n",uiCnt,packet->serialNo, packet->strlength, packet->record);
        printf("uiCnt : %d ==> %s, %s, %s\n",uiCnt,serialNum, textLen,packet->record);

        if(istart==0){
          printf("get file name %s\n",packet->record);

                  
          fwrite=fopen(packet->record,"w+");

          if(fwrite==NULL){
            log_msg("write file open error\n");
            exit(1);
          }

          istart=1;
          ++icheck;
          write(icSock[uiCnt],(char*)&ok_ack,sizeof(struct Packet_Ack));
          continue;
        }

        if( 0 == strncmp(packet->record,MSG_END, strlen(MSG_END)) )       //클라이언트가 종료 메세지를 입력할 경우
        {
          write(icSock[uiCnt],(char*)&ok_ack,sizeof(struct Packet_Ack));
          close(icSock[uiCnt]);            //해당 소켓을 닫고          
          --uiUser;                //uiUser 수를 줄여주고
          icSock[uiCnt] = icSock[uiUser];          //빠져나간 자리에 가장 마지막에 들어온 유저의 소켓 번호를 넣어준다
          fclose(fwrite);
          icheck=1;
          istart=0;
          continue;
        }

        if(icheck!=atoi(serialNum)){
          printf("num check err %d %d\n",icheck,atoi(serialNum));
          log_msg("num check err\n");
          write(icSock[uiCnt],(char*)&err_ack,sizeof(struct Packet_Ack));
          close(icSock[uiCnt]);
        }
        // else if(atoi(textLen)!=strlen(text)){
        //   log_msg("len check err\n");
        //   printf("len check err  %d %d\n",atoi(textLen),strlen(text));
        //   write(icSock[uiCnt],(char*)&err_ack,sizeof(struct Packet_Ack));
        //   close(icSock[uiCnt]);
        // }
        else{
          write(icSock[uiCnt],(char*)&ok_ack,sizeof(struct Packet_Ack));
          fputs(packet->record, fwrite);
          ++icheck;
        }

        
      }
    } // end for loop

  } // end while 


  for(uiCnt = 0; uiCnt < uiUser; ++uiCnt)          //종료시 열린 소켓을 모두 닫아준다.
  {
   close(icSock[uiCnt]);  
  }

  log_msg("=========================\n\n");

  close(iSock);
  exit(0);
}


void log_msg(char* msg){
  FILE* fp;
  fp=fopen("logfile.log","a+");
  fprintf(fp,"%s",msg);
  fclose(fp);
}

void log_date()
{

  FILE* fp;
  fp=fopen("logfile.log","a+");
  struct tm *date;
  time_t t = time(NULL); 
  date = localtime(&t);
  fprintf (fp, "\n");
  fprintf( fp,"%d/%d/%d %d:%d:%d\n" , date->tm_year + 1900 , date->tm_mon + 1 , date->tm_mday , date->tm_hour , date->tm_min , date->tm_sec );
  fclose (fp);
 
}