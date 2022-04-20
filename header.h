#ifndef HEADER_H
# define HEADER_H


#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct s_philosofers
{
	int 		philo_number;
	int 		ate;
	int 		left_fork;
	int 		right_fork;
	long long 	time_to_die;
	pthread_t	philo_thread;
	long long 	start_time;
} t_philosofers;

typedef struct s_data
{
	int 					all_philo;
	int						time_to_die;
	int						time_to_eat;
	int						time_to_sleep;
	int 					each_time_toeat;
	pthread_mutex_t			*forks;
	struct s_philosofers	*philo_tab;
}	t_data;
void	ft_error(int i);
int		ft_atoi(const char *str);

# endif