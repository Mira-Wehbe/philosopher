/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwehbe <miwehbe@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 15:17:11 by miwehbe           #+#    #+#             */
/*   Updated: 2025/08/21 15:17:11 by miwehbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void smart_sleep(t_simulation *sim,size_t duration)
{
  size_t starttime;
  size_t currenttime;
  size_t elapsed;

  starttime =get_time();
  elapsed=0;
  while(elapsed < duration)
  {
    if(sim->stop ==0)
      break;
    usleep(500);
    currenttime = get_time();
    elapsed =currenttime - starttime;
  }
}

void	take_forks(t_philo *philo)
{
	int	left;
	int	right;
	int	first;
	int	second;

	left = philo->id;
	right = (philo->id + 1) % philo->simul->num_of_philos;
	if (left < right)
	{
		first = left;
		second = right;
	}
	else
	{
		first = right;
		second = left;
	}
	pthread_mutex_lock(&philo->simul->forks[first]);
	printf("%zu %d has taken a fork\n",
		get_time() - philo->simul->start_time, philo->id + 1);
	pthread_mutex_lock(&philo->simul->forks[second]);
	printf("%zu %d has taken a fork\n",
		get_time() - philo->simul->start_time, philo->id + 1);
}

void put_forks(t_philo *philo)
{
  int left;
  int right;

  left = philo->id;
  right=(philo->id+1) % philo->simul->num_of_philos;
  pthread_mutex_unlock(&philo->simul->forks[left]);
  pthread_mutex_unlock(&philo->simul->forks[right]);
}
