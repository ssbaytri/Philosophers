/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 20:51:28 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/07/01 21:52:36 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <fcntl.h>
# include <limits.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_config
{
	int			philo_count;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			must_eat_count;
	long		start_time;
	pid_t		*philos;
	sem_t		*forks;
	sem_t		*log_sem;
	sem_t		*death_sem;
	sem_t		*meal_sem;
}				t_config;

typedef struct s_philo
{
	int			id;
	int			times_eaten;
	long		last_meal_time;
	t_config	*config;
}				t_philo;

int				parse_args(int ac, char **av);
int				ft_atoi(const char *str);
long			get_time_ms(void);
int				ft_usleep(long ms);
void			print_log(t_philo *philo, const char *message);

void			cleanup_semaphores(void);
int				init_all(t_config *cfg, char **argv);

void			thinking(t_philo *philo);
void			sleeping(t_philo *philo);
void			eating(t_philo *philo);

void			philo_routine(t_philo *philo);
int				simulation(t_config *cfg);

#endif