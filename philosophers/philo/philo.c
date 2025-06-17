/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 20:42:57 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/06/17 04:13:12 by ssbaytri         ###   ########.fr       */
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
		pthread_mutex_init(&cfg->logs_mutex, NULL) ||
		pthread_mutex_init(&cfg->eat_mutex, NULL))
		return (0);
	cfg->philo_full_count = 0;
	cfg->stop_simulation = 0;
	cfg->start_time = get_time_ms() + (10 * cfg->philo_count);
	cfg->time_to_think = cfg->time_to_die - cfg->time_to_sleep;
	if (cfg->philo_count % 2 != 0)
		cfg->time_to_think += cfg->time_to_eat;
	return (1);
}

int main(int ac, char **av)
{
	t_config	cfg;
	// t_philo		*philos;
	// int i;
	// pthread_t thread;
	
	if (!validate_args(ac, av))
		return (1);
	if (!init_config(&cfg, ac, av))
	{
		printf("Error: Failed to initialize configuration.\n");
		return (1);
	}
	
}
