/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozdemir <ozdemir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 12:11:10 by ozdemir           #+#    #+#             */
/*   Updated: 2024/05/15 16:09:04 by ozdemir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void    create_philos_threads(t_general *general)
{
        int     i;

        i = 0;
        while (i < general->number_of_philosophers)
        {
                pthread_create(&general->philos[i].thread, NULL, philo_cycle, &general->philos[i]);
                i++;
        }
}

void    join_philos_threads(t_general *general)
{
        int     i;

        i = 0;
        while (i < general->number_of_philosophers)
        {
                pthread_join(general->philos[i].thread, NULL);
                i++;
        }
}

int     main(int ac, char **av)
{
        t_general general;

        if (ac < 5 || ac > 6)
                exit_error("Invalid number of args");
        if (init_general(&general, ac, av))
                exit_error("Init error");
        start_death_checker(&general);
        create_philos_threads(&general);
        join_philos_threads(&general);
        join_death_checker(&general);

        destroy_mutexes(&general);
        free(general.forks);
        free(general.philos);
        return (0);
}