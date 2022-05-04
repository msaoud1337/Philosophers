#include "header.h"

void    philo_eating(t_data *data)
{
	long long	start;

	start = gettime();
	while (1)
	{
		if ((gettime() - start) >= data->time_to_eat)
			break ;
	}
}