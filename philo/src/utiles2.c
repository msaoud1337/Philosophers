/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaoud <msaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 13:41:33 by msaoud            #+#    #+#             */
/*   Updated: 2022/05/15 12:41:22 by msaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	ft_arv5(t_data *data)
{
	if (data->arc == 6)
	{
		if (data->all_ate >= (data->each_time_toeat * data->all_philo))
		{
			pthread_mutex_lock(&data->print);
			printf("each philosopher ate at least %d", data->each_time_toeat);	
			return (0);
		}
	}
	return (1);
}

void	checkingfordeath(void	*arg)
{
	t_data	*data;
	int		i;

	data = arg;
	while (1)
	{
		i = -1;
		while (++i < data->all_philo && data->alive)
		{
			if (!ft_arv5(data))
				return ;
			if (data->philo_tab[i].is_eating == 0)
			{
				if (gettime() - data->philo_tab[i].last_meal
					> data->time_to_die)
				{
					pthread_mutex_lock(&data->print);
					printf("%lld %d %s\n", gettime() - data->start_time,
						data->philo_tab[i].philo_number + 1, "died");
					return ;
				}
			}
		}
		usleep(1000);
	}
}

int	ft_mutex_init(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->all_philo)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
			return (0);
	}
	if (pthread_mutex_init(&data->print, NULL))
		return (0);
	if (pthread_mutex_init(&data->dead, NULL))
		return (0);
	return (1);
}

int	pars(int arc, char **arv, t_data *data)
{
	data->all_philo = ft_atoi(arv[1]);
	data->time_to_die = ft_atoi(arv[2]);
	data->time_to_eat = ft_atoi(arv[3]);
	data->time_to_sleep = ft_atoi(arv[4]);
	data->philo_tab = malloc(sizeof(t_philosofers) * data->all_philo);
	if (!data->philo_tab)
		return (0);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->all_philo);
	if (!data->forks)
		return (0);
	if (data->all_philo < 1 || data->time_to_die < 60
		|| data->time_to_eat < 60 || data->time_to_sleep < 60)
		return (0);
	data->each_time_toeat = 0;
	if (arv[5])
		data->each_time_toeat = ft_atoi(arv[5]);
	data->start_time = gettime();
	data->alive = 1;
	data->all_ate = 0;
	data->arc = arc;
	return (1);
}

void	ft_free(t_data	*data, int tmp)
{
	int	i;

	i = -1;
	if (tmp == 1)
	{
		while (++i < data->all_philo)
			pthread_mutex_destroy(&data->forks[i]);
	}
	free(data->forks);
	free(data->philo_tab);
}
