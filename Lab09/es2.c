#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void semaphoreInit(int *S);
void semaphoreSignal(int *S);
void semaphoreWait(int *S);
void semaphoreDestroy(int *S);

void spawn(void (*f)(void)){
	if(fork()==0){
		f();
		exit(0);
	}
}


void A();
void B();
void C();
void D();
void E();
void F();
void G();
void H();
void I();

int semA[2],semBCD[2],semEF[2],semG[2],semH[2],semI[2];


int main(int argc,char* argv[]){

	semA[0]=open("./fileinput/semAW.txt",O_CREAT|O_RDWR,S_IWUSR);
	semA[1]=open("./fileinput/semAR.txt",O_CREAT|O_RDWR,S_IRUSR);

	semBCD[0]=open("./fileinput/semBCDW.txt",O_CREAT|O_WRONLY,S_IWUSR);
	semBCD[1]=open("./fileinput/semBCDR.txt",O_CREAT|O_RDONLY,S_IRUSR);

	semEF[0]=open("./fileinput/semEFW.txt",O_CREAT|O_WRONLY,S_IWUSR);
	semEF[1]=open("./fileinput/semEFR.txt",O_CREAT|O_RDONLY,S_IRUSR);

	semG[0]=open("./fileinput/semGW.txt",O_CREAT|O_WRONLY,S_IWUSR);
	semG[1]=open("./fileinput/semGR.txt",O_CREAT|O_RDONLY,S_IRUSR);

	semH[0]=open("./fileinput/semHW.txt",O_CREAT|O_WRONLY,S_IWUSR);
	semH[1]=open("./fileinput/semHR.txt",O_CREAT,O_RDONLY,S_IRUSR);

	semI[0]=open("./fileinput/semIW.txt",O_CREAT|O_WRONLY,S_IWUSR);
	semI[1]=open("./fileinput/semIR.txt",O_CREAT|O_RDONLY,S_IRUSR);

	if(semA[0]<0 || semA[1]<0 || semBCD[0]<0 || semBCD[1]<0 || semEF[0]<0
		|| semEF[1]<0 || semG[0]<0 || semG[1]<0 || semH[0]<0 || semH[1]<0
		|| semI[0]<0 || semI[1]<0)
	{
		fprintf(stderr, "errore file\n" );
		exit(1);
	}	
	//creo una pipe per ogni semaforo
	pipe(semA);
	pipe(semBCD);
	pipe(semEF);
	pipe(semG);
	pipe(semH);
	pipe(semI);

	//signal per inziare
	semaphoreSignal(semA);
	//ciclo esterno
	while(1){
		spawn(A);
		spawn(B);
		spawn(C);
		spawn(D);
		spawn(E);
		spawn(F);
		spawn(G);
		spawn(H);
		//spawn(I);
		I();
	}

	//chiudo tutte le pipe
	semaphoreDestroy(semA);
	semaphoreDestroy(semBCD);
	semaphoreDestroy(semEF);
	semaphoreDestroy(semG);
	semaphoreDestroy(semH);
	semaphoreDestroy(semI);



}

void A(){
//	printf("sono in A\n");
	semaphoreWait(semA);
	fprintf(stdout, "A\n");
	sleep(2);
	semaphoreSignal(semBCD);
	semaphoreSignal(semBCD);
	semaphoreSignal(semBCD);
	
}

void B(){
	semaphoreWait(semBCD);
	fprintf(stdout, "B\n");
	sleep(2);
	semaphoreSignal(semI);
	
}

void C(){
	semaphoreWait(semBCD);
	fprintf(stdout, "C\n");
	sleep(2);
	semaphoreSignal(semEF);
	semaphoreSignal(semEF);

}

void D(){
	semaphoreWait(semBCD);
	fprintf(stdout, "D\n");
	sleep(2);
	semaphoreSignal(semH);
	
}

void E(){
	semaphoreWait(semEF);
	fprintf(stdout, "E\n" );
	sleep(2);
	semaphoreSignal(semG);
	
}

void F(){
	semaphoreWait(semEF);
	fprintf(stdout, "F\n");
	sleep(2);
	semaphoreSignal(semG);
	
}

void G(){
	semaphoreWait(semG);
	semaphoreWait(semG);
	fprintf(stdout, "G\n");
	sleep(2);
	semaphoreSignal(semI);
	
}

void H(){
	semaphoreWait(semH);
	fprintf(stdout, "H\n");
	sleep(2);
	semaphoreSignal(semI);
	
}

void I(){
	semaphoreWait(semI);
	semaphoreWait(semI);
	semaphoreWait(semI);
	fprintf(stdout, "I\n");
	sleep(2);
	semaphoreSignal(semA);
	
}

void semaphoreInit(int *S){
	if(pipe(S)<0){
		fprintf(stderr, "errore allocazione pipe\n");
		exit(1);
	}
	return;
}

void semaphoreSignal(int *S){
	char c='X';
	if(write(S[1],&c,sizeof(char))!=1){
		fprintf(stderr, "errore scrittura\n" );
		exit(1);
	}
	return;
}

void semaphoreWait(int *S){
	char c;
	if(read(S[0],&c,sizeof(char))<0){
		fprintf(stderr, "errore lettura\n");
		exit(1);
	}
	return;
}

void semaphoreDestroy(int *S){
	close(S[0]);
	close(S[1]);
	return;
}
