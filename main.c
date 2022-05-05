/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaoud <msaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 16:05:14 by msaoud            #+#    #+#             */
/*   Updated: 2022/05/05 15:32:18 by msaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	eat(t_philosofers *philo)
{
	t_data *data;

	data = philo->data;
	printf("***%d|| %d %d\n",pthread_mutex_lock(&data->forks[philo->right_fork]), philo->left_fork ,philo->right_fork);
		// printf("mutex succes\n");
	printf("print ***%d\n",pthread_mutex_lock(&data->print));
	action(philo->philo_number, philo->start_time, "has taken a fork");
	pthread_mutex_lock(&data->forks[philo->left_fork]);
	action(philo->philo_number, philo->start_time, "has taken a fork");
	action(philo->philo_number, philo->start_time, "is eating");
	philo_mouve(data->time_to_eat);
	pthread_mutex_unlock(&data->print);
	philo->last_meal = gettime();
	pthread_mutex_unlock(&data->forks[philo->right_fork]);
	pthread_mutex_unlock(&data->forks[philo->left_fork]);
}

void	*philosofers(void	*param)
{
	t_philosofers	*philo;
	t_data			*data;

	philo = param;
	data = philo->data;
	if (philo->philo_number % 2)
		usleep(100);
	while (data->alive)
	{
		eat(philo);
		check_death(philo);
		philo_mouve(data->time_to_sleep);
		action(philo->philo_number, philo->start_time, "is sleeping");
		action(philo->philo_number, philo->start_time, "is thinking");
	}
	return (0);
}

void	ft_philo_init(t_data *data)
{
	int	i;

	i = -1;
	while (++i  < data->all_philo)
	{
		data->philo_tab[i].philo_number = i;
		data->philo_tab[i].ate = 0;
		data->philo_tab[i].left_fork = i;
		data->philo_tab[i].right_fork = (i + 1) % data->all_philo;
		data->philo_tab[i].data = data;
	}
}

void	ft_mutex_init(t_data *data)
{
	int i;

	i = -1;
	while (++i < data->all_philo)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
			ft_error(4);
	}
}

void	ft_thread_init(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->all_philo)
	{
		if (pthread_create(&data->philo_tab[i].philo_thread, NULL, &philosofers, (void *)&data->philo_tab[i]))
			ft_error(3);
		data->philo_tab[i].start_time = gettime();	
	}
	i = -1;
	while (++i < data->all_philo)
		pthread_join(data->philo_tab[i].philo_thread, NULL);
}

void	pars(char **arv, t_data *data)
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
	// data->forks = malloc(sizeof(pthread_mutex_t) * data->all_philo);
	// if (!data->forks)
	// 	ft_error(1);
	data->start_time = gettime();
	data->alive = 1;
}

int main(int arc, char **arv)
{
	t_data	data;

	if (arc < 5 || arc > 6)
		ft_error(0);
	pars(arv, &data);
	ft_philo_init(&data);
	ft_thread_init(&data);
	ft_mutex_init(&data);
}
