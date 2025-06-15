/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 20:42:57 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/06/15 23:47:27 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// | Argument Index | Description                                 | Required? |
// | -------------- | ------------------------------------------- | --------- |
// | `argv[1]`      | `number_of_philosophers`                    | Yes       |
// | `argv[2]`      | `time_to_die` (in ms)                       | Yes       |
// | `argv[3]`      | `time_to_eat` (in ms)                       | Yes       |
// | `argv[4]`      | `time_to_sleep` (in ms)                     | Yes       |
// | `argv[5]`      | `number_of_times_each_philosopher_must_eat` | Optional  |

#include "philo.h"

static int	validate_args(int ac, char **av)
{
	if (ac < 5 || ac > 6 || !parse_args(ac, av))
	{
		printf("Error: Invalid arguments.\n");
		return (0);
	}
	return (1);
}

long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	init_forks(t_config *cfg)
{
	int	i;

	cfg->forks = malloc(sizeof(pthread_mutex_t) * cfg->philo_count);
	if (!cfg->forks)
		return (0);
	i = 0;
	while (i < cfg->philo_count)
	{
		if (pthread_mutex_init(&cfg->forks[i], NULL) != 0)
			return (0);
		i++;
	}
	return (1);
}

int	destroy_forks(t_config *cfg)
{
	int	i;

	if (!cfg->forks)
		return (1);
	i = 0;
	while (i < cfg->philo_count)
	{
		if (pthread_mutex_destroy(&cfg->forks[i]) != 0)
			return (0);
		i++;
	}
	free(cfg->forks);
	cfg->forks = NULL;
	return (1);
}

int	init_config(t_config *cfg, int argc, char **argv)
{
	memset(cfg, 0, sizeof(t_config));
	cfg->philo_count = ft_atoi(argv[1]);
	cfg->time_to_die = ft_atoi(argv[2]);
	cfg->time_to_eat = ft_atoi(argv[3]);
	cfg->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		cfg->must_eat_count = ft_atoi(argv[5]);
	else
		cfg->must_eat_count = -1;
	cfg->stop_simulation = 0;
	cfg->start_time = get_time_ms();
	if (!init_forks(cfg))
	{
		printf("Error: Failed to initialize forks.\n");
		return (0);
	}
	if (pthread_mutex_init(&cfg->print_mutex, NULL) != 0)
		return (0);
	return (1);
}

t_philo	*init_philos(t_config *cfg)
{
	t_philo	*philos;
	int		i;

	philos = malloc(sizeof(t_philo) * cfg->philo_count);
	if (!philos)
		return (NULL);
	i = 0;
	while (i < cfg->philo_count)
	{
		philos[i].id = i;
		philos[i].times_eaten = 0;
		philos[i].last_meal_time = cfg->start_time;
		philos[i].left_fork = &cfg->forks[i];
		philos[i].right_fork = &cfg->forks[(i + 1) % cfg->philo_count];
		philos[i].config = cfg;
		i++;
	}
	return (philos);
}

void	print_action(t_philo *philo, const char *action)
{
	long timestamp;

	pthread_mutex_lock(&philo->config->print_mutex);
	if (!philo->config->stop_simulation)
	{
		timestamp = get_time_ms() - philo->config->start_time;
		printf("%ld %d %s\n", timestamp, philo->id, action);
	}
	pthread_mutex_unlock(&philo->config->print_mutex);
}

void	smart_sleep(int duration, t_philo *philo)
{
	long start;

	start = get_time_ms();
	while (!philo->config->stop_simulation)
	{
		if ((get_time_ms() - start) >= duration)
			break ;
		usleep(100);
	}
}

void take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		print_action(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		print_action(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		print_action(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		print_action(philo, "has taken a fork");
	}
}

void	release_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void start_eating(t_philo *philo)
{
	print_action(philo, "is eating");
	philo->last_meal_time = get_time_ms();
	philo->times_eaten++;
	smart_sleep(philo->config->time_to_eat, philo);
}

int has_eaten_enough(t_philo *philo)
{
	if (philo->config->must_eat_count == -1)
		return (0);
	return (philo->times_eaten >= philo->config->must_eat_count);
}

int	should_stop(t_philo *philo)
{
	int	stop;

	pthread_mutex_lock(&philo->config->stop_mutex);
	stop = philo->config->stop_simulation;
	pthread_mutex_unlock(&philo->config->stop_mutex);
	return (stop);
}


void	*philo_routine(void *arg)
{
	t_philo *philo = (t_philo *)arg;
	if (philo->config->philo_count == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		print_action(philo, "has taken a fork");
		while (!should_stop(philo))
			usleep(100);
		pthread_mutex_unlock(philo->left_fork);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		usleep(100);
	while (!should_stop(philo))
	{
		take_forks(philo);
		start_eating(philo);
		release_forks(philo);
		if (has_eaten_enough(philo))
			break ;
		print_action(philo, "is sleeping");
		smart_sleep(philo->config->time_to_sleep, philo);
		print_action(philo, "is thinking");
	}
	return (NULL);
}

int all_philos_ate(t_philo *philos, t_config *cfg)
{
	int i;
	
	if (cfg->must_eat_count == -1)
		return (0);
	i = 0;
	while (i < cfg->philo_count)
	{
		if (philos[i].times_eaten < cfg->must_eat_count)
			return (0);
		i++;
	}
	return (1);
}

void start_monitor(t_philo *philos, t_config *cfg)
{
	int i;
	long now;

	while (!cfg->stop_simulation)
	{
		i = 0;
		while (i < cfg->philo_count)
		{
			now = get_time_ms();
			if ((now - philos[i].last_meal_time) >= cfg->time_to_die)
			{
				cfg->stop_simulation = 1;
				pthread_mutex_lock(&cfg->print_mutex);
				printf("%ld %d died\n", now - cfg->start_time, philos[i].id);
				pthread_mutex_unlock(&cfg->print_mutex);
				return ;
			}
			i++;
		}
		if (all_philos_ate(philos, cfg))
		{
			cfg->stop_simulation = 1;
			return ;
		}
		usleep(1000);
	}
}

int	main(int argc, char **argv)
{
	t_config	cfg;
	t_philo		*philos;
	int i;

	if (!validate_args(argc, argv))
		return (1);
	if (!init_config(&cfg, argc, argv))
	{
		printf("Error: Failed to initialize config.\n");
		return (1);
	}
	philos = init_philos(&cfg);
	if (!philos)
	{
		printf("Error: Failed to initialize philosophers.\n");
		destroy_forks(&cfg);
		return (1);
	}
	i = 0;
	while (i < cfg.philo_count)
	{
		if (pthread_create(&philos[i].thread, NULL, philo_routine, &philos[i]) != 0)
		{
			printf("Error: Failed to create philosopher thread.\n");
			free(philos);
			destroy_forks(&cfg);
			return (1);
		}
		i++;
	}
	start_monitor(philos, &cfg);
	i = 0;
	while (i < cfg.philo_count)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
	destroy_forks(&cfg);
	free(philos);
	return (0);
}
