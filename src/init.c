/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozdemir <ozdemir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 15:06:58 by ozdemir           #+#    #+#             */
/*   Updated: 2024/05/15 16:05:39 by ozdemir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void    init_forks(t_fork *forks, t_general *general)
{
        int     i;

        i = 0;
        while (i < general->number_of_philosophers)
        {
                forks[i].used = 0;
                pthread_mutex_init(&forks[i].lock, NULL);
        }
}

int     init_general(t_general *general, int ac, char **av)
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
        general->start_time = get_time_in_ms();
        pthread_mutex_init(&general->died_mutex, NULL);

        general->forks = malloc(sizeof(t_fork) * general->number_of_philosophers);
        if (!general->forks)
                return(1);
        
        general->philos = malloc(sizeof(t_philo) * general->number_of_philosophers);
        if (!general->philos)
                return(1);

        init_forks(general->forks, general);
        init_philos(general->philos, general->forks, general);
        
        return (0);
}

void init_philos(t_philo *philos, t_fork *forks, t_general *general)
{
        int     i;

        i = 0;
        while (i < general->number_of_philosophers)
        {
                philos[i].id = i + 1;
                philos[i].using_left = 0;
                philos[i].using_right = 0;
                philos[i].last_meal_time = 0;
                philos[i].eaten_count = 0;
                philos[i].left_fork = &forks[i];
                philos[i].right_fork = &forks[(i + 1) % general->number_of_philosophers];
                pthread_mutex_init(&philos->meal_lock, NULL);
                philos[i].general = general;
        }
}

void    destroy_mutexes(t_general *general)
{
        int     i;

        i = 0;
        while (i < general->number_of_philosophers)
        {
                pthread_mutex_destroy(&general->forks[i].lock);
                pthread_mutex_destroy(&general->philos[i].meal_lock);
        }
        pthread_mutex_destroy(&general->died_mutex);
}