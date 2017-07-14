// template
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <errno.h>
#include <err.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char* argv[]) {

	if(argc != 3){
		errx(1, "Incorrect number of arguments");
    }
    
	int fd1 = open(argv[1], O_RDONLY), fd2;

	if(fd1 == -1){
		errx(2, "File reading error");
    }
    
	uint16_t bm = 0;
	uint32_t fileSize;
	uint32_t pixelArrayPosition;
	int32_t width, height;
	uint16_t bitsPerPixel;
	uint32_t compr;

//Reading the needed information and checking if the input file follows the specifications
//and terminating the program if it doesn't
	lseek(fd1, 0, SEEK_SET);
	read(fd1, &bm, 2);
	if(bm != (0x42 | 0x4d << 8)){
	    close(fd1);
	    errx(3, "File format is invalid");
	}
	
	lseek(fd1, 18, SEEK_SET);
	read(fd1, &width, 4);
	
	lseek(fd1, 22, SEEK_SET);
	read(fd1, &height, 4);
	if(width < 20 || height < 20){
	    close(fd1);
	    errx(3, "File format is invalid");
	}

	lseek(fd1, 28, SEEK_SET);
	read(fd1, &bitsPerPixel, 2);
	if(bitsPerPixel != 24){
	    close(fd1);
	    errx(3, "File format is invalid");
	}

	lseek(fd1, 30, SEEK_SET);
	read(fd1, &compr, 4);
	if(compr != 0){
	    close(fd1);
	    errx(3, "File format is invalid");
	}

	lseek(fd1, 2, SEEK_SET);
	read(fd1, &fileSize, 4);

	lseek(fd1, 10, SEEK_SET);
	read(fd1, &pixelArrayPosition, 4);

//Creat an output file
	fd2 = open(argv[2], O_CREAT | O_WRONLY);
	if(fd2 == -1){
	    close(fd1);
		errx(4, "File writing error");
    }
    
//Allocate space for array containing the output file info
	unsigned char* pixelarr;
	pixelarr = (unsigned char*) malloc(fileSize);

	if(fileSize != 0 && pixelarr == NULL){
	    close(fd1);
		errx(5, "Allocating failed");
    }
    
	lseek(fd1, 0, SEEK_SET);
	read(fd1, pixelarr, fileSize);

//Find the needed padding
	char padding = 0;

	switch((3 * width) % 4) {
	case 1:
		padding = 3;
		break;
	case 2:
		padding = 2;
		break;
	case 3:
		padding = 1;
		break;
	}

//Setting the needed value for each pixel
	for(int i = 0; i < height; i++) {
		for(int j = 0; j < width * 3; j++) {
			if((j == 4 || j == width - 5) && (i >= 4 && i <= height - 5)){
				pixelarr[pixelArrayPosition + i * (3 * width + padding) + j * 3 + 0] = 255;
				pixelarr[pixelArrayPosition + i * (3 * width + padding) + j * 3 + 1] = 0;
				pixelarr[pixelArrayPosition + i * (3 * width + padding) + j * 3 + 2] = 0;
			}
			if(i == 4 && (j >= 4 && j <= height - 5)) {
				pixelarr[pixelArrayPosition + i * (3 * width + padding) + j * 3 + 0] = 0;
				pixelarr[pixelArrayPosition + i * (3 * width + padding) + j * 3 + 1] = 0;
				pixelarr[pixelArrayPosition + i * (3 * width + padding) + j * 3 + 2] = 255;
			}
		    if((i == height - 5) && (j >= 4 && j <= height - 5)) {
        	    pixelarr[pixelArrayPosition + i * (3 * width + padding) + j * 3 + 0] = 0;
			    pixelarr[pixelArrayPosition + i * (3 * width + padding) + j * 3 + 1] = 255;
        		pixelarr[pixelArrayPosition + i * (3 * width + padding) + j * 3 + 2] = 0;
		    }
		    if((j == 4 && i == 4) || (j == width - 5 && i == height - 5) || (j == 4 && i == height - 5) || (j == width - 5 && i == 4)){ 
		        pixelarr[pixelArrayPosition + i * (3 * width + padding) + j * 3 + 0] = 0;
				pixelarr[pixelArrayPosition + i * (3 * width + padding) + j * 3 + 1] = 0;
				pixelarr[pixelArrayPosition + i * (3 * width + padding) + j * 3 + 2] = 0;
		    }
		}
		
	}

//Putting content into the output file 
	write(fd2, pixelarr, fileSize);

	free(pixelarr);

	close(fd1);
	close(fd2);
	
	printf("Image was created successfully!\n");
	return 0;
}
