#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>

long long	gettime()
{
	long long time;
	struct timeval	curr_time;

	gettimeofday(&curr_time, NULL);
	time = curr_time.tv_sec * 1000;
	time += curr_time.tv_usec / 1000;
	return (time);
}
