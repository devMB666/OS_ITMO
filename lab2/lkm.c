#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/ioctl.h>
#include <linux/sched.h>
#include <linux/time.h>
#include <linux/pid.h>

#include "ioctl_new.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mikhail Bulukhto");
MODULE_DESCRIPTION("LKM ioctl, task_cputime, inode");
MODULE_VERSION("0.01");

#define MYMAJOR 90

int pid = 0;
int retval;

static long my_ioctl(struct file *file, unsigned int cmd, unsigned long arg){
	struct tasknew_cputime cputime;
	struct task_struct* task;
	struct inode* inode_o;
	struct inode_new inode; 
	
	switch(cmd){
		case WR_PID: //write pid number
			if(copy_from_user(&pid, (int*)arg, sizeof(pid))) pr_err("DATA WRITE ERROR!\n");
			pr_info("PID = %d\n", pid);
			break;
			
		case RD_TASK_CPUTIME: //read values from task_cputime and inode
			task = get_pid_task(find_get_pid(pid), PIDTYPE_PID); 
			if(task != NULL){
				cputime.utime = task->utime;
				cputime.stime = task->stime;
				inode_o = file->f_inode;
				inode.i_uid = i_uid_read(inode_o);
				inode.i_gid = i_gid_read(inode_o);
				printk("user - %lld , stime - %lld\n", cputime.utime, cputime.stime);
				printk("uid - %u\n gid - %u\n",inode.i_uid, inode.i_gid);
				break;
			}
			else printk("Error! no avaliable tasks.");
	}
	return 0;
}

static const struct file_operations fops = {
	.owner = THIS_MODULE,
	.unlocked_ioctl = my_ioctl,
};

static int __init lkm_init(void) {
	printk(KERN_INFO "Core mode is started\n");
	retval = register_chrdev(MYMAJOR,"own_driver",&fops);
	
	if(retval == 0){
		printk("own_driver dev number Major:%d , Minor:%d\n",MYMAJOR,0);
	}
	else if(retval > 0){
		printk("own_driver dev number Major:%d , Minor:%d\n", retval >> 20, retval&0xfffff);
	}
	else{
		printk("Couldn't register dev number\n");
	}
	return 0;
}
static void __exit lkm_exit(void) {
	unregister_chrdev(MYMAJOR, "own_driver");
	printk(KERN_INFO "Core mode is finished\n");
}

module_init(lkm_init);
module_exit(lkm_exit);
