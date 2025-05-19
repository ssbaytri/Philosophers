/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 20:42:57 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/05/19 21:46:43 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *routine()
{
	printf("hello from thread\n");
	sleep(3);
	printf("ending thread\n");
	return (NULL);
}

int	main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	pthread_t t1, t2;;
	pthread_create(&t1, NULL, routine, NULL);
	pthread_create(&t2, NULL, routine, NULL);
	pthread_join(t1, NULL);
	return (0);
}