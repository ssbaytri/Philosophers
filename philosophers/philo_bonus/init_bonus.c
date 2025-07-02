/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 19:44:50 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/07/02 16:42:44 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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

static int	init_semaphores(t_config *cfg)
{
	sem_unlink("/forks_sem");
	sem_unlink("/log_sem");
	sem_unlink("/death_sem");
	sem_unlink("/meal_sem");
	cfg->forks = sem_open("/forks_sem", O_CREAT | O_EXCL, 0644,
			cfg->philo_count);
	if (cfg->forks == SEM_FAILED)
		return (0);
	cfg->death_sem = sem_open("/death_sem", O_CREAT | O_EXCL, 0644, 1);
	if (cfg->death_sem == SEM_FAILED)
		return (0);
	cfg->log_sem = sem_open("/log_sem", O_CREAT | O_EXCL, 0644, 1);
	if (cfg->log_sem == SEM_FAILED)
		return (0);
	cfg->meal_sem = sem_open("/meal_sem", O_CREAT | O_EXCL, 0644, 1);
	if (cfg->meal_sem == SEM_FAILED)
		return (0);
	return (1);
}

static int	init_philos(t_config *cfg)
{
	cfg->philos = malloc(sizeof(pid_t) * cfg->philo_count);
	if (!cfg->philos)
		return (0);
	return (1);
}

void	cleanup_semaphores(void)
{
	sem_unlink("/forks_sem");
	sem_unlink("/log_sem");
	sem_unlink("/death_sem");
	sem_unlink("/meal_sem");
}

int	init_all(t_config *cfg, char **argv)
{
	init_args(cfg, argv);
	if (!init_semaphores(cfg))
		return (0);
	if (!init_philos(cfg))
		return (0);
	return (1);
}
