#include<stdio.h>
#include<unistd.h>
#include<linux/unistd.h>
#include<sys/time.h>
#include <fcntl.h>
#include <stdlib.h>

#define MAX_LENGTH 255
#define N 20


int main(){
	struct timeval gtodTimes[N];
	char* procClockTimes[N];
	char bytes_read[N];
	int fd;
	
	fd = open("/dev/mytime", O_RDONLY);
	printf("here 1\n");
	/* check for errors HERE */
	if( fd == -1){
		printf("Open file fail");
		return 0;
	}
	
	*procClockTimes = malloc(N * sizeof(char*));
	
	for(int i = 0; i < N; i++){
		procClockTimes[i] = malloc(MAX_LENGTH * sizeof(char));
	}
	
	printf("here 2\n");
	for(int i=0; i < N; i++)
	{
		gettimeofday(&gtodTimes[i], 0);
		//printf("i = %d\n",i);
		
		if(read(fd, procClockTimes[i], MAX_LENGTH) == -1){
			printf("read file fail\n");
			return 0;
		}
		/* check for errors HERE */
	}
	printf("here 3\n");
	close(fd);

	for(int i=0; i < N; i++) {
		printf("gtodTimes =          %ld %ld \n%s \n\n", gtodTimes[i].tv_sec,gtodTimes[i].tv_usec, procClockTimes[i]);
		/* fix the output format appropriately in the above line */
	}



	return 0;
}
