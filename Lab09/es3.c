#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>
#include <semaphore.h>

sem_t semA,semBCD,semEF,semG,semH,semI;

void *ret;

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

int main(int argc,char* argv[]){
//vettore di struct thread
	struct threadData td[9];
	int i;
	void *retval;

	sem_init(&semA,0,1);
	sem_init(&semBCD,0,0);
	sem_init(&semEF,0,0);
	sem_init(&semG,0,0);
	sem_init(&semH,0,0);
	sem_init(&semI,0,0);

	while(1){
		pthread_create(&(td[0].threadId),NULL,A,(void*)&td[0]);
		pthread_create(&(td[1].threadId),NULL,B,(void*)&td[1]);
		pthread_create(&(td[2].threadId),NULL,C,(void*)&td[2]);
		pthread_create(&(td[3].threadId),NULL,D,(void*)&td[3]);
		pthread_create(&(td[4].threadId),NULL,E,(void*)&td[4]);
		pthread_create(&(td[5].threadId),NULL,F,(void*)&td[5]);
		pthread_create(&(td[6].threadId),NULL,G,(void*)&td[6]);
		pthread_create(&(td[7].threadId),NULL,H,(void*)&td[7]);
		pthread_create(&(td[8].threadId),NULL,I,(void*)&td[8]);

		pthread_join(td[0].threadId,&retval);
		pthread_join(td[1].threadId,&retval);
		pthread_join(td[2].threadId,&retval);
		pthread_join(td[3].threadId,&retval);
		pthread_join(td[4].threadId,&retval);
		pthread_join(td[5].threadId,&retval);
		pthread_join(td[6].threadId,&retval);
		pthread_join(td[7].threadId,&retval);
		pthread_join(td[8].threadId,&retval);
		
	}

}


void *A(void *arg){
	sem_wait(&semA);
	printf("A\n");
	sleep(2);
	sem_post(&semBCD);
	sem_post(&semBCD);
	sem_post(&semBCD);
	pthread_exit(ret);
}

void *B(void *arg){
	sem_wait(&semBCD);
	printf("B\n");
	sleep(2);
	sem_post(&semI);
	pthread_exit(ret);
}

void *C(void *arg){
	sem_wait(&semBCD);
	printf("C\n");
	sleep(2);
	sem_post(&semEF);
	sem_post(&semEF);
	pthread_exit(ret);
}

void *D(void *arg){
	sem_wait(&semBCD);
	printf("D\n");
	sleep(2);
	sem_post(&semH);
	pthread_exit(ret);
}

void *E(void *arg){
	sem_wait(&semEF);
	printf("E\n");
	sleep(2);
	sem_post(&semG);
	pthread_exit(ret);
}

void *F(void *arg){
	sem_wait(&semEF);
	printf("F\n");
	sleep(2);
	sem_post(&semG);
	pthread_exit(ret);

}

void *G(void *arg){
	sem_wait(&semG);
	sem_wait(&semG);
	printf("G\n");
	sleep(2);
	sem_post(&semI);
	pthread_exit(ret);
}

void *H(void *arg){
	sem_wait(&semH);
	printf("H\n");
	sleep(2);
	sem_post(&semI);
	pthread_exit(ret);
}

void *I(void *arg){
	sem_wait(&semI);
	sem_wait(&semI);
	sem_wait(&semI);
	printf("I\n");
	sleep(2);
	sem_post(&semA);
	pthread_exit(ret);
}
