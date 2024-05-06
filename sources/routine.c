/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrealbuquerque <andrealbuquerque@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 21:52:36 by andrealbuqu       #+#    #+#             */
/*   Updated: 2024/04/25 21:03:27 by andrealbuqu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*start_routine(void *pointer)
{
	t_philo	*philo;

	philo = (t_philo *)pointer;
	if (philo->id % 2 == 0)
		if (!wait_turn(philo))
			return (pointer);
	while (philo->alive && philo->parms.times_to_eat)
	{
		start_eating(philo);
		if (philo->alive)
		{
			start_sleeping(philo);
			start_thinking(philo);
		}
	}
	return (pointer);
}

void	start_eating(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	print_philo_state(philo, "has taken a fork", RED);
	if (!check_right_fork(philo))
		return ;
	pthread_mutex_lock(philo->r_fork);
	print_philo_state(philo, "has taken a fork", RED);
	if (check_if_dead(philo))
		return ;
	print_philo_state(philo, "is eating", GREEN);
	eat(philo);
}

void	start_sleeping(t_philo *philo)
{
	print_philo_state(philo, "is sleeping", YELLOW);
	usleep(philo->parms.sleep_time * 1000);
}

void	start_thinking(t_philo *philo)
{
	print_philo_state(philo, "is thinking", CYAN);
}

void	print_philo_state(t_philo *philo, char *msg, char *color)
{
	size_t	time;

	time = get_current_time() - philo->start_time;
	if (time / 100 > 0.5)
		printf("%s%zu%s %d%s %s%s\n", BLUE, time, RESET,
			philo->id, color, msg, RESET);
	else if (time / 10 > 0.5)
		printf("%s%zu%s  %d%s %s%s\n", BLUE, time, RESET,
			philo->id, color, msg, RESET);
	else
		printf("%s%zu%s   %d%s %s%s\n", BLUE, time, RESET,
			philo->id, color, msg, RESET);
}