#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

static void sigAlrm(int signo){
	return;
}

int main(int argc,char* argv[]){
	int pid;

	signal(SIGALRM,sigAlrm);

	pid=fork();
	while(1){
		if(pid==0){
			fprintf(stdout,"Child woke-up\n");
			sleep(1);
			kill(getppid(),SIGALRM);
			pause();
		}else{
			fprintf(stdout,"Father woke-up\n");
			sleep(1);
			kill(pid,SIGALRM);
			pause();
		}
	}
	return 0;
}
