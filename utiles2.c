/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaoud <msaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 13:41:33 by msaoud            #+#    #+#             */
/*   Updated: 2022/05/06 16:19:35 by msaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	philo_mouve(int time)
{
	long long	start;

	start = gettime();
	while (1)
	{
		if ((gettime() - start) >= time)
			break ;
	}
}

void	ft_arv5(t_data *data)
{
	if (data->arc == 6)
	{
		if (data->all_ate == (data->each_time_toeat * data->all_philo))
		{
			printf("data->all_ate %d\n", data->all_ate);
			pthread_mutex_lock(&data->dead);
			pthread_mutex_lock(&data->print);
			printf("each philosopher ate at least %d", data->each_time_toeat);
			exit(0);
			pthread_mutex_unlock(&data->dead);
			pthread_mutex_unlock(&data->print);
		}
	}
}

void	*checkingfordeath(void	*arg)
{
	t_data	*data;
	int		i;

	i = -1;
	data = arg;
	while (1)
	{
		i = -1;
		while (++i < data->all_philo)
		{
			ft_arv5(data);
			if (gettime() - data->philo_tab[i].last_meal > data->time_to_die)
			{
				pthread_mutex_lock(&data->dead);
				pthread_mutex_lock(&data->print);
				printf("%lld %d %s\n", gettime() - data->start_time,
					data->philo_tab[i].philo_number + 1, "died");
				exit(0);
				pthread_mutex_unlock(&data->dead);
				pthread_mutex_unlock(&data->print);
			}
		}
	}
	return (0);
}

void	ft_mutex_init(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->all_philo)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
			ft_error(4);
	}
	if (pthread_mutex_init(&data->print, NULL))
		ft_error(4);
	if (pthread_mutex_init(&data->dead, NULL))
		ft_error(4);
}

void	pars(int arc, char **arv, t_data *data)
{
	data->all_philo = ft_atoi(arv[1]);
	data->time_to_die = ft_atoi(arv[2]);
	data->time_to_eat = ft_atoi(arv[3]);
	data->time_to_sleep = ft_atoi(arv[4]);
	data->each_time_toeat = 0;
	if (arv[5])
		data->each_time_toeat = ft_atoi(arv[5]);
	data->philo_tab = malloc(sizeof(t_philosofers) * data->all_philo);
	if (!data->philo_tab)
		ft_error(1);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->all_philo);
	if (!data->forks)
		ft_error(1);
	data->start_time = gettime();
	data->alive = 1;
	data->all_ate = 0;
	data->arc = arc;
}
