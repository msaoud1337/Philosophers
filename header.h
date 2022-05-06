/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaoud <msaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 13:39:39 by msaoud            #+#    #+#             */
/*   Updated: 2022/05/06 14:52:03 by msaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philosofers
{
	int				philo_number;
	int				ate;
	int				left_fork;
	int				right_fork;
	pthread_t		philo_thread;
	long long		start_time;
	long long		last_meal;
	struct s_data	*data;
}	t_philosofers;

typedef struct s_data
{
	int						all_philo;
	int						time_to_die;
	int						time_to_eat;
	int						time_to_sleep;
	int						each_time_toeat;
	long long				start_time;
	int						all_ate;
	int						arc;
	int						alive;
	pthread_mutex_t			*forks;
	pthread_mutex_t			print;
	pthread_mutex_t			dead;
	struct s_philosofers	*philo_tab;
}	t_data;

long long	calcule_time(long long n, long long s);
void		action(int philo_id, long long time, char *action, t_data *data);
void		ft_error(int i);
int			ft_atoi(const char *str);
long long	gettime(void);
void		philo_mouve(int time);
void		philo_dead(t_philosofers *philo);
void		*checkingfordeath(void	*arg);
void		ft_mutex_init(t_data *data);
void		pars(int arc, char **arv, t_data *data);

#endif