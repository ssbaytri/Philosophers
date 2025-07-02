/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 20:09:51 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/07/02 16:42:29 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
	sem_wait(philo->config->forks);
	print_log(philo, "has taken a fork");
	sem_wait(philo->config->forks);
	print_log(philo, "has taken a fork");
	print_log(philo, "is eating");
	sem_wait(philo->config->meal_sem);
	philo->last_meal_time = get_time_ms();
	philo->times_eaten++;
	sem_post(philo->config->meal_sem);
	ft_usleep(philo->config->time_to_eat);
	sem_post(philo->config->forks);
	sem_post(philo->config->forks);
}
