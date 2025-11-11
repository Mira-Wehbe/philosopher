/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwehbe <miwehbe@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 20:39:00 by miwehbe           #+#    #+#             */
/*   Updated: 2025/11/11 21:10:04 by miwehbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	get_fork_order(t_philo *philo, pthread_mutex_t **first,
	pthread_mutex_t **second)
{
	if (philo->left_fork < philo->right_fork)
	{
		*first = philo->left_fork;
		*second = philo->right_fork;
	}
	else
	{
		*first = philo->right_fork;
		*second = philo->left_fork;
	}
}

int	take_forks(t_philo *philo)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	get_fork_order(philo, &first_fork, &second_fork);
	pthread_mutex_lock(first_fork);
	safe_print(philo->simul, philo->id + 1, "has taken a fork");
	if (should_stop(philo->simul))
	{
		pthread_mutex_unlock(first_fork);
		return (0);
	}
	pthread_mutex_lock(second_fork);
	safe_print(philo->simul, philo->id + 1, "has taken a fork");
	if (should_stop(philo->simul))
	{
		pthread_mutex_unlock(second_fork);
		pthread_mutex_unlock(first_fork);
		return (0);
	}
	return (1);
}

void	put_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 1)
		usleep(1000);
	while (!should_stop(philo->simul))
	{
		if (should_stop(philo->simul))
			break ;
		eat(philo);
		if (should_stop(philo->simul))
			break ;
		sleep_philo(philo);
		if (should_stop(philo->simul))
			break ;
		think(philo);
	}
	return (NULL);
}

/*
.get fork:hayde bthadedle kif ha ykhdu lfork btshfle aye wehde az8r bl raem wbtkhli lphilo yekhde bl awel
bsir byntru baad la wwhed mnun ykhls msh deadlock
.take fork:hon b3ti philo awal fork wbtntur ta shuf ize fi shi stop,b3den b3ti tene wehde wbrj3 bntur izefi shi 8lt
.philo routine:btkhline thread even shwy yntru mnshn deadlock,whye btsh8le cycle t3t philo yekul ynem yfkr repeat

*/