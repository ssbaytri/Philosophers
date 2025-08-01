/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 22:04:18 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/06/28 17:28:22 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int				i;
	unsigned long	result;
	int				sign;

	i = 0;
	result = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		if (result > LONG_MAX && sign == 1)
			return (-1);
		if (result > (unsigned long)LONG_MAX + 1 && sign == -1)
			return (0);
		i++;
	}
	return ((int)(result * sign));
}

long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	ft_usleep(long ms)
{
	long	start;

	start = get_time_ms();
	while ((get_time_ms() - start) < ms)
		usleep(500);
	return (0);
}

void	print_log(t_philo *philo, const char *message)
{
	long	time;

	pthread_mutex_lock(philo->log_mutex);
	time = get_time_ms() - philo->start_time;
	if (!already_dead(philo))
		printf("%ld %d %s\n", time, philo->id, message);
	pthread_mutex_unlock(philo->log_mutex);
}

int	already_dead(t_philo *philo)
{
	pthread_mutex_lock(philo->death_mutex);
	if (*philo->dead)
		return (pthread_mutex_unlock(philo->death_mutex), 1);
	pthread_mutex_unlock(philo->death_mutex);
	return (0);
}
