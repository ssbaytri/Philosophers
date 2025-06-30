#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>

int main()
{
	sem_t *sem;

	sem = sem_open("/sem_test", O_CREAT | O_EXCL, 0644, 4);
	if (sem == SEM_FAILED)
	{
		perror("sem_open");
		return 1;
	}

	for (int i = 0; i < 4; i++)
	{
		pid_t pid = fork();
		if (pid == -1)
		{
			perror("fork");
			sem_close(sem);
			sem_unlink("/sem_test");
			return 1;
		}
		if (pid == 0)
		{
			sem_wait(sem);
			printf("Child %d: acquired semaphore\n", i);
			sleep(1);
			sem_post(sem);
			sem_close(sem);
			exit(0);
		}
	}
	for (int i = 0; i < 4; i++)
	{
		wait(NULL);
	}
	sem_close(sem);
	sem_unlink("/sem_test");
	return (0);
}