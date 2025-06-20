/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 20:42:57 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/06/20 03:38:14 by ssbaytri         ###   ########.fr       */
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

static int init_config(t_config *cfg, int ac, char **av)
{
	memset(cfg, 0, sizeof(t_config));
	cfg->philo_count = ft_atoi(av[1]);
	cfg->time_to_die = ft_atoi(av[2]);
	cfg->time_to_eat = ft_atoi(av[3]);
	cfg->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		cfg->must_eat_count = ft_atoi(av[5]);
	else
		cfg->must_eat_count = -1;
	if (pthread_mutex_init(&cfg->time_mutex, NULL) ||
		pthread_mutex_init(&cfg->stop_mutex, NULL) ||
		pthread_mutex_init(&cfg->print_mutex, NULL) ||
		pthread_mutex_init(&cfg->eat_mutex, NULL))
		return (0);
	cfg->philo_full_count = 0;
	cfg->stop_simulation = 0;
	cfg->start_time = get_time_ms();
	cfg->time_to_think = cfg->time_to_die - cfg->time_to_sleep;
	if (cfg->philo_count % 2 != 0)
		cfg->time_to_think += cfg->time_to_eat;
	return (1);
}

void init_philos(t_config *cfg, t_philo **philos)
{
	int i;

	i = 0;
	while (i < cfg->philo_count)
	{
		(*philos)[i].id = i;
		(*philos)[i].config = cfg;
		(*philos)[i].times_eaten = 0;
		(*philos)[i].last_meal_time = get_time_ms();
		(*philos)[i].full = 0;
		i++;
	}
}

int init_forks(t_config *cfg)
{
	int i;

	i = 0;
	while (i < cfg->philo_count)
	{
		if (pthread_mutex_init(&cfg->forks[i], NULL))
		{
			printf("Error: Failed to initialize mutex for fork %d.\n", i);
			return (0);
		}
		i++;
	}
	return (1);
}

int setup(t_config *cfg, t_philo **philos)
{
	*philos = malloc(sizeof(t_philo) * cfg->philo_count);
	if (!*philos)
	{
		printf("Error: Failed to allocate memory for philosophers.\n");
		return (0);
	}
	init_philos(cfg, philos);
	cfg->forks = malloc(sizeof(pthread_mutex_t) * cfg->philo_count);
	if (!cfg->forks)
	{
		printf("Error: Failed to allocate memory for forks.\n");
		free(*philos);
		return (0);
	}
	if (!init_forks(cfg))
	{
		free(cfg->forks);
		free(*philos);
		return (0);
	}
	return (1);
}

void smart_sleep(long duration)
{
	long start;

	start = get_time_ms();
	while ((get_time_ms() - start) < duration)
		usleep(100);
}

void print_action(char *action, t_philo *philo)
{
	pthread_mutex_lock(&philo->config->print_mutex);
	pthread_mutex_lock(&philo->config->stop_mutex);
	if (philo->config->stop_simulation)
	{
		pthread_mutex_unlock(&philo->config->print_mutex);
		pthread_mutex_unlock(&philo->config->stop_mutex);
		return ;
	}
	pthread_mutex_unlock(&philo->config->stop_mutex);
	printf("%ld %d %s\n", get_time_ms() - philo->config->start_time, philo->id + 1, action);
	pthread_mutex_unlock(&philo->config->print_mutex);
}

void *philo_routine(void *arg)
{
	t_philo *philo;	
	t_config *cfg;
	
	philo =  (t_philo *)arg;
	cfg = philo->config;
	if (cfg->philo_count == 1)
	{
		pthread_mutex_lock(&cfg->forks[philo->id]);
		print_action("has taken a fork", philo);
		smart_sleep(cfg->time_to_die);
		pthread_mutex_unlock(&cfg->forks[philo->id]);
		return (NULL);
	}
	while (1)
	{
		pthread_mutex_lock(&cfg->stop_mutex);
		if (cfg->stop_simulation)
		{
			pthread_mutex_unlock(&cfg->stop_mutex);
			break ;
		}
		pthread_mutex_unlock(&cfg->stop_mutex);
		print_action("is thinking", philo);
		if (philo->id % 2 == 0)
		{
			pthread_mutex_lock(&cfg->forks[philo->id]);
			print_action("has taken a fork", philo);
			pthread_mutex_lock(&cfg->forks[(philo->id + 1) % cfg->philo_count]);
			print_action("has taken a fork", philo);
		}
		else
		{
			pthread_mutex_lock(&cfg->forks[(philo->id + 1) % cfg->philo_count]);
			print_action("has taken a fork", philo);
			pthread_mutex_lock(&cfg->forks[philo->id]);
			print_action("has taken a fork", philo);
		}
		print_action("is eating", philo);
		pthread_mutex_lock(&cfg->time_mutex);
		philo->last_meal_time = get_time_ms();
		pthread_mutex_unlock(&cfg->time_mutex);
		
		smart_sleep(cfg->time_to_eat);
		
		pthread_mutex_lock(&cfg->eat_mutex);
		philo->times_eaten++;
		if (cfg->must_eat_count > 0 && philo->times_eaten >= cfg->must_eat_count && !philo->full)
		{
			philo->full = 1;
			cfg->philo_full_count++;
		}
		pthread_mutex_unlock(&cfg->eat_mutex);
		
		pthread_mutex_unlock(&cfg->forks[philo->id]);
		pthread_mutex_unlock(&cfg->forks[(philo->id + 1) % cfg->philo_count]);

		print_action("is sleeping", philo);
		smart_sleep(cfg->time_to_sleep);
	}
	return (NULL);
}

void *monitor(void *arg)
{
	t_config *cfg;
	int i;

	cfg = (t_config *)arg;
	if (cfg->philo_count == 1)
	{
		smart_sleep(cfg->time_to_die);
		print_action("died", &cfg->philos[0]);
		pthread_mutex_lock(&cfg->stop_mutex);
		cfg->stop_simulation = 1;
		pthread_mutex_unlock(&cfg->stop_mutex);
		return (NULL);
	}
	while (1)
	{
		pthread_mutex_lock(&cfg->eat_mutex);
		if (cfg->must_eat_count > 0 && cfg->philo_full_count == cfg->philo_count)
		{
			pthread_mutex_unlock(&cfg->eat_mutex);
			pthread_mutex_lock(&cfg->stop_mutex);
			cfg->stop_simulation = 1;
			pthread_mutex_unlock(&cfg->stop_mutex);
			break ;	
		}
		pthread_mutex_unlock(&cfg->eat_mutex);
		
		for (i = 0; i < cfg->philo_count; i++)
		{
			pthread_mutex_lock(&cfg->time_mutex);
			long time_since_eat = get_time_ms() - cfg->philos[i].last_meal_time;
			pthread_mutex_unlock(&cfg->time_mutex);

			if (time_since_eat > cfg->time_to_die)
			{
				print_action("died", &cfg->philos[i]);
				pthread_mutex_lock(&cfg->stop_mutex);
				cfg->stop_simulation = 1;
				pthread_mutex_unlock(&cfg->stop_mutex);
				return (NULL);
			}
		}
		usleep(1000);
	}
	return (NULL);
}

int main(int ac, char **av)
{
	t_config	cfg;
	t_philo		*philos;
	int i;
	pthread_t monitor_thread;
	
	if (!validate_args(ac, av))
		return (1);
	if (!init_config(&cfg, ac, av))
	{
		printf("Error: Failed to initialize configuration.\n");
		return (1);
	}
	if (!setup(&cfg, &philos))
		return (1);
	i = -1;
	cfg.philos = philos;
	while (++i < cfg.philo_count)
		pthread_create(&philos[i].thread, NULL, philo_routine, &philos[i]);
	pthread_create(&monitor_thread, NULL, monitor, &cfg);
	for (i = 0; i < cfg.philo_count; i++)
		pthread_join(philos[i].thread, NULL);
	pthread_join(monitor_thread, NULL);
	for (i = 0; i < cfg.philo_count; i++)
		pthread_mutex_destroy(&cfg.forks[i]);
	free(cfg.forks);
	free(philos);
	return (0);
}
