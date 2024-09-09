/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozdemir <ozdemir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 13:34:53 by ozdemir           #+#    #+#             */
/*   Updated: 2024/06/06 13:56:00 by ozdemir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define INT_MAX 2147483647

typedef struct s_fork
{
	int					number;
	pthread_mutex_t		lock;
}						t_fork;

typedef struct s_philo
{
	int					id;
	int					eaten_count;
	long long			last_meal_time;
	t_fork				*left_fork;
	t_fork				*right_fork;
	pthread_t			thread;
	pthread_mutex_t		meal_lock;
	struct s_general	*general;
}						t_philo;

typedef struct s_general
{
	int					number_of_philosophers;
	long long			time_to_die;
	long long			time_to_eat;
	long long			time_to_sleep;
	int					must_eat_count;
	long long			start_time;
	pthread_mutex_t		died_mutex;
	int					died;
	pthread_t			death_thread;
	t_philo				*philos;
	t_fork				*forks;
}						t_general;

long long				get_time_in_ms(void);
void					message_print(t_philo *philo, char *str);
void					eat(t_philo *philo);
void					sleeep(t_philo *philo);
void					think(t_philo *philo);
void					take_forks(t_philo *philo);
void					drop_forks(t_philo *philo);
void					*philo_cycle(void *arg);
int						init_mutex(t_general *general);
int						init_philos(t_general *general);
int						init_general(t_general *general, int ac, char **av);
void					*check_deaths(void *arg);
void					free_all(t_general *general);
void					exit_error(char *msg);
long long				ft_atoi(const char *str);
int						args_check(char **av);
int						ft_usleep(size_t milliseconds, t_philo *philo);
int						create_thread(t_general *general);
int						check_init(t_general *general);

#endif