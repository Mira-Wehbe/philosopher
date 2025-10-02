/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwehbe <miwehbe@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 18:31:48 by miwehbe           #+#    #+#             */
/*   Updated: 2025/08/20 18:31:48 by miwehbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	initialize_simulation(t_simulation *sim, int argc, char **argv)
{
	if (!init_simulation(sim, argc, argv))
	{
		write(2, "Error: invalid input\n", 21);
		return (0);
	}
	init_philos(sim);
	return (1);
}

int	handle_single_philosopher(t_simulation *sim)
{
	pthread_t	monitor_thread;

	if (pthread_create(
			&sim->philos[0].thread,
			NULL,
			single_philosopher_routine,
			&sim->philos[0]) != 0)
	{
		write(2,
			"Error: failed to create philosopher thread\n",
			44);
		destroy_simulation(sim);
		return (0);
	}
	if (!create_monitor_thread(sim, &monitor_thread))
	{
		pthread_join(sim->philos[0].thread, NULL);
		destroy_simulation(sim);
		return (0);
	}
	pthread_join(monitor_thread, NULL);
	pthread_join(sim->philos[0].thread, NULL);
	destroy_simulation(sim);
	return (1);
}

int	handle_multiple_philosophers(t_simulation *sim)
{
	pthread_t	monitor_thread;
	int			i;

	if (!create_philosopher_threads(sim))
	{
		destroy_simulation(sim);
		return (0);
	}
	if (!create_monitor_thread(sim, &monitor_thread))
	{
		i = 0;
		while (i < sim->num_of_philos)
		{
			pthread_join(sim->philos[i].thread, NULL);
			i++;
		}
		destroy_simulation(sim);
		return (0);
	}
	return (wait_and_cleanup(sim, monitor_thread));
}

int	wait_and_cleanup(t_simulation *sim, pthread_t monitor_thread)
{
	int	i;

	pthread_join(monitor_thread, NULL);
	i = 0;
	while (i < sim->num_of_philos)
	{
		pthread_join(sim->philos[i].thread, NULL);
		i++;
	}
	destroy_simulation(sim);
	return (1);
}

int	main(int argc, char **argv)
{
	t_simulation	sim;

	if (!initialize_simulation(&sim, argc, argv))
		return (1);
	if (sim.num_of_philos == 1)
	{
		if (!handle_single_philosopher(&sim))
			return (1);
	}
	else
	{
		if (!handle_multiple_philosophers(&sim))
			return (1);
	}
	return (0);
}
