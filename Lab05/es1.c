#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>



int main(int argc,char * argv[]){
	int n;

	while(fscanf(stdin,"%d ",&n)!=EOF){
		
		if(n!=0){
			if((n%2)==0){
				fprintf(stdout,"STDOUT:%d\n",n);
			}else{
				fprintf(stderr,"STDERR:%d\n",n);
			}
		}else{
			return 0;
		}
	}
}
