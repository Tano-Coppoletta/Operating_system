#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>



int
main (int argc, char *argv[]){
  int n;
  int *vet;
  int i;
  pid_t pid[2];

  n = atoi (argv[1]);

  vet = (int *)malloc(n * sizeof(int));
  if (vet == NULL) {
    printf("Allocatin Error.\n");
    exit(1);
  }
  printf("Binary Numbers:\n");
  for(i=0;i<n;i++){
  	if((pid[0]=fork())){
  		//padre che aspetta
  	
  		
  		if((pid[1]=fork())){
  			
  			//padre che aspetta
  			//waitpid(pid[1],(int*)NULL,0);
  			//waitpid(pid[0],(int*)NULL,0);
  			 waitpid(pid[1],(int*)NULL,NULL);
  			 waitpid(pid[0],(int*)NULL,NULL);
  			 exit(1);
				
  		}else{
			vet[i]=0;	

				
  		}

  	}else{
  		vet[i]=1;
  		
  	}

  }

  for(i=0;i<n;i++){
  	fprintf(stdout, "%d", vet[i]);
  }
  fprintf(stdout, "\n");

  
 
  free(vet);

  return 0;
}
