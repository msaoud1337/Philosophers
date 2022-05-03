#include "header.h"

void	action(int philo_id, t_data *data)
{
	printf("%d %d %s",gettime - data->start_time, );

}
void	ft_error(int i)
{
	if (i == 0)
		printf("check arguments !!!\n");
	if (i == 1)
		printf("allocation failed !!!\n");
	if (i == 3)
		printf("thread creation failed !!!\n");
	if (i == 4)
		printf("mutex failed !!!\n");
	exit(0);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	signe;
	int	r;

	i = 0;
	r = 0;
	signe = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			signe = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		r = r * 10 + (str[i] - '0');
		i++;
	}
	return (r * signe);
}

long long	gettime()
{
	long long time;
	struct timeval	curr_time;

	gettimeofday(&curr_time, NULL);
	time = curr_time.tv_sec * 1000;
	time += curr_time.tv_usec / 1000;
	return (time);
}