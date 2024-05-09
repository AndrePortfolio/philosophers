/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrealbuquerque <andrealbuquerque@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 21:52:36 by andrealbuqu       #+#    #+#             */
/*   Updated: 2024/05/09 16:11:15 by andrealbuqu      ###   ########.fr       */
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
		if (death_check(philo))
			break ;
		start_eating(philo);
		start_sleeping(philo);
		start_thinking(philo);
	}
	return (pointer);
}

void	start_eating(t_philo *philo)
{
	// if (philo->id % 2 == 0)
	// {
	// 	pthread_mutex_lock(philo->r_fork);
	// 	print_philo_state(philo, "has taken a fork", RED);
	// 	pthread_mutex_lock(philo->l_fork);
	// 	print_philo_state(philo, "has taken a fork", RED);
	// }
	// else
	// {
		pthread_mutex_lock(philo->l_fork);
		print_philo_state(philo, "has taken a fork", RED);
		if (!check_right_fork(philo))
			return ;
		pthread_mutex_lock(philo->r_fork);
		print_philo_state(philo, "has taken a fork", RED);
	// }
	print_philo_state(philo, "is eating", GREEN);
	eat(philo);
}

void	start_sleeping(t_philo *philo)
{
	if (death_check(philo))
		return ;
	print_philo_state(philo, "is sleeping", YELLOW);
	ft_sleep(philo->parms.sleep_time);
}

void	start_thinking(t_philo *philo)
{
	if (death_check(philo))
		return ;
	print_philo_state(philo, "is thinking", CYAN);
}

void	print_philo_state(t_philo *philo, char *msg, char *color)
{
	size_t	time;

	time = get_current_time() - philo->start_time;
	if (time / 100 > 0.5)
	{
		if (philo->id / 10 > 0.5)
			printf("%s%zu%s %d%s %s%s\n", BLUE, time, RESET,
				philo->id, color, msg, RESET);
		else
			printf("%s%zu%s %d%s  %s%s\n", BLUE, time, RESET,
				philo->id, color, msg, RESET);
	}
	else if (time / 10 > 0.5)
	{
		if (philo->id / 10 > 0.5)
			printf("%s%zu%s  %d%s %s%s\n", BLUE, time, RESET,
				philo->id, color, msg, RESET);
		else
			printf("%s%zu%s  %d%s  %s%s\n", BLUE, time, RESET,
				philo->id, color, msg, RESET);
	}
	else
	{
		if (philo->id / 10 > 0.5)
			printf("%s%zu%s   %d%s %s%s\n", BLUE, time, RESET,
				philo->id, color, msg, RESET);
		else
			printf("%s%zu%s   %d%s  %s%s\n", BLUE, time, RESET,
				philo->id, color, msg, RESET);
	}
}
