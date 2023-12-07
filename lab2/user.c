#include <sys/ioctl.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <linux/fs.h>
#include <malloc.h>
#include <sched.h>
#include <string.h>
#include <linux/ptrace.h>
#include <linux/types.h> 

#include "ioctl_new.h"

static void print_line(void){
	printf("________________\n");
}


int main(int argc, char *argv[]){
	int32_t pid = atoi(argv[1]);
	int fd;
	fd = open("/dev/mydevice", O_WRONLY);
	if(fd < 0){
		printf("Cannot open device\n");
		return 0;
	}
	struct tasknew_cputime cputime;
	struct inode_new inode;
	ioctl(fd,WR_PID,(int32_t*) &pid);
	printf("ioctl information from kernel\n\n");
	ioctl(fd,RD_TASK_CPUTIME, &cputime);
	printf("PID - %d\n", pid);
	printf("time spent in kernel mode - %lu\ntime spent in user mode - %lu\n", cputime.stime, cputime.utime);
	printf("user id - %u \ngroup id - %u\n", inode.i_uid, inode.i_gid);
	print_line();
	close(fd);
	return 0;
}
