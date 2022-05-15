/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaoud <msaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 17:09:22 by msaoud            #+#    #+#             */
/*   Updated: 2022/05/12 18:10:03 by msaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_BONUS_H
# define HEADER_BONUS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <semaphore.h>
# include <sys/stat.h>
# include <signal.h>

typedef struct s_philosofers
{
	int				philo_number;
	int				philo_pid;
	int				left_fork;
	int				right_fork;
	int				is_eating;
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
	int						main_pid;
	int						*pid_tab;
	struct s_philosofers	*philo_tab;
	sem_t					*forks;
	sem_t					*print;
}	t_data;

void		action(int philo_n, long long start, char *s, t_data *data);
void		routine(t_philosofers *philo);
void		routine1(t_philosofers *philo);
void		ft_data_init(t_data *data);
void		ft_sem_init(t_data *data);
int			ft_atoi(const char *str);
long long	gettime(void);
int			pars(int arc, char **arv, t_data *data);
void		ft_usleep(int time);
#endif