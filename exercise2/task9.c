/**
* Да се напише програма на C, която получава като параметри от команден ред две команди
* (без параметри) и име на файл в текущата директория. Ако файлът не съществува, го създава.
* Програмата изпълнява командите последователно, по реда на подаването им. 
* Ако първата команда завърши успешно, програмата добавя нейното име към съдържанието на файла,
* подаден като команден параметър. Ако командата завърши неуспешно, 
* програмата уведомява потребителя чрез подходящо съобщение.
*/#include <err.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>

int main (int argc, char * argv[])
{
	if (argc != 4){
		errx(1, "Invalid parameters!");
	}
	int child = fork();
	int fdw = open(argv[3], O_CREAT|O_WRONLY,S_IRWXU);

	if (child == 0){
		execlp(argv[1], argv[1], NULL);

	}
	else{
		int status;
		wait(&status);
		if(WIFEXITED(status)){
			write(fdw, argv[1], strlen(argv[1]));
		}
		else{
			write(fdw, "The first command did not exit normaly", strlen("The first command did not exit normaly"));
		}
		write(fdw, "\n", 2);

		child = fork();

        	if (child == 0){
                	execlp(argv[2], argv[2], NULL);
        	}
        	else{
                	wait(&status);
                	if(WIFEXITED(status)){
                        	write(fdw, argv[2], strlen(argv[2]));
                	}
        	        else{
				write(fdw, "The second command did not exit normaly", strlen("The second command did not exit normaly"));
			}
			write(fdw, "\n", 2);
	        }

	}
	close(fdw);

	exit(0);
}
