/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozdemir <ozdemir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 10:28:14 by ozdemir           #+#    #+#             */
/*   Updated: 2024/06/07 13:54:51 by ozdemir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	eat(t_philo *philo)
{
	take_forks(philo);
	message_print(philo, "is eating");
	pthread_mutex_lock(&philo->meal_lock);
	philo->last_meal_time = get_time_in_ms() - philo->general->start_time;
	pthread_mutex_unlock(&philo->meal_lock);
	ft_usleep(philo->general->time_to_eat, philo);
	pthread_mutex_lock(&philo->general->died_mutex);
	philo->eaten_count++;
	pthread_mutex_unlock(&philo->general->died_mutex);
	drop_forks(philo);
}

void	sleeep(t_philo *philo)
{
	message_print(philo, "is sleeping");
	ft_usleep(philo->general->time_to_sleep, philo);
}

void	think(t_philo *philo)
{
	message_print(philo, "is thinking");
	ft_usleep(1, philo);
}

void	*philo_cycle(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		pthread_mutex_lock(&philo->general->died_mutex);
		if (philo->general->died)
		{
			pthread_mutex_unlock(&philo->general->died_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->general->died_mutex);
		if (philo->eaten_count == philo->general->must_eat_count
			&& philo->general->must_eat_count > 0)
			break ;
		eat(philo);
		sleeep(philo);
		think(philo);
	}
	return (NULL);
}
