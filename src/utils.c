/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozdemir <ozdemir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 11:45:22 by ozdemir           #+#    #+#             */
/*   Updated: 2024/06/07 13:54:33 by ozdemir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

long long	get_time_in_ms(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	message_print(t_philo *philo, char *str)
{
	long	time;

	time = get_time_in_ms() - philo->general->start_time;
	pthread_mutex_lock(&philo->general->died_mutex);
	if (!philo->general->died)
		printf("%1ld %d %s\n", time, philo->id, str);
	pthread_mutex_unlock(&philo->general->died_mutex);
}

long long	ft_atoi(const char *str)
{
	int			i;
	int			signe;
	long long	res;

	i = 0;
	signe = 1;
	res = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			signe = -signe;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = (res * 10) + (str[i] - '0');
		i++;
	}
	return (signe * res);
}

void	take_forks(t_philo *philo)
{
	if (philo->left_fork->number < philo->right_fork->number)
	{
		pthread_mutex_lock(&philo->left_fork->lock);
		message_print(philo, "has taken a fork");
		if (philo->general->number_of_philosophers == 1)
		{
			usleep(philo->general->time_to_die * 2000);
			return ;
		}
		pthread_mutex_lock(&philo->right_fork->lock);
		message_print(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&philo->right_fork->lock);
		message_print(philo, "has taken a fork");
		if (philo->general->number_of_philosophers == 1)
		{
			usleep(philo->general->time_to_die * 2000);
			return ;
		}
		pthread_mutex_lock(&philo->left_fork->lock);
		message_print(philo, "has taken a fork");
	}
}

void	drop_forks(t_philo *philo)
{
	if (philo->left_fork->number < philo->right_fork->number)
	{
		pthread_mutex_unlock(&philo->left_fork->lock);
		pthread_mutex_unlock(&philo->right_fork->lock);
	}
	else
	{
		pthread_mutex_unlock(&philo->right_fork->lock);
		pthread_mutex_unlock(&philo->left_fork->lock);
	}
}
