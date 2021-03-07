#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>
#include <semaphore.h>

typedef struct threadData{
	pthread_t threadId;
}threadData;

void *A(void *arg);
void *B(void *arg);
void *C(void *arg);
void *D(void *arg);
void *E(void *arg);
void *F(void *arg);
void *G(void *arg);
void *H(void *arg);
void *I(void *arg);

//dichiaro semafori
sem_t semA,semB,semC,semD,semE,semF,semG,semH,semI;

int main(int argc,char *argv[]){
	struct threadData td[9];

	sem_init(&semA,0,1);
	sem_init(&semB,0,0);
	sem_init(&semC,0,0);
	sem_init(&semD,0,0);
	sem_init(&semE,0,0);
	sem_init(&semF,0,0);
	sem_init(&semG,0,0);
	sem_init(&semH,0,0);
	sem_init(&semI,0,0);

	printf("sono qua\n");

	if(pthread_create(&(td[0].threadId),NULL,A,(void*)&td[0])!=0){
		printf("errore thread\n");
	}
	if(pthread_create(&(td[1].threadId),NULL,B,(void*)&td[1])!=0){
		printf("errore thread\n");
	}
	if(pthread_create(&(td[2].threadId),NULL,C,(void*)&td[2])!=0){
		printf("errore thread\n");
	}
	if(pthread_create(&(td[3].threadId),NULL,D,(void*)&td[3])!=0){
		printf("errore thread\n");
	}
	if(pthread_create(&(td[4].threadId),NULL,E,(void*)&td[4])!=0){
		printf("errore thread\n");
	}
	if(pthread_create(&(td[5].threadId),NULL,F,(void*)&td[5])!=0){
		printf("errore thread\n");
	}
	if(pthread_create(&(td[6].threadId),NULL,G,(void*)&td[6])!=0){
		printf("errore thread\n");
	}
	if(pthread_create(&(td[7].threadId),NULL,H,(void*)&td[7])!=0){
		printf("errore thread\n");
	}
	if(pthread_create(&(td[8].threadId),NULL,I,(void*)&td[8])!=0){
		printf("errore thread\n");
	}

	void* retval;

	pthread_join(td[0].threadId,&retval);
	pthread_join(td[1].threadId,&retval);
	pthread_join(td[2].threadId,&retval);
	pthread_join(td[3].threadId,&retval);
	pthread_join(td[4].threadId,&retval);
	pthread_join(td[5].threadId,&retval);
	pthread_join(td[6].threadId,&retval);
	pthread_join(td[7].threadId,&retval);
	pthread_join(td[8].threadId,&retval);

	printf("fine\n");
}

void *A(void *arg){
	while(1){
		sem_wait(&semA);
		printf("A\n");
		sleep(2);
		sem_post(&semB);
		sem_post(&semC);
		sem_post(&semD);
	}
}

void *B(void *arg){
	while(1){
		sem_wait(&semB);
		printf("B\n");
		sleep(2);
		sem_post(&semI);
	}
}

void *C(void *arg){
	while(1){
		sem_wait(&semC);
		printf("C\n");
		sleep(2);
		sem_post(&semE);
		sem_post(&semF);
	}
}

void *D(void *arg){
	while(1){
		sem_wait(&semD);
		printf("D\n");
		sleep(2);
		sem_post(&semH);
	}
}

void *E(void *arg){
	while(1){
		sem_wait(&semE);
		printf("E\n");
		sleep(2);
		sem_post(&semG);
	}
}


void *F(void *arg){
	while(1){
		sem_wait(&semF);
		printf("F\n");
		sleep(2);
		sem_post(&semG);
	}
}


void *G(void *arg){
	while(1){
		sem_wait(&semG);
		sem_wait(&semG);
		printf("G\n");
		sleep(2);
		sem_post(&semI);
	}
}


void *H(void *arg){
	while(1){
		sem_wait(&semH);
		printf("H\n");
		sleep(2);
		sem_post(&semI);
	}
}


void *I(void *arg){
	while(1){
		sem_wait(&semI);
		sem_wait(&semI);
		sem_wait(&semI);
		printf("I\n");
		sleep(2);
		sem_post(&semA);
	}
}
