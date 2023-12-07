#ifndef IOCTL_NEW_H
#define IOCTL_NEW_H

#define WR_PID _IOW('a','a',int32_t*)
#define RD_TASK_CPUTIME _IOR('a','b', struct tasknew_cputime*)
#define RD_INODE _IOR('a','c',struct inode_new*)

typedef uint64_t u64;
typedef __kernel_uid32_t uid_t;
typedef __kernel_gid32_t gid_t;

struct tasknew_cputime{
	u64 stime;
	u64 utime;
};

struct inode_new{
	uid_t i_uid;
	gid_t i_gid;
};

#endif
