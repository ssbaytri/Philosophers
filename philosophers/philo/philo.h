/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 20:44:13 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/06/28 17:25:15 by ssbaytri         ###   ########.fr       */
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
	int				death_flag;
	int				must_eat_count;
	pthread_mutex_t	*forks;
	pthread_mutex_t	meal_mutex;
	pthread_mutex_t	log_mutex;
	pthread_mutex_t	death_mutex;
	struct s_philo	*philos;
}					t_config;

typedef struct s_philo
{
	int				id;
	int				eating;
	int				*dead;
	int				times_eaten;
	int				must_eat_count;
	long			last_meal_time;
	long			start_time;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*meal_mutex;
	pthread_mutex_t	*log_mutex;
	pthread_mutex_t	*death_mutex;
	t_config		*config;
}					t_philo;

int					ft_atoi(const char *str);
int					parse_args(int ac, char **av);
long				get_time_ms(void);
int					init_all(t_config *cfg, char **argv);

int					already_dead(t_philo *philo);
int					ft_usleep(long ms);
void				print_log(t_philo *philo, const char *message);
void				*monitor(void *arg);

void				thinking(t_philo *philo);
void				sleeping(t_philo *philo);
void				eating(t_philo *philo);

int					simulation(t_config *cfg);

#endif