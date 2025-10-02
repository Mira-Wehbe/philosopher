/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwehbe <miwehbe@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 09:58:10 by miwehbe           #+#    #+#             */
/*   Updated: 2025/08/22 09:58:10 by miwehbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	smart_sleep(t_simulation *sim, size_t duration)
{
	size_t	starttime;
	size_t	elapsed;
	size_t	currenttime;

	starttime = get_time();
	elapsed = 0;
	while (elapsed < duration)
	{
		if (should_stop(sim))
			break ;
		usleep(1000);
		currenttime = get_time();
		elapsed = currenttime - starttime;
	}
}

int	check_philosopher_death(t_simulation *sim)
{
	size_t		current_time;
	int			i;
	long long	last_time_meal;
	long long	time_last_meal;

	i = 0;
	current_time = get_time();
	while (i < sim->num_of_philos)
	{
		last_time_meal = get_last_meal(&sim->philos[i]);
		time_last_meal = current_time - last_time_meal;
		if (time_last_meal > sim->time_to_die)
		{
			safe_print(sim, i + 1, "died");
			set_stop(sim);
			return (1);
		}
		i++;
	}
	return (0);
}

int	check_all_eaten(t_simulation *sim)
{
	int	i;
	int	meals;

	if (sim->meals_needed == -1)
		return (0);
	i = 0;
	while (i < sim->num_of_philos)
	{
		pthread_mutex_lock(&sim->meal_lock);
		meals = sim->philos[i].meals_eaten;
		pthread_mutex_unlock(&sim->meal_lock);
		if (meals < sim->meals_needed)
			return (0);
		i++;
	}
	set_stop(sim);
	return (1);
}

void	*monitor_routine(void *arg)
{
	t_simulation	*sim;
	int				death_occurred;
	int				meals_completed;

	sim = (t_simulation *)arg;
	while (!should_stop(sim))
	{
		death_occurred = check_philosopher_death(sim);
		if (death_occurred)
			break ;
		meals_completed = check_all_eaten(sim);
		if (meals_completed)
			break ;
		usleep(1000);
	}
	return (NULL);
}

void	*single_philosopher_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->simul->forks[0]);
	safe_print(philo->simul, 1, "has taken a fork");
	smart_sleep(philo->simul, philo->simul->time_to_die);
	return (NULL);
}
