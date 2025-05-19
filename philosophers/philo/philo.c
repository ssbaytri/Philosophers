/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 20:42:57 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/05/20 00:55:05 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int num = 0;

void routine()
{
	for (int i = 0; i < 10000000; i++)
		num++;
}

int	main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	pthread_t t1, t2;;
	pthread_create(&t1, NULL, (void *)routine, NULL);
	pthread_create(&t2, NULL, (void *)routine, NULL);
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	printf("number is: %d\n", num);
	return (0);
}