#include "header_bonus.h"

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

long long	gettime(void)
{
	long long		time;
	struct timeval	curr_time;

	gettimeofday(&curr_time, NULL);
	time = curr_time.tv_sec * 1000;
	time += curr_time.tv_usec / 1000;
	return (time);
}


int	pars(int arc, char **arv, t_data *data)
{
	data->all_philo = ft_atoi(arv[1]);
	data->time_to_die = ft_atoi(arv[2]);
	data->time_to_eat = ft_atoi(arv[3]);
	data->time_to_sleep = ft_atoi(arv[4]);
	data->forks = malloc(sizeof(sem_t) * data->all_philo);
	if (!data->forks)
		return (0);
	data->philo_tab = malloc(sizeof(t_philosofers) * data->all_philo);
	if (!data->philo_tab)
		return (0);
	if (data->all_philo < 1 || data->time_to_die < 60
		|| data->time_to_eat < 60 || data->time_to_sleep < 60)
		return (0);
	data->each_time_toeat = 0;
	if (arv[5])
		data->each_time_toeat = ft_atoi(arv[5]);
	data->alive = 1;
	data->all_ate = 0;
	data->arc = arc;
	data->pid_tab = malloc(sizeof(int) * data->all_philo);
	if (!data->pid_tab)
		return (0);
	return (1);
}
