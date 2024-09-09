/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozdemir <ozdemir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 14:17:46 by ozdemir           #+#    #+#             */
/*   Updated: 2024/06/04 15:43:50 by ozdemir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	died(t_general *general, int i)
{
	pthread_mutex_unlock(&general->philos[i].meal_lock);
	message_print(&general->philos[i], "died");
	pthread_mutex_lock(&general->died_mutex);
	general->died = 1;
	pthread_mutex_unlock(&general->died_mutex);
}

int	philo_full(t_general *general, int i)
{
	pthread_mutex_lock(&general->died_mutex);
	if (general->philos[i].eaten_count == general->must_eat_count)
		i++;
	pthread_mutex_unlock(&general->died_mutex);
	if (i == general->number_of_philosophers)
		return (1);
	return (0);
}

void	*check_deaths(void *arg)
{
	int			i;
	t_general	*general;

	general = (t_general *)arg;
	while (!general->died)
	{
		i = 0;
		while (i < general->number_of_philosophers)
		{
			if (philo_full(general, i))
				return (NULL);
			pthread_mutex_lock(&general->philos[i].meal_lock);
			if (get_time_in_ms() - general->start_time
				- general->philos[i].last_meal_time > general->time_to_die)
				died(general, i);
			pthread_mutex_unlock(&general->philos[i].meal_lock);
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}

int	check_init(t_general *general)
{
	if (general->number_of_philosophers == 0 || general->time_to_eat < 0
		|| general->time_to_sleep < 0 || general->time_to_die == 0)
		return (1);
	if (general->number_of_philosophers > INT_MAX
		|| general->time_to_eat > INT_MAX || general->time_to_sleep > INT_MAX
		|| general->time_to_die > INT_MAX)
		return (1);
	return (0);
}

int	args_check(char **av)
{
	int	i;
	int	j;

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
	if (ft_atoi(av[1]) > 200)
		return (1);
	return (0);
}
