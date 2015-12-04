#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>


pthread_mutex_t mutex;
int counter = 0;
const int max_access_onbuffer = 20;

void* run(void *arg);

int main(void)
{
    pthread_mutex_init(&mutex,NULL);

    int err;
    pthread_t thread1;
    pthread_attr_t attr1;
    pthread_attr_init(&attr1);

    pthread_t thread2;
    pthread_attr_t attr2;
    pthread_attr_init(&attr2);

    pthread_t thread3;
    pthread_attr_t attr3;
    pthread_attr_init(&attr3);

    pthread_t thread4;
    pthread_attr_t attr4;
    pthread_attr_init(&attr4);

    err = pthread_create(&thread1, &attr1, &run, NULL);
    if (err != 0){
        printf("\n can't create thread1 :[%s]\n", strerror(err));
        exit(1);
    }


    err = pthread_create(&thread2, &attr2, &run, NULL);
    if (err != 0){
        printf("\n can't create thread2 :[%s]\n", strerror(err));
        exit(1);
    }


    err = pthread_create(&thread3, &attr3, &run, NULL);
    if (err != 0){
        printf("\n can't create thread3 :[%s]\n", strerror(err));
        exit(1);
    }


    err = pthread_create(&thread4, &attr4, &run, NULL);
    if (err != 0){
        printf("\n can't create thread4 :[%s]\n", strerror(err));
        exit(1);
    }


    int sum = 0;
    void *access_time;

    pthread_join(thread1,&access_time);
    sum += *((int *)access_time);

    pthread_join(thread2,&access_time);
    sum += *((int *)access_time);

    pthread_join(thread3,&access_time);
    sum += *((int *)access_time);

    pthread_join(thread4,&access_time);
    sum += *((int *)access_time);


    printf("\n Total buffer access: %d \n",sum);
    return 0;
}

void* run(void *arg)
{
    int *times = ((int *)malloc(sizeof(int)));
    *times = 0;
    pthread_t id = pthread_self();
    while (counter < max_access_onbuffer) {
        pthread_mutex_lock(&mutex);
        if(counter < max_access_onbuffer ){
            printf("\n TID: %lld, PID: %d,Buffer: %d \n" ,id,getpid(),counter);
            counter ++;
            (*times)++;
        }
        pthread_mutex_unlock(&mutex);

        for(int i = 0 ; i < 0XFFFFF;i++);
    }
    printf("\n TID: %lld worked on buffer %d times \n",id,*times);
    return times;
}