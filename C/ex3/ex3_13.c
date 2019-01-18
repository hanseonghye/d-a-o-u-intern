/*
	Author : 한성혜 ( daou13 )
	Date : 2019.01.10
	Description : 다섯번의 입력을 받은 뒤 파일에 작성함.
				한 라인씩 작성된 입력 값을 파일에서 읽어서 화면에 출력함.
	*/

#include	<stdio.h>
#include	<stdlib.h>
#include 	<string.h>
#define		MAX_LEN 100

int	main (void)
{
	char	cline[MAX_LEN];
	char	*cinput2, *coutput;
	int		i, len, count;
	FILE	*fwrite, *fread;

	fwrite = NULL;
	fread = NULL;
	
	fwrite = fopen ("ex3_13.dat","w+");

	if ( fwrite == NULL ){
		printf ("write file open error\n");
		exit (1);
	}


	/*
		다섯번의 입력을 받는다. 
		이때 newline은 입력으로 보지 않는다.
		__fpurge 함수를 통해 stdin buffer를 clear한다. 
		*/

	count = 0;

	while(1){
		if( count == 5 ) break;

		cinput2 = fgets (cline, MAX_LEN, stdin);
		len = strlen (cinput2);
		
		if(len>1){
			cinput2[len-1]='\n';
			fputs (cinput2, fwrite);
			++count;
		}

		__fpurge (stdin);
	}


	printf ("\n");
	printf ("===================\n\n");

	fclose ( fwrite );

	fread = fopen ("ex3_13.dat","r");

	if ( fread == NULL ){
		printf ("read file open error\n");
		exit (1);
	}

	/*
		파일에 입력된 5개의 문자열을 print함.
		한 라인의 마지막 문자를 '\0'로 변경한 뒤 출력함.
	*/
	for( i = 0; i<5 ; ++i ){
		coutput = fgets (cline, MAX_LEN, fread);
		len = strlen (coutput);

		if( len>0 && coutput[len-1] == '\n'){
			coutput[len-1] = '\0';
		}
		printf ("[%s]\n",coutput);
	}

	fclose (fread);
	exit (0);

}

