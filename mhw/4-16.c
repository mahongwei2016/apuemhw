#include "apue.h"
#include <fcntl.h>
int main(void)
{
	if(open("tempfile",O_CREAT|O_RDWR,0755)<0)
		err_sys("creat error");
	if(unlink("tempfile")<0)
		err_sys("unlink error");
	printf("file unlink\n");
	sleep(10);
	printf("done\n");
	exit(0);
}
