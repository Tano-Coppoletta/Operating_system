#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc,char* argv[]){
	int i,j,n1,n2;
	int fp;

	fp=open(argv[1],O_RDWR);

	if(fp==-1){
		fprintf(stderr, "Errore file\n");
		exit(1);
	}

	for (i=0; i<9; i++) {
  		for (j=0; j<9-i; j++) {
  			if(fork()>0){
  				wait((int*)0);
  			}else{
  				//mi sposto sul file
				lseek(fp,j*sizeof(int),SEEK_SET);
				//leggo elemento j
				read(fp,&n1,sizeof(int));
				//mi sposto su j+1 opzionale:dopo la read si dovrebbe spostare solo
				lseek(fp,(j+1)*sizeof(int),SEEK_SET);
				//leggo elemento j+1
				read(fp,&n2,sizeof(int));
   		 		if (n1 > n2) {
       				//mi sposto sul file
					lseek(fp,j*sizeof(int),SEEK_SET);
					//leggo elemento j
					write(fp,&n2,sizeof(int));
					//mi sposto su j+1,opzionale
					lseek(fp,(j+1)*sizeof(int),SEEK_SET);
					//leggo elemento j+1
					write(fp,&n1,sizeof(int));
    			}
    			exit(2);
    		}
  		}
	}

}
