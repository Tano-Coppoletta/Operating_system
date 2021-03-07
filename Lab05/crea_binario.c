#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define N 10

int main(int argc,char* argv[]){
	int v[N]={2,1,6,3,7,4,8,5,9,0};
	FILE *fp;

	fp=fopen(argv[1],"w");

	if(fp==NULL)
		exit(1);

	fwrite(v,sizeof(int),N,fp);

	fclose(fp);
	return 0;
}
