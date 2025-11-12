/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwehbe <miwehbe@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 20:38:52 by miwehbe           #+#    #+#             */
/*   Updated: 2025/11/11 20:38:54 by miwehbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_philo *philo)
{
	if (should_stop(philo->simul))
		return ;
	if (!take_forks(philo))
		return ;
	if (should_stop(philo->simul))
	{
		put_forks(philo);
		return ;
	}
	safe_print(philo->simul, philo->id + 1, "is eating");
	set_last_meal(philo, get_time());
	smart_sleep(philo->simul, philo->simul->time_to_eat);
	put_forks(philo);
	pthread_mutex_lock(&philo->simul->meal_lock);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->simul->meal_lock);
}

void	sleep_philo(t_philo *philo)
{
	if (should_stop(philo->simul))
		return ;
	safe_print(philo->simul, philo->id + 1, "is sleeping");
	smart_sleep(philo->simul, philo->simul->time_to_sleep);
}

void	think(t_philo *philo)
{
	t_simulation	*sim;

	sim = philo->simul;
	if (should_stop(sim))
		return ;
	safe_print(sim, philo->id + 1, "is thinking");
	if (sim->num_of_philos % 2 == 1)
		usleep(1000);
}
