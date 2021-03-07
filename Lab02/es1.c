#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#define N 1024

void leggi_direttorio(char *path);

int main(int argc, char* argv[]){
  if(argc!=2){
    printf("argomenti\n");
    return -1;
  }     
   leggi_direttorio(argv[1]);
   return 1;
}
  

void leggi_direttorio(char* path){
  char fullname[N];
  struct stat buf;
  DIR *dp;
  struct dirent *dirp;

  fprintf(stdout,"%s\n",path);
  if(stat(path,&buf)<0){
    fprintf(stderr,"Errore statistiche path\n");
   
  }
  if(S_ISDIR(buf.st_mode)){
    if((dp= opendir(path))==NULL){
      fprintf(stderr,"non riesco ad aprire la cartella\n");
      exit(1);
    }
    while((dirp=readdir(dp))!=NULL){
      fprintf(stdout,"%s\t",dirp->d_name);
    }
    closedir(dp);
    printf("\n");
    if(S_ISDIR(buf.st_mode)){
      if((dp=opendir(path))==NULL){
	  fprintf(stderr,"non si apre\n");
	  exit(1);
	  
	}
	while((dirp=readdir(dp))!=NULL){
	  sprintf(fullname,"%s/%s",path,dirp->d_name);
	  
	  
	  if(stat(fullname,&buf)==-1){
	    fprintf(stderr,"non ho statistiche\n");
	    break;
	  }
	  if(S_ISDIR(buf.st_mode)){
	    if(strcmp(dirp->d_name,".")!=0 && strcmp(dirp->d_name,"..")!=0){
	    
	      leggi_direttorio(fullname);
	    }
	  }
	 
	}
	closedir(dp);
    }
    
  }
  return;
  
}
