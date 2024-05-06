/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrealbuquerque <andrealbuquerque@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 18:16:51 by andrealbuqu       #+#    #+#             */
/*   Updated: 2024/04/25 18:17:01 by andrealbuqu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor(void *pointer)
{
	t_simulation	*info;
	int				i;

	info = (t_simulation *)pointer;
	i = 0;
	while (info->philo->parms.times_to_eat)
	{
		if (info->philo[i++].alive == false)
		{
			i = 0;
			while (i < info->philo_nbr)
				if (pthread_detach(info->philo[i++].thread) != 0)
					error_message("Failed to detach thread");
			return (pointer);
		}
		if (i == info->philo_nbr)
			i = 0;
	}
	return (pointer);
}
