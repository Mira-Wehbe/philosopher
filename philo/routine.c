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

static void take_forks_last_philo(t_philo *philo)
{
  pthread_mutex_lock(philo->right_fork);
  safe_print(philo->simul, philo->id + 1, "has taken a fork");
  if (should_stop(philo->simul))
  {
    pthread_mutex_unlock(philo->right_fork);
    return;
  }
  pthread_mutex_lock(philo->left_fork);
  safe_print(philo->simul, philo->id + 1, "has taken a fork");
}

static void take_forks_regular_philo(t_philo *philo)
{
  pthread_mutex_lock(philo->left_fork);
  safe_print(philo->simul, philo->id + 1, "has taken a fork");
  if (should_stop(philo->simul))
  {
    pthread_mutex_unlock(philo->left_fork);
    return;
  }
  pthread_mutex_lock(philo->right_fork);
  safe_print(philo->simul, philo->id + 1, "has taken a fork");
}

void take_forks(t_philo *philo)
{
  if (philo->id == philo->simul->num_of_philos - 1)
    take_forks_last_philo(philo);
  else
    take_forks_regular_philo(philo);
}

void put_forks(t_philo *philo)
{
  pthread_mutex_unlock(philo->left_fork);
  pthread_mutex_unlock(philo->right_fork);
}

void *philosopher_routine(void *arg)
{
  t_philo *philo;

  philo = (t_philo *)arg;
  if (philo->id % 2 == 1)
    usleep(1000); 
  while (!should_stop(philo->simul))
  {
    if (should_stop(philo->simul))
      break;
    eat(philo);
    if (should_stop(philo->simul))
      break;
    sleep_philo(philo);
    if (should_stop(philo->simul))
      break;
    think(philo);
  }
  return (NULL);
}