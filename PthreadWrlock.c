#include<stdio.h>
#include<pthread.h>

#define READER_NUM 3
#define WRITER_NUM 2

//pthread_rwlock_t lock;
pthread_rwlock_t lock = PTHREAD_RWLOCK_INITIALIZER;//对读写锁的静态初始化(方法一)
int buf = 0;

void *read(void *_val)
{
	pthread_detach(pthread_self());
	while(1){
		if(pthread_rwlock_rdlock(&lock) != 0){// try lock by reader
			printf("writer is writing,reader waiting...++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
		}else{
			printf("reader is %u : read val is %d++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n",pthread_self(),buf);
			pthread_rwlock_unlock(&lock);
		}
		sleep(2);
	}
}

void *write(void *_val)
{
	pthread_detach(pthread_self());
	while(1){
		if(pthread_rwlock_wrlock(&lock) != 0){// try lock by writer
			printf("reader is reading,writer waiting...\n");
			sleep(1);
		}else{
			++buf;//write
			printf("writer is %u : write val is %d\n",pthread_self(),buf);
			pthread_rwlock_unlock(&lock);
		}
		sleep(1);
	}
}


int main()
{
//	pthread_rwlock_init(&lock,NULL);//对读写锁的动态初始化(方法二)

	pthread_t tid;
	int i;
	for(i = 0;i < WRITER_NUM;++i)
		pthread_create(&tid,NULL,write,NULL);
	for(i = 0;i < READER_NUM;++i)
		pthread_create(&tid,NULL,read,NULL);

	sleep(100);
	return 0;
}
