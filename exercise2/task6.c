/**
* Да се напише програма на С, която получава като параметър команда (без параметри) 
* и при успешното ѝ изпълнение, извежда на стандартния изход името на командата.
*/#include <err.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main (int argc, char * argv[])
{
	if (argc != 2){
		errx(1, "Invalid parameters!");
	}

	int pid = fork();
	if(pid > 0){
		int status;
		wait(&status);
		if( WIFEXITED(status) )
			printf("%s", argv[1]);
	}
	else if( pid == 0){
		if ( -1 == execlp(argv[1], argv[1], (char*) NULL) ){
			errx(1,"Failed exec()");
		}
	}
	exit(0);
}
