/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   used.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwehbe <miwehbe@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 17:08:34 by miwehbe           #+#    #+#             */
/*   Updated: 2025/08/21 17:08:34 by miwehbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_number(int argc, char *argv[])
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (!is_number(argv[i]))
			return (0);
		i++;
	}
	return (1);
}

int	assign_value(int argc, char *argv[], t_simulation *sim)
{
	sim->num_of_philos = ft_atoi(argv[1]);
	sim->time_to_die = ft_atoi(argv[2]);
	sim->time_to_eat = ft_atoi(argv[3]);
	sim->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		sim->meals_needed = ft_atoi(argv[5]);
	else
		sim->meals_needed = -1;
	return (1);
}

int	check_range(int argc, t_simulation *sim)
{
	if (sim->num_of_philos <= 0
		|| sim->num_of_philos > 200)
		return (0);
	if (sim->time_to_die <= 0
		|| sim->time_to_eat <= 0
		|| sim->time_to_sleep <= 0)
		return (0);
	if (argc == 6
		&& sim->meals_needed <= 0)
		return (0);
	return (1);
}

int	alloc_simulation(t_simulation *sim)
{
	sim->forks = malloc(sizeof(pthread_mutex_t) * sim->num_of_philos);
	if (!sim->forks)
		return (0);
	sim->philos = malloc(sizeof(t_philo) * sim->num_of_philos);
	if (!sim->philos)
	{
		free(sim->forks);
		return (0);
	}
	return (1);
}

void	init_forks(t_simulation *sim)
{
	int	i;

	i = 0;
	while (i < sim->num_of_philos)
	{
		pthread_mutex_init(&sim->forks[i], NULL);
		i++;
	}
}
