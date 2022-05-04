#ifndef HEADER_H
# define HEADER_H


#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>

typedef struct s_philosofers
{
	int 				philo_number;
	int 				ate;
	int 				left_fork;
	int 				right_fork;
	long long 			time_to_die;
	pthread_t			philo_thread;
	long long 			start_time;
	long long			last_meal;
	struct s_data		*data;
} t_philosofers;

typedef struct s_data
{
	int 					all_philo;
	int						time_to_die;
	int						time_to_eat;
	int						time_to_sleep;
	int 					each_time_toeat;
	long long				start_time;
	long long				last_time;
	int						alive;
	pthread_mutex_t			*forks;
	struct s_philosofers	*philo_tab;
}	t_data;

long long	calcule_time(long long n,long long s);
void	action(int philo_id, long long time, char *action);
void	ft_error(int i);
int		ft_atoi(const char *str);
long long	gettime();
void    philo_eating(t_data *data);

# endif