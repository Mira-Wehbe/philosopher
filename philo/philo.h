/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwehbe <miwehbe@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 16:11:17 by miwehbe           #+#    #+#             */
/*   Updated: 2025/08/21 16:11:17 by miwehbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_simulation	t_simulation;

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	size_t			last_meal;
	t_simulation	*simul;
}	t_philo;

typedef struct s_simulation
{
	int				num_of_philos;
	int				meals_needed;
	int				stop;
	long long		time_to_eat;
	long long		time_to_die;
	long long		time_to_sleep;
	long long		start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	stop_lock;
	pthread_mutex_t	meal_lock;
	t_philo			*philos;
}	t_simulation;

int		ft_atoi(const char *nptr);
int		is_number(const char *c);
int		parse_args(int argc, char **argv, t_simulation *sim);
int		check_number(int argc, char **argv);
int		assign_value(int argc, char **argv, t_simulation *sim);
int		check_range(int argc, t_simulation *sim);

int		init_simulation(t_simulation *sim, int argc, char **argv);
int		alloc_simulation(t_simulation *sim);
void	init_forks(t_simulation *sim);
void	init_philos(t_simulation *sim);
void	destroy_simulation(t_simulation *sim);

void	smart_sleep(t_simulation *sim, size_t duration);
size_t	get_time(void);

void	take_forks(t_philo *philo);
void	put_forks(t_philo *philo);
void	eat(t_philo *philo);
void	sleep_philo(t_philo *philo);
void	think(t_philo *philo);

void	*philosopher_routine(void *arg);
void	*single_philosopher_routine(void *arg);
void	*monitor_routine(void *arg);

int		should_stop(t_simulation *sim);
void	set_stop(t_simulation *sim);
void	set_last_meal(t_philo *philo, long long time);
void	safe_print(t_simulation *sim, int philo_id, char *message);
int		check_philosopher_death(t_simulation *sim);
int		check_all_eaten(t_simulation *sim);

int		initialize_simulation(t_simulation *sim, int argc, char **argv);
int		handle_single_philosopher(t_simulation *sim);
int		handle_multiple_philosophers(t_simulation *sim);
int		wait_and_cleanup(t_simulation *sim, pthread_t monitor_thread);
int		create_monitor_thread(t_simulation *sim, pthread_t *monitor_thread);
int		create_philosopher_threads(t_simulation *sim);
size_t	get_last_meal(t_philo *philo);
#endif
