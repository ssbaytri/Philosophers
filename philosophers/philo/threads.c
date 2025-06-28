/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 14:46:24 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/06/28 17:29:35 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		ft_usleep(1);
	while (!already_dead(philo))
	{
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}

int	simulation(t_config *cfg)
{
	pthread_t	monitor_thread;
	int			i;

	pthread_create(&monitor_thread, NULL, monitor, cfg->philos);
	i = 0;
	while (i < cfg->philo_count)
	{
		pthread_create(&cfg->philos[i].thread, NULL, philo_routine,
			&cfg->philos[i]);
		i++;
	}
	i = 0;
	pthread_join(monitor_thread, NULL);
	while (i < cfg->philo_count)
	{
		pthread_join(cfg->philos[i].thread, NULL);
		i++;
	}
	return (0);
}
