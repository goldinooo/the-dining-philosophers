#include "philo.h"
#include <sys/time.h>

int main(void)
{
	struct timeval tv; // a st
	gettimeofday(&tv, NULL);
	tv.tv_sec = tv.tv_sec * 1000 + tv.tv_usec / 1000; // convert to milliseconds
	printf("Seconds: %ld\n", tv.tv_sec);
	return (0);
}