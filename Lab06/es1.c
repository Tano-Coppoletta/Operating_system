#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <ctype.h>
#include <sys/wait.h>


#define N 50

void maiuscolo(char* stringa);



int main(int argc,char* argv[]){
	int fp[2];
	
	char stringa[N];

	

	setbuf(stdout,0);

	fp[0]=open(argv[1],O_WRONLY);
	if(fp[0]<0){
		fprintf(stderr, "errore fin\n");
		exit(1);
	}
	fp[1]=open(argv[2],O_RDONLY);
	if(fp[1]<0){
		fprintf(stderr, "errore fout\n" );
		exit(1);
	}

	pipe(fp);

	if((fork())){
		//padre
		if(fork()){
			//padre
			wait((int*)0);
			wait((int*)0);
		}else{
			//figlio produttore
			//chiudo terminale pipe che non uso
			close(fp[0]);
			while(1){
				fscanf(stdin,"%s",stringa);
				int wr=write(fp[1],stringa,N*sizeof(char));

				if(strcmp(stringa,"end")==0){
					fprintf(stdout,"fine\n");
					exit(1);
				}
			}
		}
	}else{
		//figlio consumatore
		close(fp[1]);
		char letto[N];
		while(1){
			read(fp[0],letto,N*sizeof(char));

			if(strcmp(letto,"end")==0)
				exit(1);
			maiuscolo(letto);
			fprintf(stdout, "%s\n",letto );

		}
	}
	
}

void maiuscolo(char* stringa){
	int n=strlen(stringa);
	int i;

	for(i=0;i<n;i++){
		stringa[i]=(char)toupper(stringa[i]);
	}

}
