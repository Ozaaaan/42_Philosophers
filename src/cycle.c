/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozdemir <ozdemir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 10:28:14 by ozdemir           #+#    #+#             */
/*   Updated: 2024/05/15 16:03:39 by ozdemir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void    eat(t_philo *philo)
{
        take_forks(philo);
        pthread_mutex_lock(&philo->meal_lock);
        philo->last_meal_time = get_time_in_ms();
        message_print(philo, "is eating");
        usleep(philo->general->time_to_eat);
        philo->eaten_count++;
        pthread_mutex_unlock(&philo->meal_lock);
        drop_forks(philo);
}

void    sleeep(t_philo *philo)
{
        message_print(philo, "is sleeping");
        usleep(philo->general->time_to_sleep);
}

void    think(t_philo *philo)
{
        message_print(philo, "is thinking");
}

void    *philo_cycle(void *arg)
{
        t_philo *philo = (t_philo *)arg;

        while (!philo->general->died)
        {
                eat(philo);
                sleeep(philo);
                think(philo);
        }
        return (NULL);
}
