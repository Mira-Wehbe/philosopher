/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwehbe <miwehbe@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 18:32:31 by miwehbe           #+#    #+#             */
/*   Updated: 2025/11/11 21:15:41 by miwehbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *nptr)
{
	int	sign;
	int	result;

	sign = 1;
	result = 0;
	while ((*nptr >= 9 && *nptr <= 13) || *nptr == 32)
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sign = -1;
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		result = result * 10 + (*nptr - '0');
		nptr++;
	}
	return (sign * result);
}

int	is_number(const char *c)
{
	int	i;

	i = 0;
	if (!c || !c[0])
		return (0);
	if (c[i] == '+')
		i++;
	if (!c[i])
		return (0);
	while (c[i])
	{
		if (c[i] < '0' || c[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

size_t	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
	{
		write(2, "error getting time\n", 19);
		return (0);
	}
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	create_philosopher_threads(t_simulation *sim)
{
	int	i;
	int	ret;

	i = 0;
	while (i < sim->num_of_philos)
	{
		ret = pthread_create(&sim->philos[i].thread, NULL,
				philosopher_routine, &sim->philos[i]);
		if (ret != 0)
		{
			write(2, "Error: failed to create philosopher thread\n", 44);
			while (--i >= 0)
				pthread_join(sim->philos[i].thread, NULL);
			return (0);
		}
		i++;
	}
	return (1);
}

int	create_monitor_thread(t_simulation *sim, pthread_t *monitor_thread)
{
	int	ret;

	ret = pthread_create(monitor_thread, NULL, monitor_routine, sim);
	if (ret != 0)
	{
		write(2, "Error: failed to create monitor thread\n", 39);
		return (0);
	}
	return (1);
}

/*
.create philo:btkhl2 thread la philo wbinfz philo routine 
create philo btmasel hayet lphilo kl wehd endu thread wkl wehd bym cycle khas fi ynem yekul yfkr aded thread= 3aded philo
.create monit:btkhl;2 thread wehd monitor yra2b
monitor bi ra2b kl philo bishuf ize hade met ize klun aklu aded lmeal ize sar fi shi men ltnen byem set stop

*/