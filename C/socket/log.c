#include 	<stdio.h>

void	log_msg (char* msg){
	FILE* fp;
	fp = fopen ("logfile.log", "a+");
	fprintf (fp, "%s", msg);
	fclose (fp);
}