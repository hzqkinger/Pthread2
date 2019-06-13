#include<stdio.h>
#include<pthread.h>

static int g_count = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; //mutex变量的初始化方法一
//pthread_mutex_t mutex = 1;注意，这样初始化是无效的

void *read_write_mem(void *_val)
{
	int i = 0;
	int val = 0;
	while(i < 5000){
		pthread_mutex_lock(&mutex);
		val = g_count;
		++i;
		printf("pthread id is:%d,g_count is:%d\n",(unsigned long)pthread_self(),g_count);
		g_count = val + 1;
		pthread_mutex_unlock(&mutex);
	}
}

int main()
{
//	pthread_mutex_init(&mutex,NULL);//mutex变量的初始化方法二

	pthread_t tid1;
	pthread_t tid2;
	pthread_create(&tid1, NULL,read_write_mem,NULL);
	pthread_create(&tid2, NULL,read_write_mem,NULL);
	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);
}

