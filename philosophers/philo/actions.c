/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 16:55:48 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/06/28 17:27:46 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	thinking(t_philo *philo)
{
	print_log(philo, "is thinking");
}

void	sleeping(t_philo *philo)
{
	print_log(philo, "is sleeping");
	ft_usleep(philo->config->time_to_sleep);
}

void	eating(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	print_log(philo, "has taken a fork");
	if (philo->config->philo_count == 1)
	{
		ft_usleep(philo->config->time_to_die);
		pthread_mutex_unlock(philo->right_fork);
		return ;
	}
	pthread_mutex_lock(philo->left_fork);
	print_log(philo, "has taken a fork");
	philo->eating = 1;
	print_log(philo, "is eating");
	pthread_mutex_lock(philo->meal_mutex);
	philo->last_meal_time = get_time_ms();
	philo->times_eaten++;
	pthread_mutex_unlock(philo->meal_mutex);
	ft_usleep(philo->config->time_to_eat);
	philo->eating = 0;
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}
