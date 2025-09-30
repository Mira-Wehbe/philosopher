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
    if(should_stop(sim))
      break;
    usleep(1000);
    currenttime = get_time();
    elapsed =currenttime - starttime;
  }
}

void take_forks(t_philo *philo)
{
  if (philo->id == philo->simul->num_of_philos - 1)
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
    else
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
}

void put_forks(t_philo *philo)
{
  pthread_mutex_unlock(philo->left_fork);
  pthread_mutex_unlock(philo->right_fork);
}

void get_fork_order(t_philo *philo, int *first, int *second)
{
  int left;
  int right;
    
  left = philo->id;
  right = (philo->id + 1) % philo->simul->num_of_philos;

  if (left < right)
  {
    *first = left;
    *second = right;
  }
  else
  {
    *first = right;
    *second = left;
  }
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