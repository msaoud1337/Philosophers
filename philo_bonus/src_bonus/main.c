/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaoud <msaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 15:56:46 by msaoud            #+#    #+#             */
/*   Updated: 2022/05/11 17:09:12 by msaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_bonus.h"

void	*philo(void *arg)
{
	int				i;
	t_philosofers	*philo;

	usleep(50);
	philo = (t_philosofers *)arg;
	i = -1;
	while (1)
	{
		if (philo->is_eating == 0)
		{
			if ((gettime() - philo->last_meal) >= philo->data->time_to_die)
			{
				sem_wait(philo->data->print);
				printf("%lld %d died\n", gettime() - philo->data->start_time,
					philo->philo_number + 1);
				exit(1);
			}
		}
	}
	return (0);
}

int	ft_fork(t_data *data)
{
	int			pid;
	static int	i;

	pid = fork();
	if (!pid)
	{
		data->philo_tab[i].last_meal = gettime();
		if (pthread_create(&data->philo_tab[i].philo_thread, NULL,
				&philo, (void *)&data->philo_tab[i]))
			exit(0);
		if (data->arc == 5)
			routine(&data->philo_tab[i]);
		else
			routine1(&data->philo_tab[i]);
	}
	i++;
	return (pid);
}

void	ft_waitpid(t_data *data)
{
	int	i;
	int	tmp;

	while (waitpid(-1, &tmp, 0) > 0)
	{
		if (tmp == 256)
		{
			i = -1;
			while (++i < data->all_philo)
				kill(data->pid_tab[i], SIGINT);
		}
	}
}

void	processes_creat(t_data *data)
{
	int	i;

	i = -1;
	data->start_time = gettime();
	while (++i < data->all_philo)
	{
		data->pid_tab[i] = ft_fork(data);
		if (data->pid_tab[i] < 0)
		{
			while (i >= 0)
			{
				kill(data->pid_tab[i], SIGINT);
				i--;
			}
			exit(0);
		}
	}
	ft_waitpid(data);
}

int	main(int arc, char *arv[])
{
	t_data	data;

	if (arc < 5 || arc > 6)
		return (0);
	pars(arc, arv, &data);
	ft_sem_init(&data);
	ft_data_init(&data);
	processes_creat(&data);
}
