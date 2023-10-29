#include <pthread.h>
#include <stdio.h>

char buffer[1024];

int write_idx = 0;
int read_idx = 0;

FILE* fp;

void producer(){
	for(int i = 0; i < 2048; i++){
		buffer[(write_idx++) % 1024] = i % 26 + 'a';
	}
}

void consumer(){
	for(int i = 0; i < 2048; i++){
		putc(buffer[(read_idx++) % 1024], fp);
	}
}

void check(FILE* fp){
	for(int i = 0; i < 2048; i++){
		char c = fgetc(fp);
		char another = i % 26 + 'a';
		if(c != another){
			printf("at line %d, except %c, get %c\n", i, another, c);
		}
	}
	printf("Finish, no Error\n");
}

int main()
{
	fp = fopen("tmp.txt", "w+");

	pthread_t producer_thread;
	pthread_t consumer_thread;

	pthread_create(&producer_thread, NULL, (void* (*)(void*))producer, NULL);
	pthread_create(&consumer_thread, NULL, (void* (*)(void*))consumer, NULL);

	pthread_join(producer_thread, NULL);
	pthread_join(consumer_thread, NULL);

	fclose(fp);
	fp = fopen("tmp.txt", "r");

	check(fp);

	return 0;
}
