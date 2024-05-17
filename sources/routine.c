/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andre-da <andre-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 21:52:36 by andrealbuqu       #+#    #+#             */
/*   Updated: 2024/05/17 12:44:53 by andre-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	death_check(t_philo *philo)
{
	pthread_mutex_lock(philo->monitor);
	if (!*philo->run_sim)
	{
		pthread_mutex_unlock(philo->monitor);
		return (true);
	}
	pthread_mutex_unlock(philo->monitor);
	return (false);
}

void	*start_routine(void *pointer)
{
	t_philo	*philo;

	philo = (t_philo *)pointer;
	if (philo->id % 2 == 0)
		usleep(100);
	while (true)
	{
		if (death_check(philo) 
			|| philo->times_eaten == philo->parms.times_to_eat)
			break ;
		start_eating(philo);
		start_sleeping(philo);
		start_thinking(philo);
	}
	return (pointer);
}

bool	death_check_success(t_philo *philo, bool taken, bool even)
{
	if (death_check(philo))
	{
		if (even)
		{
			if (taken)
				pthread_mutex_unlock(philo->l_fork);
			pthread_mutex_unlock(philo->r_fork);
		}
		else
		{
			if (taken)
				pthread_mutex_unlock(philo->r_fork);
			pthread_mutex_unlock(philo->l_fork);
		}
		return (true);
	}
	return (false);
}

void	start_eating(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->r_fork);
		if (death_check_success(philo, false, true))
			return ;
		print_philo_state(philo, "has taken a fork", RED);
		pthread_mutex_lock(philo->l_fork);
		if (death_check_success(philo, true, true))
			return ;
		print_philo_state(philo, "has taken a fork", RED);
	}
	else
	{
		pthread_mutex_lock(philo->l_fork);
		if (death_check_success(philo, false, false))
			return ;
		if (!check_right_fork(philo))
			return ;
		pthread_mutex_lock(philo->r_fork);
		if (death_check_success(philo, true, false))
			return ;
		print_philo_state(philo, "has taken a fork", RED);
	}
	print_philo_state(philo, "is eating", GREEN);
	eat(philo);
}

void	start_sleeping(t_philo *philo)
{
	if (death_check(philo))
		return ;
	print_philo_state(philo, "is sleeping", YELLOW);
	ft_sleep(philo->parms.sleep_time, philo);
}
