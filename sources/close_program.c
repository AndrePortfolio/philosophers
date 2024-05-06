/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_program.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andre-da <andre-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 23:58:44 by andrealbuqu       #+#    #+#             */
/*   Updated: 2024/05/06 16:52:58 by andre-da         ###   ########.fr       */
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
			pthread_mutex_destroy(&info->forks[i++]);
		free(info->forks);
	}
	if (info->philo)
		free(info->philo);
}
