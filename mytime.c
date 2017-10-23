#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <asm/uaccess.h>
#include <linux/fs.h>


#define DEVICE_NAME "mytime"
#define buffer_size 255

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Yukun");

static int major_number;
static int device_is_open = 0;
char result[buffer_size];

int __init init_my_module(void);
void __exit exit_my_module(void);
static ssize_t mytime_read(struct file *, char *, size_t, loff_t *);
static ssize_t mytime_write(struct file *, const char *, size_t, loff_t *);
static int mytime_open(struct inode *, struct file *);
static int mytime_release(struct inode *, struct file *);

static struct file_operations fops = {
  .read = mytime_read,
  .write = mytime_write,
  .open = mytime_open,
  .release = mytime_release
};

int __init init_my_time(void) {
  major_number = register_chrdev(0, DEVICE_NAME, &fops);
  if (major_number < 0) {
    printk(KERN_ALERT "Register failed, error %d.\n", major_number);
    return major_number;
  }

  printk(KERN_INFO "'mknod /dev/%s c %d 0'.\n", DEVICE_NAME, major_number);
  return 0;
}

void __exit exit_my_time(void) {
  unregister_chrdev(major_number, DEVICE_NAME);
}

static ssize_t mytime_read(struct file *filp, char *buffer, size_t length, loff_t *offset) {
  struct timespec kenrnel_time_current = current_kernel_time();
  struct  timespec kenrnel_time_getnstimeofday;
  getnstimeofday(&kenrnel_time_getnstimeofday);
  
  sprintf(result, "current_kernel_time= %ld %lu\ngetnstimeofday =     %ld %lu ",
          kenrnel_time_current.tv_sec, 
          kenrnel_time_current.tv_nsec,
          kenrnel_time_getnstimeofday.tv_sec,
          kenrnel_time_getnstimeofday.tv_nsec);
  
  printk(KERN_INFO "result = %s \n", result);
  length = sizeof(result);
  
  if(access_ok(VERIFY_WRITE,buffer,sizeof(buffer)) != 0){ 
		if(copy_to_user(buffer,&result,length) != 0 ){
      printk(KERN_INFO "return -1\n");
			return -1;
		}
	}
   //printk(KERN_INFO "length = %d .\n", length);
  return length;
}

static ssize_t mytime_write(struct file *filp, const char *buff, size_t length, loff_t *offset) {
  printk(KERN_ALERT "mytime module open \n");
  return -EINVAL;
}

static int mytime_open(struct inode *inode, struct file *file) {
  printk(KERN_ALERT "mytime module open \n");
  if (device_is_open) {
    printk(KERN_ALERT "mytime module open busy\n");
    return -EBUSY;
  }
  device_is_open = 1;

  try_module_get(THIS_MODULE);
  return 0;
}

static int mytime_release(struct inode *inode, struct file *file) {
  device_is_open = 0;
  module_put(THIS_MODULE);
  printk(KERN_ALERT "mytime module release \n");
  return 0;
}

module_init(init_my_time);
module_exit(exit_my_time);








