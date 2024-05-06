/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andre-da <andre-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 00:23:54 by andrealbuqu       #+#    #+#             */
/*   Updated: 2024/05/06 15:29:49 by andre-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_simulation	info;
	t_parameters	philo;

	philo = read_input(argc, argv, &info);
	init_forks(&info);
	init_philos(&info, philo);
	init_simulation(&info);
	free_all(&info);
	return (0);
}
