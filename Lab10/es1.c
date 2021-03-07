#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>
#include <ctype.h>

#define L 100

//flag per capire quando terminare
int flag=1;
//stringa globale
char buff[L];

void *reader(void *arg);
void *trasformers(void *arg);
void *writer(void *arg);

void toUpperInverse(char *val);

//semafori
sem_t s1,s2,s3;
//file globali
FILE *fin,*fout;

int main(int argc,char* argv[]){
	pthread_t t1,t2,t3;

	if(argc!=3){
		fprintf(stderr, "Errore parametri\n");
		exit(1);
	}
	fin=fopen(argv[1],"r");
	fout=fopen(argv[2],"w");

	if(fin==NULL || fout==NULL){
		fprintf(stderr, "errore file\n");
		exit(1);
	}
	//inizializzo semafori
	if(sem_init(&s1,0,1)==-1 ||
	   sem_init(&s2,0,0)==-1 ||
 	   sem_init(&s3,0,0)==-1){
		fprintf(stderr, "errore semafori\n");
	exit(1);
	}

	pthread_create(&t1,NULL,reader,NULL);
	pthread_create(&t2,NULL,trasformers,NULL);
	pthread_create(&t3,NULL,writer,NULL);

	pthread_join(t1,NULL);
	pthread_join(t2,NULL);
	pthread_join(t3,NULL);

	fprintf(stdout, "Fine\n");

	return 0;






}


void *reader(void *arg){
	
	while(1){
		sem_wait(&s1);
		if(fgets(buff,L,fin)==NULL){
			//setto flag a 0 e sveglio s2
			flag=0;
			sem_post(&s2);
			break;
		}
		//sveglio s2
		sem_post(&s2);
	}
	fprintf(stdout, "Fine Reader\n");
	pthread_exit((void*)1);
}


void *trasformers(void *arg){
	while(1){

		sem_wait(&s2);

		if(flag==0){
			sem_post(&s3);
			break;
		}
		toUpperInverse(buff);

		sem_post(&s3);
	}
	fprintf(stdout, "Fine trasformers\n");
	pthread_exit((void*)1);
}


void *writer(void *arg){
	while(1){
		sem_wait(&s3);
		if(flag==0){
			break;
		}
		fprintf(fout, "%s\n",buff);
		sem_post(&s1);
	}
	fprintf(stdout, "Fine writers\n");
	pthread_exit((void*)1);
}


void toUpperInverse(char *val){
	int i,j=strlen(val)-1;
	char tmp;

	for(i=0;i<strlen(val)/2;i++){
		tmp=val[i];
		if(isalpha(val[i])){
			tmp=toupper(val[i]);

		}
		if(isalpha(val[j]))
			val[j]=toupper(val[j]);
		val[i]=val[j];
		val[j]=tmp;
		j--;
	}
	val[strlen(val)/2]=toupper(val[strlen(val)/2]);
	return;
}
