/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozdemir <ozdemir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 15:06:58 by ozdemir           #+#    #+#             */
/*   Updated: 2024/06/06 13:56:22 by ozdemir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

int	init_general(t_general *general, int ac, char **av)
{
	general->number_of_philosophers = ft_atoi(av[1]);
	general->time_to_die = ft_atoi(av[2]);
	general->time_to_eat = ft_atoi(av[3]);
	general->time_to_sleep = ft_atoi(av[4]);
	general->died = 0;
	if (ac == 6)
		general->must_eat_count = ft_atoi(av[5]);
	else
		general->must_eat_count = -1;
	if (check_init(general))
		return (1);
	return (0);
}

int	init_mutex(t_general *general)
{
	int	i;

	i = 0;
	general->forks = malloc(sizeof(t_fork) * general->number_of_philosophers);
	if (!general->forks)
		return (1);
	while (i < general->number_of_philosophers)
	{
		pthread_mutex_init(&general->forks[i].lock, NULL);
		general->forks[i].number = i;
		i++;
	}
	pthread_mutex_init(&general->died_mutex, NULL);
	return (0);
}

int	init_philos(t_general *general)
{
	int	i;

	general->philos = malloc(sizeof(t_philo) * general->number_of_philosophers);
	if (!general->philos)
		return (1);
	general->start_time = get_time_in_ms();
	i = 0;
	while (i < general->number_of_philosophers)
	{
		general->philos[i].id = i + 1;
		general->philos[i].last_meal_time = 0;
		general->philos[i].eaten_count = 0;
		general->philos[i].left_fork = &general->forks[i];
		general->philos[i].right_fork = &general->forks[(i + 1)
			% general->number_of_philosophers];
		general->philos[i].general = general;
		pthread_mutex_init(&general->philos[i].meal_lock, NULL);
		i++;
	}
	return (0);
}

int	create_thread(t_general *general)
{
	int	i;

	i = 0;
	while (i < general->number_of_philosophers)
	{
		if (pthread_create(&general->philos[i].thread, NULL, philo_cycle,
				&general->philos[i]))
			return (1);
		usleep(100);
		i++;
	}
	if (pthread_create(&general->death_thread, NULL, check_deaths, general))
		return (1);
	pthread_join(general->death_thread, NULL);
	i = 0;
	while (i < general->number_of_philosophers)
	{
		pthread_join(general->philos[i].thread, NULL);
		i++;
	}
	return (0);
}

void	free_all(t_general *general)
{
	int	i;

	i = 0;
	while (i < general->number_of_philosophers)
	{
		pthread_mutex_destroy(&general->philos[i].meal_lock);
		pthread_mutex_destroy(&general->forks[i].lock);
		i++;
	}
	i = 0;
	pthread_mutex_destroy(&general->died_mutex);
	free(general->philos);
	free(general->forks);
}
