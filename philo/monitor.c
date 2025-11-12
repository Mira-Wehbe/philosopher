/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwehbe <miwehbe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 20:37:49 by miwehbe           #+#    #+#             */
/*   Updated: 2025/11/12 06:06:58 by miwehbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	smart_sleep(t_simulation *sim, size_t duration_ms)
{
	size_t	start;
	size_t	now;
	size_t	elapsed;
	size_t	remaining;

	start = get_time();
	while (!should_stop(sim))
	{
		now = get_time();
		elapsed = now - start;
		if (elapsed >= duration_ms)
			break ;
		remaining = duration_ms - elapsed;
		if (remaining > 20)
			usleep(500);
		else
			usleep(50);
	}
}

int	check_philosopher_death(t_simulation *sim)
{
	int			i;
	long long	last_meal;
	long long	since_meal;

	i = 0;
	while (i < sim->num_of_philos)
	{
		last_meal = (long long)get_last_meal(&sim->philos[i]);
		since_meal = (long long)get_time() - last_meal;
		if (since_meal > (long long)sim->time_to_die)
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
		usleep(200);
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
	pthread_mutex_unlock(&philo->simul->forks[0]);
	return (NULL);
}

/*.smart sleep like sleep bas btshaykle kl shwy ize fi hade met ta tw2f 
.check philo death btmr2 ala kl philo wbtshuf ize fi hade mr2 waetu wma akl 
.check all eaten hayde bst3mle ize fi nb of meal btshfle
ize kl wehd akl l3ded lmtlub mn lmeal li lezm
yekle wbtht pthread ta hata tfut ala kl wehd wt2ra bryha
.monitor routine hayde thread btr2b lsh8l btshuf hal fi philo met ,hal klun
aklu l3aded lmltub wl usleep bi 2lbe mnsh nkhfef d8t al cpu
*/