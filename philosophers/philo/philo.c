/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 20:42:57 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/06/27 17:03:24 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static void	cleanup(t_config *cfg)
{
	int	i;

	if (cfg->forks)
	{
		i = 0;
		while (i < cfg->philo_count)
		{
			pthread_mutex_destroy(&cfg->forks[i]);
			i++;
		}
		free(cfg->forks);
	}
	pthread_mutex_destroy(&cfg->meal_mutex);
	pthread_mutex_destroy(&cfg->log_mutex);
	pthread_mutex_destroy(&cfg->death_mutex);
	if (cfg->philos)
		free(cfg->philos);
}



int	main(int ac, char **av)
{
	t_config	cfg;

	if (!validate_args(ac, av))
		return (1);
	memset(&cfg, 0, sizeof(t_config));
	if (!init_all(&cfg, av))
	{
		printf("Error: Initialization failed.\n");
		return (cleanup(&cfg), 1);
	}
	cleanup(&cfg);
	return (0);
}
