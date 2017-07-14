/**
* Реализирайте команда cp, работеща с два аргумента, подадени като входни параметри.
*/
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <err.h>
int main (int argc, char* argv[])
{
	if (argc != 3) {
		errx(1, "err");
	}

	int fd1;
	fd1 = open(argv[1], O_RDONLY);
	if (fd1 == -1) {
		errx(2, "%s", argv[1]);
	}

	int fd2;
	fd2 = open(argv[2], O_WRONLY);
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
	exit(0);
}
