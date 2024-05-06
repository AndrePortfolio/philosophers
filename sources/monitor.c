/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andre-da <andre-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 18:16:51 by andrealbuqu       #+#    #+#             */
/*   Updated: 2024/05/06 19:59:59 by andre-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor(void *pointer)
{
	t_simulation	*info;
	int				i;

	info = (t_simulation *)pointer;
	i = 0;
	while (true)
	{
		pthread_mutex_lock(&info->philo[i].eat_count);
		if (info->philo[i].parms.times_to_eat || info->philo[i].alive == false)
		{
			pthread_mutex_unlock(&info->philo[i].eat_count);
			break ;
		}
		i++;
		if (i == info->philo_nbr)
			i = 0;
		pthread_mutex_unlock(&info->philo[i].eat_count);
	}
	return (pointer);
}
