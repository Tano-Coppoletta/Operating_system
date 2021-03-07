#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

typedef struct monomio{
	float c,x;
	int n;
}monomio;

int main(int argc,char* argv[]){
	int fd;
	FILE *fp;
	monomio m;

	fp=fopen(argv[1],"r");
	fd=open(argv[2],O_WRONLY);

	if(fp==NULL || fd==-1){
		fprintf(stderr, "errore file\n");
		exit(-1);
	}

	while(fscanf(fp,"%f%f%d",&m.c,&m.x,&m.n)!=EOF){
		write(fd,&m,sizeof(monomio));
	}
	fclose(fp);
	close(fd);

	//leggo file binario

	fd=open(argv[2],O_RDONLY);
	if(fd==-1){
		fprintf(stderr, "errore file 2\n");
		exit(1);
	}
	int i=0;
	int n=10;

	while(n>0){
		lseek(fd,i*sizeof(monomio),SEEK_SET);
		n=read(fd,&m,sizeof(monomio));
		if(n>0){
			fprintf(stdout, "%f %f %d\n",m.c,m.x,m.n);
		}
		i++;
	}

	close(fd);

}
