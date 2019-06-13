#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

typedef struct _list{
	int val;
	struct _list *next;
}List;
static List *head = NULL;

static pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t need_product = PTHREAD_COND_INITIALIZER;

void *consumer(void *_val)
{
	List *p = NULL;
	int i = 0;
	for(;i < 5;++i){
		usleep(1);//------------------------与上张截图比，多加的一句
		pthread_mutex_lock(&lock);//-----------------------------------上锁
		while(NULL == head)
			pthread_cond_wait(&need_product,&lock);//等待在条件变量上
		p = head;
		head = head->next;
		pthread_mutex_unlock(&lock);//--------------------------------解锁
		printf("consumer data:%d\n",p->val);
		free(p);p = NULL;
	}
}

void *product(void *_val)
{
	int i = 0;
	for(;i < 5;++i){
		usleep(1);//----------------------------与上张截图比，多加的一句话
		List *p = (List*)malloc(sizeof(List));
		pthread_mutex_lock(&lock);//-----------------------------------上锁
		sleep(1);p->val = i + 1000;p->next = head;       //注意，在锁里面睡除了给自己看效果，对程序并发运行毫无意义
		head = p;
		pthread_mutex_unlock(&lock);//------------------------------------解锁
		printf("product data:%d\n",p->val);
		pthread_cond_signal(&need_product);//通知等待在条件变量上的事件
	}
}

int main()
{
	pthread_t con,pro;
	pthread_create(&con, NULL,consumer,NULL);
	pthread_create(&pro, NULL,product,NULL);

	pthread_join(con,NULL);
	pthread_join(pro,NULL);
}

