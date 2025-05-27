/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 18:01:56 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/05/27 21:46:41 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	validate_digit(char *str, int *i, long *res, int *sign)
{
	while (str[*i] >= '0' && str[*i] <= '9')
	{
		*res = *res * 10 + (str[*i] - '0');
		if ((*res * *sign) > INT_MAX || (*res * *sign) < INT_MIN)
			return (0);
		(*i)++;
	}
	while (str[*i])
	{
		if (str[*i] != ' ')
			return (0);
		(*i)++;
	}
	return (1);
}

static int	is_valid_number(char *str)
{
	int		i;
	long	result;
	int		sign;

	i = 0;
	result = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-')
		return (0);
	if (str[i] == '+')
		i++;
	if (str[i] == '\0')
		return (0);
	if (!validate_digit(str, &i, &result, &sign))
		return (0);
	return (1);
}

int	parse_args(int ac, char **av)
{
	int	i;

	i = 1;
	while (i < ac)
	{
		if (!is_valid_number(av[i]) || ft_atoi(av[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}
