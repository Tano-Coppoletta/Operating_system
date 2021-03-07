#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <fcntl.h>
#define N 1024

void copia_ricorsiva(char* source, char* destination);

int main(int argc,char* argv[]){
	char destination[N];

	if(argc!=3){
		fprintf(stderr, "errore parametri\n");
	}
	//creo direttorio copia
	strcpy(destination,argv[2]);
	sprintf(destination,"%s/copia",destination);
	mkdir(destination,S_IRUSR|S_IWUSR|S_IXUSR);
	copia_ricorsiva(argv[1],destination);

}


void copia_ricorsiva(char* source, char* destination){
	char fullname1[N],fullname2[N];
	struct stat buf;
	DIR *dp;
	struct dirent *dirp;
	char buff[N];
	int fr,fw,nRead;

	if(stat(source,&buf)<0){
		fprintf(stderr,"errore nel path\n");
		exit(1);
	}
	if(S_ISDIR(buf.st_mode)){

		if((dp=opendir(source))==NULL){
			fprintf(stderr, "errore nell'apertura cartella %s", source);
			exit(1);
		}
		while((dirp=readdir(dp))!=NULL){
			sprintf(fullname1,"%s/%s",source,dirp->d_name);
			//aggiungo cartella al path
			sprintf(fullname2,"%s/%s",destination,dirp->d_name);
			if(stat(fullname1,&buf)<0){
				fprintf(stderr,"errore nel path\n");
				exit(1);
			}
			
			if(S_ISDIR(buf.st_mode)){
				if(strcmp(dirp->d_name,".")!=0 && strcmp(dirp->d_name,"..")!=0){
					
					if(mkdir(fullname2,S_IRUSR|S_IWUSR|S_IXUSR)==-1)
						fprintf(stderr, "errore nella creazione del direttorio %s\n", source);
					//ricorro
					copia_ricorsiva(fullname1,fullname2);
				}
			}else{
				fr=open(fullname1,O_RDONLY);
				fw=open(fullname2,O_WRONLY|O_CREAT|O_TRUNC,S_IRUSR|S_IWUSR);

				if(fr==-1 || fw==-1){
					fprintf(stderr, "errore file\n");
					//exit(1);
				}
				 while((nRead=read(fr,buff,N))>0){
     
      				write(fw,buff,nRead);
  				}
    			close(fr);
   				close(fw);
			}
		}
		closedir(dp);
	}
}
