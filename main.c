/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaoud <msaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 16:05:14 by msaoud            #+#    #+#             */
/*   Updated: 2022/05/07 19:06:37 by msaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	eat(t_philosofers *philo)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(&data->forks[philo->right_fork]);
	action(philo->philo_number, philo->start_time, "has taken a fork", data);
	pthread_mutex_lock(&data->forks[philo->left_fork]);
	action(philo->philo_number, philo->start_time, "has taken a fork", data);
	action(philo->philo_number, philo->start_time, "is eating", data);
	philo_mouve(data->time_to_eat, philo, 1);
	data->all_ate++;
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
		if (!data->alive)
			break ;
		action(philo->philo_number, philo->start_time, "is sleeping", data);
		philo_mouve(data->time_to_sleep, philo, 0);
		action(philo->philo_number, philo->start_time, "is thinking", data);
	}
	return (0);
}

void	ft_philo_init(t_data *data)
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

void	ft_thread_init(t_data *data)
{
	int			i;
	pthread_t	check;

	i = -1;
	while (++i < data->all_philo)
	{
		data->philo_tab[i].last_meal = gettime();
		data->philo_tab[i].start_time = gettime();
		if (pthread_create(&data->philo_tab[i].philo_thread, NULL, &philosofers,
				(void *)&data->philo_tab[i]))
			ft_error(3);
		pthread_mutex_init(&data->philo_tab[i].check, NULL);
	}
	if (pthread_create(&check, NULL, &checkingfordeath, (void *)data))
		ft_error(3);
	pthread_join(check, NULL);
}

int	main(int arc, char **arv)
{
	t_data	data;

	if (arc < 5 || arc > 6)
		ft_error(0);
	pars(arc, arv, &data);
	ft_philo_init(&data);
	ft_mutex_init(&data);
	ft_thread_init(&data);
}
