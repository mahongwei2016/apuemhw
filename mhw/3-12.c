#include "apue.h"
#include <fcntl.h>
#include <unistd.h>
#ifdef printf_function
#define printf_function(); printf("%s begin\n",__FUNCTION__);
#else
#define printf_function(); 
#endif
void set_fl(int fd,int flags);
void clr_fl(int fd,int flags);
void printf_fl(int fd);
void set_fl(int fd,int flags)
{
	int val;
	printf_function();
	if((val=fcntl(fd,F_GETFL,0))<0)
		err_sys("fcntl F_GETEL error");
	val |=flags;
	if(fcntl(fd,F_SETFL,val)<0)
		err_sys("fcntl f_SETFL error");
}
void clr_fl(int fd,int flags)
{
	int val;
	printf_function();
	if((val=fcntl(fd,F_GETFL,0))<0)
		err_sys("fcntl F_GETEL error");
	val &=~flags;
	if(fcntl(fd,F_SETFL,val)<0)
		err_sys("fcntl f_SETFL error");
}
void printf_fl(int fd)
{
	int val;
	printf_function();
	if((val=fcntl(fd,F_GETFL,0))<0)
		err_sys("fcntl error for fd:%d",fd);
	switch(val&O_ACCMODE){
	case O_RDONLY:
		printf("read only");
		break;
	case O_WRONLY:
		printf("write only");
		break;
	case O_RDWR:
		printf("read write");
		break;
	default:
		err_dump("unknown access mode1");
	}
	if(val & O_APPEND)
		printf(",append");
	if(val & O_NONBLOCK)
		printf(",nonblocking");
	if(val & O_SYNC)
		printf(",synchronous writes");
	printf("\n");
}
int main(int argc,char* argv[])
{
	int fd;
	printf("time :%s\n",__TIME__);
	unlink("tmp");
	if(fd=open("tmp",O_RDWR|O_CREAT,0666)<0)
		err_sys("open tmp error");
	printf_fl(fd);
	set_fl(fd,O_APPEND|O_SYNC|O_NONBLOCK);
	printf_fl(fd);
	clr_fl(fd,O_APPEND|O_SYNC|O_NONBLOCK);
	printf_fl(fd);
	close(fd);
	unlink("tmp");
	exit(0);
}
