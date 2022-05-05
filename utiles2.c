#include "header.h"

void    philo_mouve(int time)
{
	long long	start;

	start = gettime();
	while (1)
	{
		if ((gettime() - start) >= time)
			break ;
	}
}

int		check_death(t_philosofers *philo)
{
	pthread_mutex_lock(&philo->data->dead);
	if ((gettime() - philo->start_time) > philo->data->time_to_die)
	{
		philo->data->alive = 0;
		printf("%lld %d %s\n",gettime() - philo->start_time, philo->philo_number + 1, "died");
		exit(0);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->dead);
	return (0);
}

// void	philo_dead(t_philosofers *philo)
// {
// }