#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>


void ciclo(int n,int t);

int main(int argc,char * argv[]) {
	int n,t;

	if(argc!=3){
		printf("errore parametri\n");
		exit(1);
	}
	n=atoi(argv[1]);
	t=atoi(argv[2]);
	ciclo(n,t);

}

void ciclo(int n,int t){
	int i;

	for(i=0;i<n;i++){
		if(fork()){
			if(fork()){
				exit(1);
			}
		}
	}
	sleep(t);
	printf("%d %d\n",getpid(),getppid());
}
