/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 17:05:10 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/06/27 19:07:25 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int already_dead(t_philo *philo)
{
	pthread_mutex_lock(philo->death_mutex);
	if (*philo->dead)
		return (pthread_mutex_unlock(philo->death_mutex), 1);
	pthread_mutex_unlock(philo->death_mutex);
	return (0);
}

int check_philo_death(t_philo *philo)
{
	pthread_mutex_lock(philo->meal_mutex);
	if ((get_time_ms() - philo->last_meal_time) >= philo->config->time_to_die)
		return (pthread_mutex_unlock(philo->meal_mutex), 1);
	pthread_mutex_unlock(philo->meal_mutex);
	return (0);
}

int check_death(t_philo *philos)
{
	int i;

	i = 0;
	while (i < philos->config->philo_count)
	{
		if (check_philo_death(&philos[i]))
		{
			print_log(&philos[i], "died");
			pthread_mutex_lock(philos[i].death_mutex);
			*philos[i].dead = 1;
			pthread_mutex_unlock(philos[i].death_mutex);
			return (1);
		}
		i++;
	}
	return (0);
}

int check_all_ate(t_philo *philos)
{
	int i;
	int finished_philos;

	i = 0;
	finished_philos = 0;
	if (philos->config->must_eat_count == -1)
		return (0);
	while (i < philos->config->philo_count)
	{
		pthread_mutex_lock(philos[i].meal_mutex);
		if (philos[i].times_eaten >= philos->config->must_eat_count)
			finished_philos++;
		pthread_mutex_unlock(philos[i].meal_mutex);
		i++;
	}
	if (finished_philos == philos->config->philo_count)
	{
		pthread_mutex_lock(philos[0].death_mutex);
		*philos[0].dead = 1;
		pthread_mutex_unlock(philos[0].death_mutex);
		return (1);
	}
	return (0);
}

void *monitor(void *arg)
{
	t_philo *philos;

	philos = (t_philo *)arg;
	while(1)
	{
		if (check_death(philos) || check_all_ate(philos))
			break ;
	}
	return (arg);
}