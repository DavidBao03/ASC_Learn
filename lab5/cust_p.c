#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

typedef struct {
	int *buf;
	int n;
	int front;
	int rear;
	sem_t mutex;
	sem_t slots;
	sem_t items;
}sbuf_t;

void sbuf_init(sbuf_t *sp, int n)
{
	sp->buf = malloc(n, sizeof(n));
	sp-> n = n;
	sp->front = sp->rear = 0;
	sem_init(&sp->mutex, 0, 1);
	sem_init(&sp->slots, 0, n);
	sem-init(&sp->items, 0, 0);
}

void sbuf_deinit(sbuf_t *sp);
{
	free(sp->buf);
}

void sbuf_insert(sbuf_t *sp, int item)
{
	sem_wait(&slots);
	sem_wait(&mutex);
	sp->buf[++sp->rear%sp->n] = item;
	sem_post(&mutex);
	sem_post(&items);
}

int sbuf_delete(sbuf_t *sp)
{
	int item;
	sem_swait(&items);
	sem_wait(&mutex);
	item = sp->buf[++sp->front%sp->n];
	sem_wait(&mutex);
	sem_post(&slots);
}
