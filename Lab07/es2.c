#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

#define N 50

typedef struct file
{
	char file_in[N];
	char file_out[N];
	int i;
}file;



void *tF(void *par){
	//ogni thread crea il nome del suo file
	struct file *f;
	f=(struct file*)par;
	int num,i;
	//prendo numero e creo stringa
	char fileI[N],fileO[N],temp[N];
	num=f->i;
	
	sprintf(temp,"%d.txt",num);
	strcpy(fileI,f->file_in);
	strcat(fileI,temp);
	strcpy(fileO,f->file_out);
	strcat(fileO,temp);
	printf("%s %s\n",fileI,fileO);
	//apro i due file
	FILE *fin;
	fin=fopen(fileI,"r");
	if(fin==NULL){
		fprintf(stderr, "errore filein\n" );
		exit(1);
	}
	
	//leggo quanti numeri contiene il file
	int da_leggere;
	fscanf(fin,"%d",&da_leggere);
	int j;

	//alloco vettore di interi da ordinare
	int *vett;
	vett=malloc(da_leggere*sizeof(int));

	if(vett==NULL){
		fprintf(stderr, "errore malloc vett\n");
		exit(1);
	}
	//leggo file
	for(j=0;j<da_leggere;j++){
		fscanf(fin,"%d",&vett[j]);
	}
	fclose(fin);
	int tmp;
	//ordino il vettore
	for(i=0;i<da_leggere-1;i++){
		for(j=0;j<da_leggere-i-1;j++){
			if(vett[j]>vett[j+1]){
				tmp=vett[j];
				vett[j]=vett[j+1];
				vett[j+1]=tmp;
			}
		}
	}
	FILE *fout;
	//apro file scrittura
	fout=fopen(fileO,"w");
	if(fout==NULL){
		fprintf(stderr, "errore fout\n");
		exit(1);
	}
	//scrivo vettore su file
	for(j=0;j<da_leggere;j++){
		fprintf(fout, "%d\n",vett[j]);
	}
	fclose(fout);
	pthread_exit(NULL);
}

int main(int argc, char* argv[]){
	pthread_t *threads;
	int n,i;
	struct file *files;

	if(argc!=4){
		fprintf(stderr, "errore parametri\n");
		exit(1);
	}
	//prelevo n
	n=atoi(argv[1]);
	threads=malloc(n*sizeof(pthread_t));
	if(threads==NULL){
		fprintf(stderr, "errore vettore threads\n");
		exit(1);
	}

	files=malloc(n*sizeof(struct file));
	if(files==NULL){
		fprintf(stderr, "errore allocazione struct\n");
		exit(1);
	}
	
	
	for(i=0;i<n;i++){
		strcpy(files[i].file_in,argv[2]);
		strcpy(files[i].file_out,argv[3]);
		files[i].i=i+1;
		pthread_create(&threads[i],NULL,tF,(void*)&files[i]);

	}
	for(i=0;i<n;i++){
		pthread_join(threads[i],NULL);
	}
	return 0;


}
