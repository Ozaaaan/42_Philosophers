/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozdemir <ozdemir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 14:17:46 by ozdemir           #+#    #+#             */
/*   Updated: 2024/05/15 16:11:35 by ozdemir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void *check_deaths(void *arg)
{
        int     i;

        i = 0;
        t_general *general = (t_general *)arg;
        while (!general->died)
        {
                while (i < general->number_of_philosophers)
                {
                        pthread_mutex_lock(&general->philos[i].meal_lock);
                        if (get_time_in_ms() - general->philos[i].last_meal_time > general->time_to_die)
                        {
                                pthread_mutex_lock(&general->died_mutex);
                                general->died = 1;
                                message_print(&general->philos[i], "died");
                                pthread_mutex_unlock(&general->died_mutex);
                        }
                        pthread_mutex_unlock(&general->philos[i].meal_lock);
                }
                usleep(1000);
        }
        return NULL;
}

void    start_death_checker(t_general *general)
{
        pthread_create(&general->death_thread, NULL, check_deaths, general);
}

void    join_death_checker(t_general *general)
{
        pthread_join(general->death_thread, NULL);
}

int     args_check(char **av)
{
        int     i;
        int     j;

        i = 1;
        while (av[i])
        {
                j = 0;
                while (av[i][j])
                {
                        if (av[i][j] < '0' || av[i][j] > '9')
                                return (1);
                        j++;
                }
                i++;
        }
        return (0);
}