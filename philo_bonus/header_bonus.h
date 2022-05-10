#ifndef HEADER_BONUS_H
# define HEADER_BONUS_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <semaphore.h>

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
    int                     main_pid;
	int						*pid_tab;
	struct s_philosofers	*philo_tab;
    sem_t                   *forks;
    sem_t                   print;
}	t_data;

int	ft_atoi(const char *str);
long long	gettime(void);
int	pars(int arc, char **arv, t_data *data);

#endif