/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 20:42:57 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/06/11 22:58:47 by ssbaytri         ###   ########.fr       */
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

long get_time_ms(void)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int init_forks(t_config *cfg)
{
	int i;

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

int init_config(t_config *cfg, int argc, char **argv)
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

int	main(int argc, char **argv)
{
	t_config cfg;
	
	if (!validate_args(argc, argv))
		return (1);
	if (!init_config(&cfg, argc, argv))
	{
		printf("Error: Failed to initialize config.\n");
		return (1);
	}
	return (0);
}
