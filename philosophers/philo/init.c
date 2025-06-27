/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 13:47:26 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/06/27 16:16:53 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_args(t_config *cfg, char **argv)
{
	cfg->philo_count = ft_atoi(argv[1]);
	cfg->time_to_die = ft_atoi(argv[2]);
	cfg->time_to_eat = ft_atoi(argv[3]);
	cfg->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		cfg->must_eat_count = ft_atoi(argv[5]);
	else
		cfg->must_eat_count = -1;
}

static int	init_philos(t_config *cfg)
{
	int	i;

	cfg->philos = malloc(sizeof(t_philo) * cfg->philo_count);
	if (!cfg->philos)
		return (0);
	i = 0;
	while (i < cfg->philo_count)
	{
		cfg->philos[i].id = i + 1;
		cfg->philos[i].eating = 0;
		cfg->philos[i].times_eaten = 0;
		cfg->philos[i].must_eat_count = cfg->must_eat_count;
		cfg->philos[i].start_time = get_time_ms();
		cfg->philos[i].last_meal_time = get_time_ms();
		cfg->philos[i].log_mutex = &cfg->log_mutex;
		cfg->philos[i].meal_mutex = &cfg->meal_mutex;
		cfg->philos[i].death_mutex = &cfg->death_mutex;
		cfg->philos[i].dead = &cfg->death_flag;
		cfg->philos[i].left_fork = &cfg->forks[i];
		cfg->philos[i].right_fork = &cfg->forks[(i + 1) % cfg->philo_count];
		cfg->philos[i].config = cfg;
		i++;
	}
	return (1);
}

static int	init_forks(t_config *cfg)
{
	int	i;

	i = 0;
	cfg->forks = malloc(sizeof(pthread_mutex_t) * cfg->philo_count);
	if (!cfg->forks)
		return (0);
	while (i < cfg->philo_count)
	{
		pthread_mutex_init(&cfg->forks[i], NULL);
		i++;
	}
	return (1);
}

int	init_all(t_config *cfg, char **argv)
{
	cfg->death_flag = 0;
	pthread_mutex_init(&cfg->meal_mutex, NULL);
	pthread_mutex_init(&cfg->log_mutex, NULL);
	pthread_mutex_init(&cfg->death_mutex, NULL);
	init_args(cfg, argv);
	if (!init_forks(cfg))
		return (0);
	if (!init_philos(cfg))
		return (0);
	return (1);
}
