#include<stdio.h>
#include<unistd.h>
#include<linux/unistd.h>
#include<linux/time.h>
int main(){
	int y = 2;
	struct timespec current_time;
	y = syscall(326,&current_time);
	printf("syscall return value :%d\n",y);//negative value of y will indicate a failure

	long nanoseconds = (long)(current_time.tv_nsec);
	printf("seconds is %d \n",current_time.tv_sec);
	printf("nanoseconds = %lu \n",current_time.tv_nsec);

	return 0;
}
