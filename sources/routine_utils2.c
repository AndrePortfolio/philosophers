/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andre-da <andre-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 16:51:46 by andrealbuqu       #+#    #+#             */
/*   Updated: 2024/05/17 16:07:23 by andre-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	start_thinking(t_philo *philo)
{
	if (death_check(philo))
		return ;
	print_philo_state(philo, "is thinking", CYAN);
}

void	single_digit(t_philo *philo, char *msg, char *color, size_t time)
{
	if (philo->id / 10 > 0.5)
		printf("%s%zu%s   %d%s %s%s\n", BLUE, time, RESET,
			philo->id, color, msg, RESET);
	else
		printf("%s%zu%s   %d%s  %s%s\n", BLUE, time, RESET,
			philo->id, color, msg, RESET);
}

void	print_philo_state(t_philo *philo, char *msg, char *color)
{
	size_t	time;

	time = get_current_time() - philo->start_time;
	pthread_mutex_lock(philo->print);
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
		single_digit(philo, msg, color, time);
	pthread_mutex_unlock(philo->print);
}
