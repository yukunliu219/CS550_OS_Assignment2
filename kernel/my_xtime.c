#include  <linux/linkage.h>
#include  <linux/export.h>
#include  <linux/time.h>
#include  <asm/uaccess.h>
#include  <linux/printk.h>
#include  <linux/slab.h>
#include  <linux/kernel.h>
#include  <linux/syscalls.h> 


asmlinkage int sys_my_xtime(struct timespec *current_time){
	if(access_ok(VERIFY_WRITE,current_time,sizeof(current_time)) != 0){
		struct timespec kenrnel_time = current_kernel_time();

		if(copy_to_user(current_time,&kenrnel_time,sizeof(struct timespec)) != 0 ){
			return -1;
		}

		//time_t time_second = (time_t)(&current_time->tv_sec);
		long nanoseconds = (long)(kenrnel_time.tv_nsec);
		//clock_gettime(CLOCK_REALTIME, &ts);
		//time(&time_second);
		
		printk(KERN_ALERT "seconds is %d \n",kenrnel_time.tv_sec);
		printk(KERN_ALERT "nanoseconds is %lu\n",nanoseconds);
		return 0;
	}
	else{
		return 	EFAULT;
	}
	
}
EXPORT_SYMBOL(sys_my_xtime);
