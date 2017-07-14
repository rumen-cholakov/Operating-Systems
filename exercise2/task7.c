/**
* Да се напише програма на С, която получава като параметри три команди (без параметри),
* изпълнява ги последователно, като изчаква края на всяка и извежда на стандартния изход 
* номера на завършилия процес, както и неговия код на завършване.
*/
#include <err.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main (int argc, char * argv[])
{
	if (argc != 4){
		errx(1, "Invalid parameters!");
	}
	int pid, i = 1;
	for(; i < argc; ++i) {
		pid = fork();
		if( pid > 0 ) {
			int status;
			wait(&status);
			if( WIFEXITED(status) ) {
				printf("my pid is: %d\n%s exit status: %d\n", getpid(), argv[i], status);
			}
		}
		else if( pid == 0 ) {
			break;
			if ( -1 == execlp(argv[i], argv[1], (char*) NULL) ){
				errx(1,"Failed exec()");
			}
		}
	}
	exit(0);
}
