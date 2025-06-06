/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 20:42:57 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/06/05 23:37:34 by ssbaytri         ###   ########.fr       */
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

static int	print_args(char **av)
{
	int	i;

	i = 1;
	while (av[i])
	{
		printf("%d ", ft_atoi(av[i]));
		printf("\n");
		i++;
	}
	return (1);
}

int	main(int argc, char **argv)
{
	if (!validate_args(argc, argv))
		return (1);
	t_philo philo;
	memset(&philo, 0, sizeof(t_philo));
	printf("Philosopher ID: %d\n", philo.id);
	print_args(argv);
	struct timeval tv;
	gettimeofday(&tv, NULL);
	long seconds = tv.tv_sec;
	long microseconds = tv.tv_usec;
	long milisonds = (seconds * 1000) + (microseconds / 1000);
	printf("Current time in milliseconds: %ld\n", milisonds);
	printf("Currect time in seconds: %ld\n", seconds);
	return (0);
}
