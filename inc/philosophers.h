/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozdemir <ozdemir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 13:34:53 by ozdemir           #+#    #+#             */
/*   Updated: 2024/05/15 16:09:37 by ozdemir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include "Libft/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_fork
{
	int	used;
	pthread_mutex_t	lock;
}			t_fork;

typedef struct s_philo
{
	int	id;
	t_fork *left_fork;
	t_fork *right_fork;
	int	using_left;
	int	using_right;                                                                  
	int	eaten_count;
	long long last_meal_time;
	pthread_mutex_t	meal_lock;
	struct s_general *general;
	pthread_t thread;
}			t_philo;

typedef struct s_general
{
	int	number_of_philosophers;
	long long	time_to_die;
	long long	time_to_eat;
	long long	time_to_sleep;
	int	must_eat_count;
	long long	start_time;
	pthread_mutex_t died_mutex;
	int	died;
	pthread_t	death_thread;
	t_philo *philos;
	t_fork	*forks;
}			t_general;


long long get_time_in_ms(void);
void message_print(t_philo *philo, char *str);
void eat(t_philo *philo);
void sleeep(t_philo *philo);
void think(t_philo *philo);
void take_forks(t_philo *philo);
void drop_forks(t_philo *philo);
void *philo_cycle(void *arg);
void init_forks(t_fork *forks, t_general *general);
void init_philos(t_philo *philos, t_fork *forks, t_general *general);
int init_general(t_general *general, int ac, char **av);
void create_philos_threads(t_general *general);
void join_philos_threads(t_general *general);
void *check_deaths(void *arg);
void start_death_checker(t_general *general);
void join_death_checker(t_general *general);
void destroy_mutexes(t_general *general);
void exit_error(char *msg);

#endif