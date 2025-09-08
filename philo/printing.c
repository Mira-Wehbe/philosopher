/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwehbe <miwehbe@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 15:33:25 by miwehbe           #+#    #+#             */
/*   Updated: 2025/08/22 15:33:25 by miwehbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_philo *philo)
{
	take_forks(philo);
	philo->last_meal = get_time();
	printf("%lld %d is eating\n",
		philo->last_meal - philo->simul->start_time, philo->id + 1);
	smart_sleep(philo->simul, philo->simul->time_to_eat);
	put_forks(philo);
	philo->meals_eaten++;
}

void	sleep_philo(t_philo *philo)
{
	printf("%lld %d is sleeping\n",
		get_time() - philo->simul->start_time, philo->id + 1);
	smart_sleep(philo->simul, philo->simul->time_to_sleep);
}

void	think(t_philo *philo)
{
	printf("%lld %d is thinking\n",
		get_time() - philo->simul->start_time, philo->id + 1);
}
