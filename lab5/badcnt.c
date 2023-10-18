#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

void *thread(void* vargp);

volatile long cnt = 0;

int main(int argc, char **argv)
{
	long niters;
	pthread_t tid1, tid2;

	if(argc != 2) {
		printf("usage: %s <niters>\n", argv[0]);
		exit(0);
	}
	
	niters = atoi(argv[1]);

	pthread_create(&tid1, NULL, thread, (void*)&niters);
	pthread_create(&tid2, NULL, thread, (void*)&niters);

	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);

	if(cnt != (2 * niters))
		printf("BOOM! cnt = %ld\n", cnt);
	else
		printf("OK cnt = %ld\n", cnt);

	exit(0);
}

void *thread(void *vargp)
{

	long niters = *((long*)vargp);
	long i = 0;
	
	for(i = 0; i < niters; i++)
		cnt++;
	
	
	return NULL;
}
