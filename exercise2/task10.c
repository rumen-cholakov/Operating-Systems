/**
* Да се напише програма на C, която получава като командни параметри две команди (без параметри). 
* Изпълнява ги едновременно и извежда на стандартния изход номера на процеса на първата завършила успешно.
*/#include <err.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <signal.h>
int main (int argc, char * argv[])
{
	if (argc != 3){
		errx(1, "Invalid parameters!");
	}

	int child1 = fork();
	if (child1 == 0){
		execlp(argv[1], argv[1], NULL);
	}

	int child2 = fork();
	if (child2 == 0){
		execlp(argv[2], argv[2], NULL);
	}

	if(child1 != 0 && child2 !=0){
		int pid, status;
		pid = waitpid(-1, &status, 0);
		if(WIFEXITED(status)){
			printf("%d\n",pid);
		}
		wait(&status);
	}

	exit(0);
}
