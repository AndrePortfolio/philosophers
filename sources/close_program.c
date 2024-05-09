/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_program.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrealbuquerque <andrealbuquerque@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 23:58:44 by andrealbuqu       #+#    #+#             */
/*   Updated: 2024/05/08 23:52:39 by andrealbuqu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	error_message(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		write(2, &str[i++], 1);
	write(2, "\n", 1);
	exit (1);
}

void	free_all(t_simulation *info)
{
	int	i;

	i = 0;
	if (info->forks)
	{
		while (i < info->philo_nbr)
		{
			pthread_mutex_destroy(&info->forks[i]);
			pthread_mutex_destroy(&info->philo[i].meals);
			pthread_mutex_destroy(&info->philo[i].starvation);
			i++;
		}
		free(info->forks);
	}
	pthread_mutex_destroy(&info->monitor);
	if (info->philo)
		free(info->philo);
}
