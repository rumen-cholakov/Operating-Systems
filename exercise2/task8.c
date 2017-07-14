/**
* Да се напише програма на С, която получава като параметър име на файл. 
* Създава процес син, който записва стринга `foobar` във файла (ако не съществува,
* го създава, в противен случай го занулява), след което процеса родител прочита записаното 
* във файла съдържание и го извежда на стандартния изход, добавяйки по един интервал между всеки два символа.
*/
#include <err.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>

int main (int argc, char * argv[])
{
	if (argc != 2){
		errx(1, "Invalid parameters!");
	}
	int child = fork();
	if (child == 0){
		int fdw = open(argv[1], O_CREAT|O_TRUNC|O_WRONLY,S_IRWXU);
		write(fdw, "foobar", 7);
		close(fdw);
	}
	else{
		wait(NULL);
		int fdr = open(argv[1], O_RDONLY);
		char two[2];
		while(read(fdr, two, 2) >= 1){
			write(1, two, 2);
			two[0] = ' ';
			two[1] = ' ';
			write(1, &two[0], 1);

		}
		printf("\n");
		close(fdr);
	}
	exit(0);
}
