/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaoud <msaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 16:05:14 by msaoud            #+#    #+#             */
/*   Updated: 2022/04/20 01:23:41 by msaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"


void	ft_mutex_init(t_data *data)
{
	int i;

	i = -1;
	while (++i < data->all_philo)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
			ft_error(4);
	}
		printf("%d",i);
}

void	*test()
{
	printf("salam\n");
	return 0;
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
		if (pthread_create(&data->philo_tab[i].philo_thread, NULL, &test, NULL))
			ft_error(3);
	}
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
	data->forks = malloc(sizeof(pthread_mutex_t) * data->all_philo);
	if (!data->forks)
		ft_error(1);
}

int main(int arc, char **arv)
{
	t_data	data;

	if (arc < 5 || arc > 6)
		ft_error(0);
	pars(arv, &data);
	ft_mutex_init(&data);
	ft_philo_init(&data);
}
