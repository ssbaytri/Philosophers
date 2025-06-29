#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <fcntl.h>

#define THREAD_NUM 4

sem_t *semaphore;

void *routine(void *arg)
{
	sem_wait(semaphore);
	sleep(1);
	printf("Hello from theead %d\n", *(int *)arg);
	sem_post(semaphore);
	free(arg);
	return NULL;
}

int main()
{
	pthread_t threads[THREAD_NUM];
	int i;
	semaphore = sem_open("/my_sem", O_CREAT, 0644, 1);
	if (semaphore == SEM_FAILED)
	{
		perror("Failed to open semaphore");
		return 1;
	}
	for (i = 0; i < THREAD_NUM; i++)
	{
		int *a = malloc(sizeof(int));
		*a = i;
		if (pthread_create(&threads[i], NULL, &routine, a) != 0)
		{
			perror("Failed to create thread");
			return 1;
		}
	}
	for (i = 0; i < THREAD_NUM; i++)
	{
		if (pthread_join(threads[i], NULL) != 0)
		{
			perror("Failed to join thread");
			return 1;
		}
	}
	sem_close(semaphore);
	sem_unlink("/my_sem");
	return 0;
}