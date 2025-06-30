/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 20:51:25 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/06/30 20:02:03 by ssbaytri         ###   ########.fr       */
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
	return (0);
}
