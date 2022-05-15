/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaoud <msaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 16:22:56 by msaoud            #+#    #+#             */
/*   Updated: 2022/05/12 18:09:35 by msaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_bonus.h"

void	action(int philo_n, long long start, char *s, t_data *data)
{
	sem_wait(data->print);
	printf("%lld %d %s\n", gettime() - start, philo_n + 1, s);
	sem_post(data->print);
}

void	routine(t_philosofers *philo)
{
	t_data	*data;

	if (philo->philo_number % 2)
		usleep(10000);
	data = philo->data;
	while (1)
	{
		sem_wait(philo->data->forks);
		action(philo->philo_number, data->start_time, "has taken a fork", data);
		sem_wait(philo->data->forks);
		action(philo->philo_number, data->start_time, "has taken a fork", data);
		philo->is_eating = 1;
		action(philo->philo_number, data->start_time, "is eating", data);
		philo->last_meal = gettime();
		ft_usleep(philo->data->time_to_eat);
		philo->is_eating = 0;
		sem_post(philo->data->forks);
		sem_post(philo->data->forks);
		action(philo->philo_number, data->start_time, "is sleeping", data);
		ft_usleep(philo->data->time_to_sleep);
		action(philo->philo_number, data->start_time, "is thinking", data);
	}
}

void	routine1(t_philosofers *philo)
{
	int		i;
	t_data	*data;

	data = philo->data;
	i = -1;
	if (philo->philo_number % 2)
		usleep(1000);
	while (++i < philo->data->each_time_toeat)
	{
		sem_wait(philo->data->forks);
		action(philo->philo_number, data->start_time, "has taken a fork", data);
		sem_wait(philo->data->forks);
		action(philo->philo_number, data->start_time, "has taken a fork", data);
		philo->is_eating = 1;
		action(philo->philo_number, data->start_time, "is eating", data);
		philo->last_meal = gettime();
		ft_usleep(philo->data->time_to_eat);
		philo->is_eating = 0;
		sem_post(philo->data->forks);
		sem_post(philo->data->forks);
		action(philo->philo_number, data->start_time, "is sleeping", data);
		ft_usleep(philo->data->time_to_sleep);
		action(philo->philo_number, data->start_time, "is thinking", data);
	}
	exit(2);
}

void	ft_data_init(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->all_philo)
	{
		data->philo_tab[i].philo_number = i;
		data->philo_tab[i].left_fork = i;
		data->philo_tab[i].right_fork = (i + 1) % data->all_philo;
		data->philo_tab[i].is_eating = 0;
		data->philo_tab[i].data = data;
	}
}

void	ft_sem_init(t_data *data)
{
	sem_unlink("forks");
	sem_unlink("print");
	data->forks = sem_open("forks", O_CREAT, S_IRWXU, data->all_philo);
	data->print = sem_open("print", O_CREAT, S_IRWXU, 1);
}
