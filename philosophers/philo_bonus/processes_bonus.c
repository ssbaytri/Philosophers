/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 20:40:51 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/07/01 22:03:21 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void kill_processes(t_config *cfg)
{
	int i;

	i = 0;
	while (i < cfg->philo_count)
	{
		kill(cfg->philos[i], SIGTERM);
		i++;
	}
}

static void wait_processes(t_config *cfg)
{
	int i;
	int status;

	i = 0;
	status = 0;
	while (i < cfg->philo_count)
	{
		waitpid(-1, &status, 0);
		if (status != 0)
		{
			kill_processes(cfg);
			break ;
		}
		i++;
	}
}

static void process_philo(t_config  *cfg, int id)
{
	t_philo *philo;
	
	philo->id = id;
	philo->times_eaten = 0;
	philo->last_meal_time = get_time_ms();
	philo->config = cfg;
	philo_routine(philo);
}

int simulation(t_config *cfg)
{
	int i;

	i = 0;
	cfg->start_time = get_time_ms();
	while (i < cfg->philo_count)
	{
		cfg->philos[i] = fork();
		if (cfg->philos[i] == 0)
			process_philo(cfg, i + 1);
		i++;
	}
}