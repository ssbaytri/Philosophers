/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 20:23:21 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/07/01 21:52:21 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void *check_philo_death(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	while (1)
	{
		long curr_time;

		curr_time = get_time_ms();
		sem_wait(philo->config->death_sem);
		if ((curr_time - philo->last_meal_time) > philo->config->time_to_die)
		{
			sem_wait(philo->config->log_sem);
			printf("%ld %d died\n", curr_time - philo->config->start_time, philo->id);
			exit(1);
		}
		sem_post(philo->config->death_sem);
		usleep(100);
	}
	return (NULL);
}

void philo_routine(t_philo *philo)
{
	pthread_t monitor_thread;
	
	philo->last_meal_time = get_time_ms();
	pthread_create(&monitor_thread, NULL, check_philo_death, philo);
	pthread_detach(monitor_thread);
	if (philo->id % 2 == 0)
		ft_usleep(1);
	while (1)
	{
		eating(philo);
		if (philo->config->must_eat_count != -1 && philo->times_eaten >= philo->config->must_eat_count)
			exit(0);
		sleeping(philo);
		thinking(philo);
	}
}
