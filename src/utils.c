/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozdemir <ozdemir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 11:45:22 by ozdemir           #+#    #+#             */
/*   Updated: 2024/05/15 16:09:11 by ozdemir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

long long	get_time_in_ms(void)
{
	struct timeval time;
	gettimeofday(&time, NULL);
	return(time.tv_sec * 1000) + (time.tv_usec / 1000);
}

void	message_print(t_philo *philo, char *str)
{
	long	time;

	pthread_mutex_lock(&philo->general->died_mutex);
	if (!philo->general->died)
	{
		time = get_time_in_ms() - philo->general->start_time;
		printf("%1ld %d %s\n", time, philo->id, str);
	}
	pthread_mutex_unlock(&philo->general->died_mutex);
}

void	exit_error(char *msg)
{
	write(2, "Error\n", 6);
	write(STDERR_FILENO, msg, ft_strlen(msg));
	write(STDERR_FILENO, "\n", 1);
	exit(EXIT_FAILURE);
}

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork->lock);
	message_print(philo, "has taken a fork");
	pthread_mutex_lock(&philo->right_fork->lock);
	message_print(philo, "has taken a fork");
}

void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->left_fork->lock);
	pthread_mutex_unlock(&philo->right_fork->lock);
}