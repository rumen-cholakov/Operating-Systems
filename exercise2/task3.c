/**
* Koпирайте файл /etc/passwd в текущата ви работна директория и променете разделителят на копирания файл от ":", на "?"
*/
#include <stdio.h>
#include <err.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int main (int argc, char* argv[])
{
	if (argc != 2) {
		errx(1, "err");
	}

	int fd;
	fd = open(argv[1], O_RDWR);
	if (fd == -1) {
		err(2, "%s", argv[1]);
	}

	char c, w = '?';
	ssize_t read_size;


	while ((read_size = read(fd, &c, sizeof(c))) > 0) {
		if (c == ':') {
			lseek(fd, -1, SEEK_CUR);
			write(fd, &w, 1);
		}
	}

	close(fd);

	exit(0);
}
