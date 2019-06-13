#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>

#define SEM_PRO 10
#define SEM_CON 0
sem_t sem_product;
sem_t sem_consumer;
int bank[SEM_PRO];
void init_all_data()
{
	int i = 0;
	for(;i<SEM_PRO;++i){
		bank[i] = 0;
	}
	sem_init(&sem_product,0,SEM_PRO);
	sem_init(&sem_consumer,0,SEM_CON);
}

void *consumer(void *_val)
{
	int c = 0;
	while(1){
		sem_wait(&sem_consumer);
		int _consumer = bank[c];
		printf("[c = %d]consume done...,val is:%d\n",c,_consumer);
		sem_post(&sem_product);
		c = (c + 1) % SEM_PRO;
		usleep(700000);
	}
}

void *product(void *_val)
{
	int p = 0;
	while(1){
		sem_wait(&sem_product);
		int _product = rand() % 100;
		bank[p] = _product;
		printf("[p = %d]product done...,val is:%d++++++++++++++++++++++++++++++++++++++++++++++++++\n",p,_product);
		sem_post(&sem_consumer);
		p = (p + 1) % SEM_PRO;
		usleep(300000);
	}
}

int main()
{
	init_all_data();

	pthread_t con,pro;
	pthread_create(&con, NULL,consumer,NULL);
	pthread_create(&pro, NULL,product,NULL);

	pthread_join(con,NULL);
	pthread_join(pro,NULL);

	printf("因为前面是死循环，所以执行不到这\n");
	sem_destroy(&sem_product);
	sem_destroy(&sem_consumer);
}


