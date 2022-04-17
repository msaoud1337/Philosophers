#ifndef HEADER_H
# define HEADER_H


#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct s_data
{
    int n;
    int n_philosofers;
    int n_fork;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int time_to_think;
    int n_team_eating;
    int must_eat;
    int *philosofers;
    pthread_t   *threads;
    pthread_mutex_t *mutex;
    struct s_data *next;
} t_data;

int	ft_atoi(const char *str);

# endif