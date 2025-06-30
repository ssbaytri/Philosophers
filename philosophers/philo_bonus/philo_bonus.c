/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 20:51:25 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/06/30 21:01:10 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	validate_args(int ac, char **av)
{
	if (ac < 5 || ac > 6 || !parse_args(ac, av))
	{
		printf("Error: Invalid arguments.\n");
		return (0);
	}
	return (1);
}

static void cleanup(t_config *cfg)
{
	if (cfg->philos)
		free(cfg->philos);
	cleanup_semaphores();
}

static void kill_processes(t_config *cfg)
{
	int i;

	i = 0;
	while (i < cfg->philo_count)
	{
		kill(cfg->philos[i], SIGKILL);
		i++;
	}
}

static void wait_for_processes(t_config *cfg)
{
	int i;
	int status;

	i = 0;
	while (i < cfg->philo_count)
	{
		waitpid(cfg->philos[i], &status, 0);
		if (WEXITSTATUS(status) == 1)
		{
			kill_processes(cfg);
			break ;
		}
		i++;
	}
}

int	main(int ac, char **av)
{
	t_config cfg;
	if (!validate_args(ac, av))
		return (1);
	memset(&cfg, 0, sizeof(t_config));
	if (!init_all(&cfg, av))
	{
		printf("Error: Initialization failed.\n");
		return (cleanup(&cfg), 1);
	}
	
	wait_for_processes(&cfg);
	cleanup(&cfg);
	return (0);
}
