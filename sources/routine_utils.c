/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrealbuquerque <andrealbuquerque@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 11:03:36 by andrealbuqu       #+#    #+#             */
/*   Updated: 2024/05/09 15:54:34 by andrealbuqu      ###   ########.fr       */
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

void	ft_sleep(suseconds_t time_to_wait)
{
	suseconds_t	start;

	start = (suseconds_t)get_current_time();
	while (true)
	{
		if (((suseconds_t)get_current_time() - start) >= (suseconds_t)time_to_wait)
			return ;
		usleep (100);
	}
}

bool	check_right_fork(t_philo *philo)
{
	if (!philo->r_fork)
	{
		ft_sleep(philo->parms.die_time);
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_lock(philo->monitor);
		*philo->run_sim = false;
		pthread_mutex_unlock(philo->monitor);
		print_philo_state(philo, "died", ORANGE);
		return (false);
	}
	return (true);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->starvation);
	philo->last_meal = get_current_time();
	pthread_mutex_unlock(&philo->starvation);
	
	// printf("last meal %d (eat): %zu\n", philo->id, philo->last_meal);

	ft_sleep(philo->parms.eat_time);

	pthread_mutex_lock(&philo->meals);
	philo->times_eaten++;
	pthread_mutex_unlock(&philo->meals);

	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
}
