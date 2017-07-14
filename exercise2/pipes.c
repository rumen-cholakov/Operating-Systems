/**
#Simulate the work of cat <input1>|grep <input2>|wc -l
*/
#include <unistd.h>
#include <sys/types.h>
#include <err.h>
#include <stdlib.h>
#include <sys/wait.h>

int main (int argc, char* argv[])
{
	if (argc != 3) {
		errx(1, "invalid number of arguments");
	}
	const int R = 0;
	const int W = 1;
	int fd[2];
	pipe(fd);
	pid_t child;
	if ((child = fork()) == -1) {
		err(1, "fork grep");
	}
	if(child > 0){
		close(fd[R]);
                if (dup2(fd[W], 1) == -1) {
                        err(1, "dup2 cat");
                }
                if (execlp("cat", "cat", argv[1], NULL) == -1) {
                        err(1, "exec cat");
                }
	}

	if (child == 0) {
		close(fd[W]);
		if (dup2(fd[R], 0) == -1) {
			err(1, "dup2 grep");
		}
		int fd2[2];
		pipe(fd2);
		pid_t grandchild;
		if ((grandchild = fork()) == -1) {
        	        err(1, "fork grep");
	        }
		if(grandchild > 0){
                	close(fd2[R]);
                	if (dup2(fd2[W], 1) == -1) {
                        	err(1, "dup2 grep");
                	}
                	if (execlp("grep", "grep", argv[2], NULL) == -1) {
                        	err(1, "exec grep");
                	}
        	}
		if(grandchild == 0){
			close(fd[R]);
			close(fd2[W]);
			if (dup2(fd2[R], 0) == -1){
        	                err(1, "dup2 wc");
	                }
			if (execlp("wc", "wc", "-l", NULL) == -1) {
                                err(1, "exec wc");
                        }

		}
		wait(NULL);
	}
	wait(NULL);
	exit(0);
}
