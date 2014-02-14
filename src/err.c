#include <stdio.h>
#include <stdlib.h>

void err_sys(const char *str)
{
	perror(str);
	exit(1);
}
