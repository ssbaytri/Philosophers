/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 20:09:51 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/06/30 20:22:14 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void thinking(t_philo *philo)
{
	print_log(philo, "is thinking");
}

void sleeping(t_philo *philo)
{
	print_log(philo, "is sleeping");
	ft_usleep(philo->config->time_to_sleep);
}

void eating(t_philo *philo)
{
	sem_wait(philo->config->forks);
	print_log(philo, "has taken a fork");
	if (philo->config->philo_count == 1)
	{
		ft_usleep(philo->config->time_to_die);
		sem_post(philo->config->forks);
		return ;
	}
	sem_wait(philo->config->forks);
	print_log(philo, "has taken a fork");
	print_log(philo, "is eating");
	philo->last_meal_time = get_time_ms();
	philo->times_eaten++;
	ft_usleep(philo->config->time_to_eat);
	sem_post(philo->config->forks);
	sem_post(philo->config->forks);
}
