#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>


#define N 50
#define LUNGHEZZA_FILE 5

//matrice per i thread come variabile globale
int matrice[N][N];

typedef struct file
{
	char file_in[N];
	int i;
}file;





void merge(int a[],int p,int q,int r);
void unisci(int a[],int indice);




void *tF(void *par){
	//ogni thread crea il nome del suo file
	struct file *f;
	f=(struct file*)par;
	int num,i;
	//prendo numero e creo stringa
	char fileI[N],temp[N];
	num=f->i;
	
	sprintf(temp,"%d.txt",num);
	num=num-1;
	strcpy(fileI,f->file_in);
	strcat(fileI,temp);
	FILE *fin;
	fin=fopen(fileI,"r");
	if(fin==NULL){
		fprintf(stderr, "errore filein\n" );
		exit(1);
	}
	int j;

	//alloco vettore di interi da ordinare
	int *vett;
	vett=malloc(LUNGHEZZA_FILE*sizeof(int));

	if(vett==NULL){
		fprintf(stderr, "errore malloc vett\n");
		exit(1);
	}
	//leggo file
	for(j=0;j<LUNGHEZZA_FILE;j++){
		fscanf(fin,"%d",&vett[j]);
	}
	fclose(fin);
	int tmp;
	//ordino il vettore
	for(i=0;i<LUNGHEZZA_FILE-1;i++){
		for(j=0;j<LUNGHEZZA_FILE-i-1;j++){
			if(vett[j]>vett[j+1]){
				tmp=vett[j];
				vett[j]=vett[j+1];
				vett[j+1]=tmp;
			}
		}
	}
	
	//scrivo vettore su ordinato e su matrice
	for(j=0;j<LUNGHEZZA_FILE;j++){
		matrice[num][j]=vett[j];
	}
	pthread_exit(NULL);
}

int main(int argc,char* argv[]){
	pthread_t *threads;
	struct file *files;
	int da_fondere,ordinato[N],i;

	if(argc!=4){
		fprintf(stderr, "errore parametri\n");
		exit(1);
	}
	int n=atoi(argv[1]);

	threads=malloc(n*sizeof(pthread_t));
	if(threads==NULL){
		fprintf(stderr, "errore allocazione threads\n");
		exit(1);
	}

	files=malloc(n*sizeof(struct file));
	if(files==NULL){
		fprintf(stderr, "errore allocazione struct\n");
		exit(1);
	}

	for(i=0;i<n;i++){
		strcpy(files[i].file_in,argv[2]);
		files[i].i=i+1;
		pthread_create(&threads[i],NULL,tF,(void*)&files[i]);

	}
	for(i=0;i<n;i++){
		pthread_join(threads[i],NULL);
		da_fondere=i*LUNGHEZZA_FILE;
		unisci(ordinato,i);
		if(i>0)
			merge(ordinato,0,da_fondere-1,(i+1)*LUNGHEZZA_FILE);
	}

	//scrittura su fileout
	FILE *file_out;
	file_out=fopen(argv[3],"w");
	if(file_out==NULL){
		fprintf(stderr, "errore file_out\n");
		exit(1);
	}

	for(i=0;i<n*LUNGHEZZA_FILE;i++){
		fprintf(file_out, "%d\n",ordinato[i]);
	}

	return 0;





}

void merge(int a[],int p,int q,int r){
	int i,j,k=0,b[N];
	i=p;j=q+1;

	while(i<=q && j<=r){
		if(a[i]<a[j]){
			b[k]=a[i];
			i++;
		}else{
			b[k]=a[j];
			j++;
		}
		k++;
	}
	while(i<=q){
		b[k]=a[i];
		i++;
		k++;
	}
	while(j<=r){
		b[k]=a[j];
		j++;
		k++;
	}
	for(k=p;k<=r;k++){
		a[k]=b[k-p];
	}
	return;
}

void unisci(int *a,int indice){
	int i,k=0;

	
	for(i=indice*LUNGHEZZA_FILE;i<(indice+1)*LUNGHEZZA_FILE;i++){
		a[i]=matrice[indice][k];
		//fprintf(stdout, "%d\n",a[i] );
		k++;
	}

	for(i=0;i<(indice+1)*LUNGHEZZA_FILE;i++){
		fprintf(stdout, "%d\n",a[i] );
	}

}
