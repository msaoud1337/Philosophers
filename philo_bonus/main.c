#include "header_bonus.h"

void	action(int philo_n , long long start, char *s, t_data *data)
{
	sem_wait(&data->print);
	printf("%lld %d %s", philo_n + 1, gettime() - start, s);
	sem_post(&data->print);
}

void	routine(t_philosofers *philo)
{
	while (1)
	{
		sem_wait(&philo->data->forks[philo->left_fork]);
		action(philo->philo_number, philo->data->start_time, "has taken a fork", philo->data);
		sem_wait(&philo->data->forks[philo->right_fork]);
		action(philo->philo_number, philo->data->start_time, "has taken a fork", philo->data);
		philo->is_eating = 1;
		action(philo->philo_number, philo->data->start_time, "is eating", philo->data);
		philo->last_meal = gettime();
		usleep(philo->data->time_to_eat * 1000);
		philo->is_eating = 0;
		sem_post(&philo->data->forks[philo->left_fork]);
		sem_post(&philo->data->forks[philo->right_fork]);
		action(philo->philo_number, philo->data->start_time, "is sleeping", philo->data);
		usleep(philo->data->time_to_sleep * 1000);
		action(philo->philo_number, philo->data->start_time, "is thinking", philo->data);
	}
}

void	*philo(void *arg)
{
	int				i;
	t_philosofers	*philo;

	usleep(50);
	philo = (t_philosofers *)arg;
	i = -1;
	while (1)
	{
		if(philo->is_eating == 0)
		{
			if ((gettime() - philo->last_meal) >= philo->data->time_to_die)
				exit(1);
		}
	}
	return (0);
}

int		ft_fork(t_data *data)
{
	int			pid;
	static int	i;

	pid = fork();
	if (!pid)
	{
		if (pthread_create(&data->philo_tab[i].philo_thread, NULL, &philo, (void *)&data->philo_tab[i]))
			exit(0);
		routine(&data->philo_tab[i++]);
	}
	return (pid);
}

void	processes_creat(t_data *data)
{
	int i;

	i = 0;
	while (++i < data->all_philo)
	{
		data->pid_tab[i] = ft_fork(data);
		if (data->)

	}
}

void	ft_data_init(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->all_philo)
	{
		data->philo_tab[i].philo_number = i;
		data->philo_tab[i].left_fork = i;
		data->philo_tab[i].right_fork = (i + 1) % data->all_philo;
		data->philo_tab[i].is_eating = 0;
		data->philo_tab[i].data = data;
	}
}

void    ft_sem_init(t_data *data)
{
	int i;

	i = -1;
	while (++i < data->all_philo)
		sem_open("forks", O_CREAT, 0777, );
	sem_init(&data->print, 0, 1);
}


int main(int arc, char *arv[])
{
	t_data  data;

	if (arc < 5 || arc > 6)
		return (0);
	pars(arc, arv, &data);
	ft_data_init(&data);
	ft_sem_init(&data);
	processes_creat(&data);
}