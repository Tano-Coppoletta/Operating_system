#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>


#define N 50

void maiuscolo(char* stringa);

static void sigAlrm(int signo){
	return;
}

int main(int argc,char* argv[]){
	pid_t pidc1;
	int fp;
	if(argc!=2){
		fprintf(stderr, "Errore parametri\n");
	}

	//instanzio gestore di segnale
	signal(SIGALRM,sigAlrm);

	fp=open(argv[1],O_RDWR);

	if(fp==-1){
		fprintf(stderr, "Errore file\n");	
		exit(1);
	}

	
	//padre
	if((pidc1=fork())){
		if(fork()){
			//padre
			wait((int*)0);
			wait((int*)0);
		}else{
			//figlio produttore
			while(1){
				pid_t pidc2=getpid();
				char stringa[N];

				fscanf(stdin,"%s",stringa);
				//scrivo pid sul file
				int wr=write(fp,&pidc2,sizeof(pid_t));
				//printf("%d\n",pidc2);
				//scrivo stringa su file;
				wr+=write(fp,stringa,N*sizeof(char));
				//printf("%s %d \n",stringa,pidc1 );
				if(wr!=N*sizeof(char)+sizeof(pid_t))
					fprintf(stderr, "errore buffer\n");
				//mi rimetto all'inizio del file
				lseek(fp,0,SEEK_SET);
				//sveglio figlio
				kill(pidc1,SIGALRM);
				//controllo se hanno scritto end
				if(strcmp("end",stringa)==0)
					exit(1);
				pause();
			}
		}

	}else{
		//consumatore
		while(1){
			pause();
			char buff[N];
			pid_t source;
			int rd=read(fp,&source,sizeof(pid_t));
			rd+=read(fp,buff,N*sizeof(char));
			
			if(rd!=N*sizeof(char)+sizeof(pid_t))
				fprintf(stderr, "errore buffer lettura\n");

			if(strcmp(buff,"end")==0)
				exit(1);
			//converto in maiuscolo e stampo
			
			maiuscolo(buff);
			fprintf(stdout, "%s\n",buff );
			lseek(fp,0,SEEK_SET);
			kill(source,SIGALRM);


		}

	}

}


void maiuscolo(char* stringa){
	int n=strlen(stringa);
	int i;

	for(i=0;i<n;i++){
		stringa[i]=(char)toupper(stringa[i]);
	}
	return;
}
