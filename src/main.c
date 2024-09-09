/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozdemir <ozdemir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 12:11:10 by ozdemir           #+#    #+#             */
/*   Updated: 2024/06/03 12:01:39 by ozdemir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

int	ft_usleep(size_t milliseconds, t_philo *philo)
{
	size_t	start;
	int		dead;

	start = get_time_in_ms();
	while ((get_time_in_ms() - start) < milliseconds)
	{
		pthread_mutex_lock(&(philo->general->died_mutex));
		dead = philo->general->died;
		pthread_mutex_unlock(&(philo->general->died_mutex));
		if (dead == 1)
			break ;
		usleep(500);
	}
	return (0);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	exit_error(char *msg)
{
	write(2, "Error\n", 6);
	write(STDERR_FILENO, msg, ft_strlen(msg));
	write(STDERR_FILENO, "\n", 1);
	exit(EXIT_FAILURE);
}

int	main(int ac, char **av)
{
	t_general	general;

	if (ac < 5 || ac > 6)
		exit_error("Invalid number of args");
	if (args_check(av))
		exit_error("Invalid arg");
	if (init_general(&general, ac, av))
		exit_error("Init error");
	if (init_mutex(&general))
		exit_error("Mutex init error");
	if (init_philos(&general))
		exit_error("Philo init error");
	if (create_thread(&general))
	{
		free_all(&general);
		exit_error("Thread error");
	}
	free_all(&general);
	pthread_exit(NULL);
	return (0);
}
