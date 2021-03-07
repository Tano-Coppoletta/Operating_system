#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc,char* argv[]){
	int fp[2],fo[2];
	char c1='f',c2='c';

	fp[0]=open(argv[1],O_RDONLY);
	if(fp[0]<0){
		exit(1);
	}

	fp[1]=open(argv[2],O_WRONLY);

	if(fp[1]<0)
		exit(1);

	fo[0]=open(argv[3],O_RDONLY);
	if(fo[0]<0)
		exit(1);

	fo[1]=open(argv[4],O_WRONLY);
	if(fo[1]<0)
		exit(1);
	pid_t pid=fork();
	while(1){
		if(pid!=0){
			//padre legge fp e scrive fo
			char leggo;
			close(fp[1]);
			close(fo[0]);
			fprintf(stdout, "I'm the father (PID=%d\n",getpid());
			write(fo[1],&c1,sizeof(char));
			read(fp[1],&leggo,sizeof(char));

		}else{
			//figlio legge fo e scrive fp
			char leggo;
			close(fp[0]);
			close(fo[1]);
			read(fo[0],&leggo,sizeof(char));
			fprintf(stdout, "I'm the child (PID=%d\n",getpid());
			write(fp[1],&c2,sizeof(char));
		}
	}
}
