/**
* Реализирайте команда cat, работеща с произволен брой подадени входни параметри.
*/
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <err.h>
int main (int argc, char* argv[])
{
	if (argc < 2) {
		errx(1, "err");
	}

	int fd, i;
	char c[4096];
	ssize_t read_size;

	for(i = 1; i < argc; ++i) {
		fd = open(argv[1], O_RDONLY);

		if (fd == -1) {
			errx(2, "%s", argv[1]);
		}

		while ((read_size = read(fd, &c, sizeof(c))) > 0) {
			if (write(1, &c, read_size) != read_size ) {
				close(fd);
				errx(1, "Error while writing");
			}
		}
		close(fd);
	}
	exit(0);
}
