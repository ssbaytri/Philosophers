/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 20:42:57 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/05/26 20:38:13 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int num = 0;
pthread_mutex_t lock;

void routine()
{
	for (int i = 0; i < 10000000; i++)
	{
		pthread_mutex_lock(&lock);
		num++;
		pthread_mutex_unlock(&lock);
	}
}

int	main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	pthread_t t1, t2;
	pthread_mutex_init(&lock, NULL);
	pthread_create(&t1, NULL, (void *)routine, NULL);
	pthread_create(&t2, NULL, (void *)routine, NULL);
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	printf("number is: %d\n", num);
	pthread_mutex_destroy(&lock);
	return (0);
}