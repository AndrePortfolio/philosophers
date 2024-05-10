/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andre-da <andre-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 18:16:51 by andrealbuqu       #+#    #+#             */
/*   Updated: 2024/05/10 17:01:09 by andre-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	is_satisfied(t_simulation *info)
{
	int	i;

	i = 0;
	while (i < info->philo_nbr)
	{
		pthread_mutex_lock(&info->philo[i].meals);
		if (info->philo->parms.times_to_eat != info->philo[i].times_eaten)
		{
			pthread_mutex_unlock(&info->philo[i].meals);
			return ;
		}
		pthread_mutex_unlock(&info->philo[i].meals);
		i++;
	}
	pthread_mutex_lock(&info->monitor);
	info->run_sim = false;
	pthread_mutex_unlock(&info->monitor);
}

bool	is_dead(t_simulation *info)
{
	int	i;

	i = 0;
	while (i < info->philo_nbr)
	{
		pthread_mutex_lock(&info->philo[i].starvation);
		if ((get_current_time() - info->philo[i].last_meal)
			> info->philo[i].parms.die_time)
		{
			pthread_mutex_unlock(&info->philo[i].starvation);
			pthread_mutex_lock(&info->monitor);
			info->run_sim = false;
			pthread_mutex_unlock(&info->monitor);

			if (info->philo[i].r_fork)
				print_philo_state(&info->philo[i], "died", ORANGE);
			return (true);
		}
		pthread_mutex_unlock(&info->philo[i].starvation);
		i++;
	}
	return (false);
}

void	*monitor(void *pointer)
{
	t_simulation	*info;

	info = (t_simulation *)pointer;
	pthread_mutex_lock(&info->monitor);
	while (info->run_sim)
	{
		pthread_mutex_unlock(&info->monitor);
		if (is_dead(info))
			return (pointer);
		if (info->philo->parms.times_to_eat != -1)
			is_satisfied(info);
		pthread_mutex_lock(&info->monitor);
	}
	pthread_mutex_unlock(&info->monitor);
	return (pointer);
}
