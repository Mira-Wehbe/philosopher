/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwehbe <miwehbe@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 20:48:06 by miwehbe           #+#    #+#             */
/*   Updated: 2025/09/29 20:48:06 by miwehbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	should_stop(t_simulation *sim)
{
	int	value;

	pthread_mutex_lock(&sim->stop_lock);
	value = sim->stop;
	pthread_mutex_unlock(&sim->stop_lock);
	return (value);
}

void	set_stop(t_simulation *sim)
{
	pthread_mutex_lock(&sim->stop_lock);
	sim->stop = 1;
	pthread_mutex_unlock(&sim->stop_lock);
}

size_t	get_last_meal(t_philo *philo)
{
	size_t	time;

	pthread_mutex_lock(&philo->simul->meal_lock);
	time = philo->last_meal;
	pthread_mutex_unlock(&philo->simul->meal_lock);
	return (time);
}

void	set_last_meal(t_philo *philo, long long time)
{
	pthread_mutex_lock(&philo->simul->meal_lock);
	philo->last_meal = time;
	pthread_mutex_unlock(&philo->simul->meal_lock);
}

void	safe_print(t_simulation *sim, int philo_id, char *message)
{
	size_t	timestamp;

	pthread_mutex_lock(&sim->print_lock);
	if (!should_stop(sim))
	{
		timestamp = get_time() - sim->start_time;
		printf("%zu %d %s\n", timestamp, philo_id, message);
	}
	pthread_mutex_unlock(&sim->print_lock);
}
