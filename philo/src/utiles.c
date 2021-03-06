/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaoud <msaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 13:43:30 by msaoud            #+#    #+#             */
/*   Updated: 2022/05/12 18:06:44 by msaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	action(int philo_id, long long time, char *action, t_data *data)
{
	pthread_mutex_lock(&data->print);
	printf("%lld %d %s\n", gettime() - time, philo_id + 1, action);
	pthread_mutex_unlock(&data->print);
}

void	ft_usleep(int time)
{
	long long	stop_time;

	stop_time = gettime() + time;
	while (gettime() < stop_time)
		usleep(50);
	return ;
}

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
