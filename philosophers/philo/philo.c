/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 20:42:57 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/05/27 18:30:06 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free2(char **split, char *joined)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(joined);
	free(split);
}

static int has_nega(int *nums)
{
	int i;

	i = 0;
	while (nums[i])
	{
		if (nums[i] < 0)
			return (1);
		i++;
	}
	return (0);
}

static int validate_args(int *args, int size)
{
	if (size < 4 || size > 5 || has_nega(args))
	{
		printf("Error: Invalid Args.\n");
		free(args);
		return (0);
	}
	return (1);
}

static int print_args(int *args, int size)
{
	int i;

	i = 0;
	while (i < size)
	{
		printf("%d ", args[i]);
		printf("\n");
		i++;
	}
	return (1);
}

int	main(int argc, char **argv)
{
	int *args;
	int size;

	size = 0;
	args = parce_nums(argc, argv, &size);
	if (!validate_args(args, size))
		return (1);
	print_args(args, size);
	free(args);
	return (0);
}