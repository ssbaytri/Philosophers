/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 20:42:57 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/05/27 22:03:12 by ssbaytri         ###   ########.fr       */
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
	print_args(argv);
	return (0);
}
