#include<stdio.h>
#include<pthread.h>

static int g_count = 0;

void *read_write_mem(void *_val)
{
	int i = 0;
	int val = 0;
	while(i < 5000){
		val = g_count;
		++i;
		printf("pthread id is:%d,g_count is:%d\n",(unsigned long)pthread_self(),g_count);
		g_count = val + 1;
	}
}

int main()
{
	pthread_t tid1;
	pthread_t tid2;
	pthread_create(&tid1, NULL,read_write_mem,NULL);
	pthread_create(&tid2, NULL,read_write_mem,NULL);
	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);
}
