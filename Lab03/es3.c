#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>



int main(int argc,char* argv[]){
	

	fprintf(stdout, "P1 - PID: %d\t PPID: %d\n",getpid(),getppid());

	if(fork()){
		fprintf(stdout, "P2 - PID: %d\t PPID: %d\n",getpid(),getppid());
		if(fork()){
			fprintf(stdout, "P4 - PID: %d\t PPID: %d\n",getpid(),getppid());
			wait((int *)0);

		}else{
			fprintf(stdout, "P5 - PID: %d\t PPID: %d\n",getpid(),getppid());
			exit(1);
		}
		fprintf(stdout, "P7 - PID: %d\t PPID: %d\n",getpid(),getppid());
		wait((int *)0);
	}else{
		fprintf(stdout,"P3 - PID: %d\t PPID: %d\n",getpid(),getppid());
		if(fork())
			wait((int *)0);
		else{
			fprintf(stdout, "P6 - PID: %d\t PPID: %d\n",getpid(),getppid());
			exit(1);
		}
		fprintf(stdout, "P8 - PID:%d\t PPID: %d\n",getpid(),getppid());
		exit(1);
	}
	fprintf(stdout,"P9 -PID: %d\t PPID: %d\n",getpid(),getppid());
}
