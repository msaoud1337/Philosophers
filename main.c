/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaoud <msaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 16:05:14 by msaoud            #+#    #+#             */
/*   Updated: 2022/04/17 02:35:31 by msaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	*philosofers(void *arg)
{
	t_data	*philo = arg;
	printf("n_philo %d\n",philo->n_philosofers);
	return (0);
}

void	creatingthreads(t_data *philo)
{
	int	i;

	i = -1;
	while (++i < philo->n_philosofers)
		pthread_create(&philo->threads[i], NULL, &philosofers, philo);
	i = -1;
	while (++i < philo->n_philosofers)
		pthread_join(philo->threads[i], NULL);
	printf("return (0)\n");
}

void	pars(char **arv, t_data *philo)
{
	philo->n_philosofers = ft_atoi(arv[1]);
	philo->n_fork = philo->n_philosofers;
	philo->time_to_die = ft_atoi(arv[2]);
	philo->time_to_eat = ft_atoi(arv[3]);
	philo->time_to_sleep = ft_atoi(arv[4]);
	philo->must_eat = 0;
	if (arv[5])
		philo->must_eat = ft_atoi(arv[5]);
	philo->philosofers = malloc(sizeof(int) * philo->n_philosofers);
	if (!philo->philosofers)
		return ;
	philo->threads = malloc(sizeof(pthread_t) * philo->n_philosofers);
	if (!philo->threads)
		return ;
	philo->mutex = malloc(sizeof(pthread_mutex_t) * philo->n_philosofers);
	if (!philo->mutex)
		return ;
	creatingthreads(philo);
}

int	main(int arc, char **arv)
{
	t_data	*philo;

	pthread_mutex_init(&mutex, NULL);
	if (arc > 4 && arc <= 6)
		pars(arv, &philo);
	else
		printf("Invalid arguments !!\n");
	return (0);
}
