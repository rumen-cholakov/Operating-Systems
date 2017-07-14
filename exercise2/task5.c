/**
* Напишете програма, която приема точно 2 аргумента. Първият може да бъде само 
* `--min`, `--max` или `--print` (вижте `man 3 strcmp`). Вторият аргумент е двоичен файл,
* в който има записани цели неотрицателни двубайтови числа (`uint16_t` - вижте `man stdint.h`). Ако първият аргумент е:
*  - `--min` - програмата отпечатва кое е най-малкото число в двоичния файл.
*  - `--max` - програмата отпечатва кое е най-голямото число в двоичния файл.
*  - `--print` - програмата отпечатва на нов ред всяко число.
*/
#include <stdlib.h>
#include <err.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>



int main(int argc, char * argv[]){
	if(argc != 3 || !(0 == strcmp("--min",argv[1]) || 0 == strcmp("--max",argv[1]) || 0 == strcmp("--print",argv[1]))){
		errx(1,"Invaid parameters!");
	}

	int fd1 = open(argv[2], O_RDONLY);
       	if (fd1 == -1) {
              	errx(2, "Could not open %s", argv[2]);
       	}


	uint16_t readbuff;
	uint16_t min;
	uint16_t max;
	min = UINT16_MAX;
	max = 0;

	if(0 == strcmp("--min",argv[1])){
		while(read(fd1, &readbuff, sizeof(readbuff)) == sizeof(readbuff)){
			min = readbuff < min ? readbuff : min;
		}
		printf("min: %u\n", min);
		exit(0);
	}
	else if(0 == strcmp("--max",argv[1])){
                while(read(fd1, &readbuff, sizeof(readbuff)) == sizeof(readbuff)){
                        max = readbuff > max ? readbuff : max;
                }
                printf("max: %u\n", max);
                exit(0);
	}
	else if(0 == strcmp("--print",argv[1])){
                while(read(fd1, &readbuff, sizeof(readbuff)) == sizeof(readbuff)){
			printf("%u\n", readbuff);
                }
                exit(0);
        }

}
