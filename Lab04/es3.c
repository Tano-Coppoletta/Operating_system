#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>


int main(int argc,char* argv[]){
	char comando[124]="\0";
	FILE *fp;
	char buff[124],cmd[124];
	char **matrice,*temp;	
	int i=0;


	matrice=malloc(124*sizeof(char*));
	for(i=0;i<124;i++){
		matrice[i]=malloc(12*sizeof(char));
	}
	i=0;
	//apro file
	fp=fopen(argv[1],"r");
	if(fp==NULL){
		fprintf(stderr,"errore file\n");
		exit(1);
	}
	while(fscanf(fp,"%s",buff)>0){

		if(strcmp(buff,"end")!=0){
			//compilo stringa per system
			strcat(comando,buff);
			strcat(comando," ");
			//compilo matrice per exec
			strcpy(matrice[i],buff);
			i++;
			//fprintf(stdout,"MATRICE %s\n",matrice[i]);
		}else{
			
			strcpy(buff,"\0");
			//scrivo in cmd il nome del comando per la exec
			sscanf(comando,"%s",cmd);
			
			//aggiungo null alla fine della matrice
			temp=matrice[i];
			matrice[i]=(char*) 0;
			
			if(fork()){
			//uso system
			//fprintf(stdout,"SYSTEM\n");
			//system(comando);
			
			sleep(3);
			matrice[i]=temp;
			i=0;
			strcpy(comando,"\0");
			
			}else{
			//uso exec
			/*fprintf(stdout,"COMANDO %s\n",cmd,i);
			for(int j=0;j<4;j++){
				fprintf(stdout,"%s ",matrice[j]);
				
			}
			fprintf(stdout, "\n");*/
			execvp(cmd,matrice);
			exit(1);
			}
		}
	}
	fclose(fp);


}
