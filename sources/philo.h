/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andre-da <andre-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 00:22:37 by andrealbuqu       #+#    #+#             */
/*   Updated: 2024/05/17 12:45:06 by andre-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdbool.h>
# include <limits.h>

# define WHITE_SPACES " \n\v\t\r\f"

# define RED "\x1b[31m"
# define GREEN "\x1b[32m"
# define YELLOW "\x1b[33m"
# define CYAN "\x1b[36m"
# define BLUE "\x1b[34m"
# define ORANGE "\x1b[38;5;208m"
# define RESET "\x1b[0m"

typedef struct s_parameters
{
	size_t			die_time;
	size_t			eat_time;
	size_t			sleep_time;
	int				times_to_eat;
}					t_parameters;

typedef struct s_philo
{
	int				id;
	bool			*run_sim;
	pthread_t		thread;
	size_t			start_time;
	size_t			last_meal;
	int				times_eaten;
	t_parameters	parms;
	pthread_mutex_t	meals;
	pthread_mutex_t	starvation;
	pthread_mutex_t	*monitor;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
}					t_philo;

typedef struct s_simulation
{
	pthread_t		thread;
	int				philo_nbr;
	bool			run_sim;
	t_philo			*philo;
	pthread_mutex_t	monitor;
	pthread_mutex_t	*forks;
}					t_simulation;

/*-------------------------------Read Input----------------------------------*/
/*---------------------------------------------------------------------------*/
t_parameters	read_input(int argc, char **argv, t_simulation *info);
bool			is_white_space(char c, char *spaces);
void			optional_argument(char *argv, t_parameters *philo);
int				ft_atoi(char *str);

/*-------------------------------Initialize----------------------------------*/
/*---------------------------------------------------------------------------*/
void			init_philos(t_simulation *info, t_parameters philo);
void			init_forks(t_simulation *info);
void			init_simulation(t_simulation *info);
void			philo_struct(t_simulation *info, t_parameters philo, int i);

/*---------------------------------Routine-----------------------------------*/
/*---------------------------------------------------------------------------*/
void			*start_routine(void *philo);
void			start_eating(t_philo *philo);
void			start_sleeping(t_philo *philo);
void			start_thinking(t_philo *philo);
void			*monitor(void *pointer);
void			print_philo_state(t_philo *philo, char *msg, char *color);
size_t			get_current_time(void);
bool			check_right_fork(t_philo *philo);
void			eat(t_philo *philo);
void			ft_sleep(suseconds_t time_to_wait, t_philo *philo);
bool			death_check(t_philo *philo);
bool			death_check_success(t_philo *philo, bool taken, bool even);

/*------------------------------Close Program--------------------------------*/
/*---------------------------------------------------------------------------*/
void			error_message(char *str);
void			free_all(t_simulation *info);

#endif
