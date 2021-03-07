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

sem_t s1,s2,s3,s4;

typedef struct threadData{
	int fd;
}threadData;

typedef struct monomio{
	float c,x;
	int n;
}monomio;

//somme dei monomi come variabili globali
float sum1,sum2,sum3;
//flag per far morire T4
int flag=0;

void *monomioUno(void *args);
void *monomioDue(void *args);
void *monomioTre(void *args);
void *somma(void *args); 
float calcola(monomio m);

int main(int argc,char* argv[]){
	int fd;
	struct threadData tD;
	pthread_t t[4];

	if(argc!=2){
		fprintf(stderr, "Errore parametri\n");
		exit(1);
	}

	fd=open(argv[1],O_RDONLY);

	if(fd==-1){
		fprintf(stderr, "Errore file\n");
		exit(1);
	}

	sem_init(&s1,0,1);
	sem_init(&s2,0,1);
	sem_init(&s3,0,1);
	sem_init(&s4,0,0);

	tD.fd=fd;

	pthread_create(&t[0],NULL,monomioUno,(void*)&tD);
	pthread_create(&t[1],NULL,monomioDue,(void*)&tD);
	pthread_create(&t[2],NULL,monomioTre,(void*)&tD);
	pthread_create(&t[3],NULL,somma,(void*)&tD);

	pthread_join(t[0],NULL);
	pthread_join(t[1],NULL);
	pthread_join(t[2],NULL);
	pthread_join(t[3],NULL);

	return 0;

}


void *monomioUno(void *args){
	struct threadData *tD;
	tD=(struct threadData *)
	 args;
	int fd=tD->fd;
	int i=0,n=10;
	//n è un valore fittizio per iniziare il ciclo
	struct monomio m;

	while(n>0){
		sem_wait(&s1);
		lseek(fd,i*sizeof(monomio),SEEK_SET);
		n=read(fd,&m,sizeof(monomio));
		if(n>0){
			fprintf(stdout, "%f %f %d\n",m.c,m.x,m.n );
			sum1=calcola(m);
		}else{
			sum1=0;
			flag=1;
		}
		//sveglio s2
		sem_post(&s4);
		i=i+3;
	}
	pthread_exit((void*)1);

}

void *monomioDue(void *args){
	struct threadData *tD;
	tD=(struct threadData *)
	 args;
	 int fd=tD->fd;
	int i=1,n=10;
	//n è un valore fittizio per iniziare il ciclo
	struct monomio m;
	while(n>0){
		sem_wait(&s2);
		lseek(fd,i*sizeof(monomio),SEEK_SET);
		n=read(fd,&m,sizeof(monomio));
	
		if(n>0){
			sum2=calcola(m);
		}else{
			sum2=0;
			flag=2;
		}
		sem_post(&s4);
		i+=3;
	}
	pthread_exit((void*)1);
	
}
void *monomioTre(void *args){
	struct threadData *tD;
	tD=(struct threadData *)
	 args;
	int fd=tD->fd;
	int i=2,n=10;
	//n è un valore fittizio per iniziare il ciclo
	struct monomio m;
	while(n>0){
		sem_wait(&s3);
		lseek(fd,i*sizeof(monomio),SEEK_SET);
		n=read(fd,&m,sizeof(monomio));
		if(n>0){
			sum3=calcola(m);
		}else{
			sum3=0;
			flag=3;
		}
		sem_post(&s4);
		i+=3;
	}
	pthread_exit((void*)1);
}

void *somma(void *args){
	float i;
	
	while(1){	
	//aspetto i monomi
	sem_wait(&s4);
	sem_wait(&s4);
	sem_wait(&s4);



	//sommo e stampo
	i=sum1+sum2+sum3;
	fprintf(stdout, "Somma: %f\n",i );
	if(flag!=0){
		pthread_exit((void*)1);
	}

	sem_post(&s1);
	sem_post(&s2);
	sem_post(&s3);
	}
}

 
float calcola(monomio m){
	int i;
	int sum;
	for(i=1;i<m.n;i++){
		sum=m.x*m.x;
	}
	sum=sum*m.c;

	return sum;
}
