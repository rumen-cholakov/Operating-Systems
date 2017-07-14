/**
* Реализирайте команда cp, работеща с произволен брой подадени входни параметри
*/#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <err.h>
#include <string.h>

int main (int argc, char* argv[])
{
	if(argc < 3){
		errx(1,"Not enough arguments");
	}

	struct stat stat_buff;
	stat(argv[argc-1],&stat_buff);
	if (S_ISDIR(stat_buff.st_mode)) {
		int i;
		char * path;
		size_t dir_path_len = strlen(argv[argc - 1]);
		for(i = 1; i < argc - 1; ++i){
			size_t path_len = strlen(argv[i]) + dir_path_len + 2;
			path = (char *) malloc(path_len);
			if(!path){
				err(1,"Problem with allocation");
			}
			strcpy(path,argv[argc - 1]);
			strcat(path,"/");
			strcat(path,argv[i]);
			int fd1;
        		fd1 = open(argv[i], O_RDONLY);
       	 		if (fd1 == -1) {
        	        	errx(2, "%s", argv[1]);
	        	}

	        int fd2;
			struct stat stat_buff_file;
			stat(argv[i],&stat_buff_file);
        		fd2 = open(path, O_CREAT|O_WRONLY,stat_buff_file.st_mode);
	        	if (fd2 == -1) {
        	        	close(fd1);
                		errx(3, "%s", argv[2]);
        		}

	        	char c[4096];
        		ssize_t read_size;

        		while ((read_size = read(fd1, &c, sizeof(c))) > 0) {
                		if (write(fd2, &c, read_size) != read_size ) {
                        		close(fd1);
	                        	close(fd2);
        	                	errx(1, "Error while writing");
  	             		}
        		}

        		close(fd1);
	        	close(fd2);

			free(path);
		}
	}
	exit(0);
}
