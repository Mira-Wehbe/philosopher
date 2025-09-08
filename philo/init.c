/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwehbe <miwehbe@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 18:32:05 by miwehbe           #+#    #+#             */
/*   Updated: 2025/08/20 18:32:05 by miwehbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	parse_args(int argc, char *argv[], t_simulation *sim)
{
  if(argc != 5 && argc != 6)
    return (0);
  if(!check_number(argc,argv))
    return (0);
  assign_value(argc,argv,sim);
  if(!check_range(argc,sim))
    return(0);
  return (1);
}

int	init_simulation(t_simulation *sim, int argc, char **argv)
{
  if(!parse_args(argc,argv,sim))
    return (0);
  if(!alloc_simulation(sim))
    return (0);
  init_forks(sim);
  sim->stop = 0;
  sim->start_time=get_time();
  return (1);
}

void init_philos(t_simulation *sim)
{
  int i;

  i = 0;
  while (i < sim->num_of_philos)
  {
    sim->philos[i].id = i+1;
    sim->philos[i].left_fork = &sim->forks[i];
    sim->philos[i].right_fork= &sim->forks[(i+1)% sim->num_of_philos];
    sim->philos[i].meals_eaten = 0;
    sim->philos[i].last_meal = sim->start_time;
    sim->philos[i].simul = sim;
    i++;
  }
}

void destroy_simulation(t_simulation *sim)
{
  int i;

  i = 0;
  while (i <sim->num_of_philos)
  {
    pthread_mutex_destroy(&sim->forks[i]);
    i++;
  }
  pthread_mutex_destroy(&sim->print_lock);
  free(sim->forks);
  free(sim->philos);
}