#include <asm-generic/errno-base.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>
#include <error.h>
#include <string.h>


extern int errno;

int main (int argc, char** argv){
    FILE* pf;
    int errnum;
    char zero_file[1024] ;
    char* reading_file_message="Reading file is impossible: %s\n";

    if (argc > 2){
        errno = E2BIG;
        perror("Too many arguments");
        return errno;
    }

    pf = fopen ("unexist.txt", "rb");
	
    if (pf == NULL) {
//        errnum = errno;
//        fprintf(stderr, "Value of errno: %d\n", errno);
        perror("Can't open the file");
//        fprintf(stderr, "Error opening file: %s\n", strerror( errnum ));
//        strerror_r(errno, zero_file, sizeof(zero_file));
//        printf(reading_file_message, zero_file);
    } 
    else {
        fclose (pf);
   }

	return 0;
}
