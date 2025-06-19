/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 20:44:13 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/06/19 07:43:57 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_config
{
	int				philo_count;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int 			time_to_think;
	int				must_eat_count;
	int 			philo_full_count;
	int				meal_exist;
	long			start_time;
	int				stop_simulation;
	pthread_mutex_t	*forks;
	pthread_mutex_t	eat_mutex;
	pthread_mutex_t	stop_mutex;
	pthread_mutex_t time_mutex;
	pthread_mutex_t	print_mutex;
}					t_config;

typedef struct s_philo
{
	int				id;
	int				times_eaten;
	long			last_meal_time;
	int				full;
	pthread_t		thread;
	t_config		*config;
}					t_philo;

int					ft_atoi(const char *str);
int					parse_args(int ac, char **av);

#endif