/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andre-da <andre-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 23:59:06 by andrealbuqu       #+#    #+#             */
/*   Updated: 2024/05/17 11:30:02 by andre-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_parameters	read_input(int argc, char **argv, t_simulation *info)
{
	t_parameters	philo;

	if (argc != 5 && argc != 6)
		error_message("Invalid number of arguments");
	info->philo_nbr = ft_atoi(argv[1]);
	if (info->philo_nbr < 1 || info->philo_nbr > 200)
		error_message("Invalid number of philosophers");
	if (ft_atoi(argv[2]) >= 1)
		philo.die_time = ft_atoi(argv[2]);
	else
		error_message("Invalid death timer");
	if (ft_atoi(argv[3]) >= 1)
		philo.eat_time = ft_atoi(argv[3]);
	else
		error_message("Invalid eat timer");
	if (ft_atoi(argv[4]) >= 1)
		philo.sleep_time = ft_atoi(argv[4]);
	else
		error_message("Invalid sleep timer");
	if (argc == 6)
		optional_argument(argv[5], &philo);
	else
		philo.times_to_eat = -1;
	return (philo);
}

void	optional_argument(char *argv, t_parameters *philo)
{
	if (ft_atoi(argv) >= 1)
		philo->times_to_eat = ft_atoi(argv);
	else
		error_message("Invalid number for times to eat");
}

bool	is_white_space(char c, char *spaces)
{
	int	i;

	i = 0;
	while (spaces[i])
		if (spaces[i++] == c)
			return (true);
	return (false);
}

int	ft_atoi(char *str)
{
	long long	result;
	int			sign;
	int			i;

	result = 0;
	sign = 1;
	i = 0;
	while (is_white_space(str[i], WHITE_SPACES))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i++] == '-')
			sign = -sign;
	}
	while (str[i] >= '0' && str[i] <= '9')
		result = result * 10 + str[i++] - '0';
	while (str[i])
	{
		if ((str[i] && !is_white_space(str[i++], WHITE_SPACES)))
			error_message("Argument is not a valid number");
	}
	if (result > INT_MAX)
		error_message("Number must be an integer");
	return (result * sign);
}
