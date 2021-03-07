#define N 50
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char* argv[]){
    int fp;
    int fo;
    char s[N];
    int nRead;

    fp=open(argv[1],O_RDONLY);
    fo=open(argv[2],O_WRONLY|O_CREAT|O_TRUNC,S_IRUSR|S_IWUSR);

    if(fp==-1 || fo==-1)
	exit(1);
    
	  
    while((nRead=read(fp,s,N))>0){
     
      write(fo,s,nRead);
    }
    close(fp);
    close(fo);
    return 0;
}
