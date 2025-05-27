/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 18:01:56 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/05/27 18:17:25 by ssbaytri         ###   ########.fr       */
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
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	if (str[i] == '\0')
		return (0);
	if (!validate_digit(str, &i, &result, &sign))
		return (0);
	return (1);
}

static int	count_args(char **splitted_nums)
{
	int	count;

	count = 0;
	while (splitted_nums[count])
		count++;
	return (count);
}

static char	*join_nums(int ac, char **av)
{
	char	*res;
	char	*tmp;
	char	*tmp2;
	int		i;

	i = 1;
	res = ft_strdup("");
	while (i < ac)
	{
		tmp2 = ft_strtrim(av[i], " ");
		if (!av[i][0] || tmp2[0] == '\0')
			return (free(res), free(tmp2), NULL);
		tmp = ft_strjoin(res, av[i]);
		free(res);
		res = tmp;
		tmp = ft_strjoin(res, " ");
		free(res);
		res = tmp;
		free(tmp2);
		i++;
	}
	return (res);
}

int	*parce_nums(int ac, char **av, int *size)
{
	char	*joined_nums;
	char	**splitted_nums;
	int		*nums;
	int		count;
	int		i;

	i = 0;
	joined_nums = join_nums(ac, av);
	if (!joined_nums)
		return (NULL);
	splitted_nums = ft_split(joined_nums, ' ');
	count = count_args(splitted_nums);
	nums = (int *)malloc(sizeof(int) * count);
	if (!nums)
		return (free2(splitted_nums, joined_nums), NULL);
	while (i < count)
	{
		if (!is_valid_number(splitted_nums[i]))
			return (free(nums), free2(splitted_nums, joined_nums), NULL);
		nums[i] = ft_atoi(splitted_nums[i]);
		i++;
	}
	return (free2(splitted_nums, joined_nums), *size = count, nums);
}
