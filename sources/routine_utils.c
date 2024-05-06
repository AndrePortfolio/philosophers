/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrealbuquerque <andrealbuquerque@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 11:03:36 by andrealbuqu       #+#    #+#             */
/*   Updated: 2024/04/25 18:18:45 by andrealbuqu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		error_message("Error extracting time of day");
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

bool	wait_turn(t_philo *philo)
{
	if ((philo->parms.eat_time > philo->parms.die_time))
	{
		usleep(philo->parms.die_time * 1000);
		print_philo_state(philo, "died", ORANGE);
		philo->alive = false;
		return (false);
	}
	usleep(100);
	return (true);
}

bool	check_if_dead(t_philo *philo)
{
	if (get_current_time() - philo->last_meal > philo->parms.die_time)
	{
		print_philo_state(philo, "died", ORANGE);
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
		philo->alive = false;
		return (true);
	}
	return (false);
}

bool	check_right_fork(t_philo *philo)
{
	if (!philo->r_fork)
	{
		usleep(philo->parms.die_time * 1000);
		print_philo_state(philo, "died", ORANGE);
		pthread_mutex_unlock(philo->l_fork);
		philo->alive = false;
		return (false);
	}
	return (true);
}

void	eat(t_philo *philo)
{
	philo->last_meal = get_current_time();
	usleep(philo->parms.eat_time * 1000);
	philo->parms.times_to_eat--;
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
}