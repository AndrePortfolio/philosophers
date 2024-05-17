/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_program.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andre-da <andre-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 21:48:20 by andrealbuqu       #+#    #+#             */
/*   Updated: 2024/05/17 16:10:08 by andre-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_simulation(t_simulation *info)
{
	int	i;

	i = 0;
	while (i < info->philo_nbr)
	{
		if (pthread_create(&info->philo[i].thread, NULL, start_routine,
				(void *)&info->philo[i]) != 0)
			error_message("Failed to create philo thread");
		i++;
	}
	if (pthread_create(&info->thread, NULL, monitor, (void *)info) != 0)
		error_message("Failed to create monitor thread");
	i = 0;
	while (i < info->philo_nbr)
		pthread_join(info->philo[i++].thread, NULL);
	if (pthread_join(info->thread, NULL) != 0)
		error_message("Failed to join monitor thread");
}

void	init_forks(t_simulation *info)
{
	int	i;

	info->forks = malloc(sizeof(pthread_mutex_t) * info->philo_nbr);
	if (!info->forks)
		error_message("Failed to allocate memory for philosophers");
	i = 0;
	while (i < info->philo_nbr)
		if (pthread_mutex_init(&info->forks[i++], NULL) != 0)
			error_message("Failed to initialize fork mutex");
}

void	philo_struct(t_simulation *info, t_parameters philo, int i)
{
	info->philo[i].id = i + 1;
	info->philo[i].run_sim = &info->run_sim;
	info->philo[i].start_time = get_current_time();
	info->philo[i].last_meal = info->philo[i].start_time;
	info->philo[i].parms = philo;
	info->philo[i].times_eaten = 0;
	info->philo[i].monitor = &info->monitor;
	info->philo[i].print = &info->print;
	info->philo[i].l_fork = &info->forks[i];
	if (info->philo_nbr == 1 && i == 0)
		info->philo[i].r_fork = NULL;
	else if (i == info->philo_nbr - 1)
		info->philo[i].r_fork = &info->forks[0];
	else
		info->philo[i].r_fork = &info->forks[i + 1];
	pthread_mutex_init(&info->philo[i].meals, NULL);
	pthread_mutex_init(&info->philo[i].starvation, NULL);
}

void	init_philos(t_simulation *info, t_parameters philo)
{
	int		i;

	info->run_sim = true;
	pthread_mutex_init(&info->monitor, NULL);
	pthread_mutex_init(&info->print, NULL);
	info->philo = (t_philo *)malloc(sizeof(t_philo) * info->philo_nbr);
	if (!info->philo)
		error_message("Failed to allocate memory for philosophers");
	i = 0;
	while (i < info->philo_nbr)
		philo_struct(info, philo, i++);
}
