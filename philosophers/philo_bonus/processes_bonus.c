/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 20:40:51 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/06/30 20:47:19 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void philo_process(t_config *cfg, int id)
{
	t_philo philo;

	philo.id = id;
	philo.times_eaten = 0;
	philo.must_eat_count = cfg->must_eat_count;
	philo.start_time = cfg->start_time;
	philo.last_meal_time = get_time_ms();
	philo.config = cfg;
	pthread_create(&philo.monitor_thread, NULL, death_monitor, &philo);
	pthread_detach(philo.monitor_thread);
	if (philo.id % 2 == 0)
		ft_usleep(1);
	while (1)
	{
		eating(&philo);
		sleeping(&philo);
		thinking(&philo);
	}
}

int simulation(t_config *cfg)
{
	int i;

	i = 0;
	while (i < cfg->philo_count)
	{
		cfg->philos[i] = fork();
		if (cfg->philos[i] == 0)
		{
			philo_process(cfg, i + 1);
			exit(0);
		}
		i++;
	}
	return (0);
}