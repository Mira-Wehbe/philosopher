/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwehbe <miwehbe@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 18:31:48 by miwehbe           #+#    #+#             */
/*   Updated: 2025/08/20 18:31:48 by miwehbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
int main(int argc, char **argv)
{
    t_simulation sim;

    if (!init_simulation(&sim, argc, argv))
    {
        write(2, "Error: invalid input\n", 21);
        return (1);
    }
    printf("num_of_philos: %d\n", sim.num_of_philos);
    printf("time_to_die: %lld\n", sim.time_to_die);
    printf("time_to_eat: %lld\n", sim.time_to_eat);
    printf("time_to_sleep: %lld\n", sim.time_to_sleep);
    printf("meals_needed: %d\n", sim.meals_needed);
    init_philos(&sim);
    int i = 0;
    while (i < sim.num_of_philos)
    {
        printf("Philo %d - left fork: %p, right fork: %p, last_meal: %lld\n",
            sim.philos[i].id,
            sim.philos[i].left_fork,
            sim.philos[i].right_fork,
            sim.philos[i].last_meal);
        i++;
    }
    destroy_simulation(&sim);

    return (0);
}
