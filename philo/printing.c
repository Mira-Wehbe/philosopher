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

void eat(t_philo *philo)
{
  if (should_stop(philo->simul))
    return;
  take_forks(philo);
    
  if (should_stop(philo->simul))
  {
    put_forks(philo);
    return;
  }  
  safe_print(philo->simul, philo->id + 1, "is eating");
  set_last_meal(philo, get_time());
  smart_sleep(philo->simul, philo->simul->time_to_eat);
  put_forks(philo);
  pthread_mutex_lock(&philo->simul->meal_lock);
  philo->meals_eaten++;
  pthread_mutex_unlock(&philo->simul->meal_lock);
}

void sleep_philo(t_philo *philo)
{
  if (should_stop(philo->simul))
    return;    
  safe_print(philo->simul, philo->id + 1, "is sleeping");
  smart_sleep(philo->simul, philo->simul->time_to_sleep);
}

void think(t_philo *philo)
{
  if (should_stop(philo->simul))
    return;    
  safe_print(philo->simul, philo->id + 1, "is thinking");
  if (philo->simul->num_of_philos % 2 == 1)
    usleep(1000);
}