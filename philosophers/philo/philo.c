/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 20:42:57 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/06/27 13:27:20 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// | Argument Index | Description                                 | Required? |
// | -------------- | ------------------------------------------- | --------- |
// | `argv[1]`      | `number_of_philosophers`                    | Yes       |
// | `argv[2]`      | `time_to_die` (in ms)                       | Yes       |
// | `argv[3]`      | `time_to_eat` (in ms)                       | Yes       |
// | `argv[4]`      | `time_to_sleep` (in ms)                     | Yes       |
// | `argv[5]`      | `number_of_times_each_philosopher_must_eat` | Optional  |

#include "philo.h"

static int	validate_args(int ac, char **av)
{
	if (ac < 5 || ac > 6 || !parse_args(ac, av))
	{
		printf("Error: Invalid arguments.\n");
		return (0);
	}
	return (1);
}

long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}



int main(int ac, char **av)
{	
	if (!validate_args(ac, av))
		return (1);
	
}
