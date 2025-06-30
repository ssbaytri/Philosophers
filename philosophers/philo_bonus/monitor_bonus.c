/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 20:23:21 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/06/30 21:51:28 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	check_death(t_philo *philo)
{
	if ((get_time_ms() - philo->last_meal_time) >= philo->config->time_to_die)
	{
		sem_wait(philo->config->death_sem);
		printf("%ld %d died\n", get_time_ms() - philo->start_time, philo->id);
		exit(1);
	}
	return (0);
}

static int	check_meal_finished(t_philo *philo)
{
	if (philo->config->must_eat_count != -1
		&& philo->times_eaten >= philo->config->must_eat_count)
		exit(0);
	return (0);
}

void	*death_monitor(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		check_death(philo);
		check_meal_finished(philo);
		ft_usleep(100);
	}
	return (NULL);
}
