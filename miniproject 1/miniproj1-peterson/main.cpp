#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>


int counter = 0;
const int max_access_onbuffer = 20;
int flags[4];
int turns[3];

void* run(void *arg);
int others(int i,int count);

struct arg_struct{
    int num;
};

int main(void)
{
    for (int i = 0; i < 4; i++) {
        flags[i] = -1;
    }

    for (int i = 0; i < 3; i++) {
        turns[i] = 0;
    }

    int err;
    pthread_t thread1;
    pthread_attr_t attr1;
    pthread_attr_init(&attr1);
    struct arg_struct arg1;
    arg1.num = 0;

    pthread_t thread2;
    pthread_attr_t attr2;
    pthread_attr_init(&attr2);
    struct arg_struct arg2;
    arg2.num = 1;

    pthread_t thread3;
    pthread_attr_t attr3;
    pthread_attr_init(&attr3);
    struct arg_struct arg3;
    arg3.num = 2;

    pthread_t thread4;
    pthread_attr_t attr4;
    pthread_attr_init(&attr4);
    struct arg_struct arg4;
    arg4.num = 3;

    err = pthread_create(&thread1, &attr1, &run, (void *)&arg1);
    if (err != 0){
        printf("\n can't create thread1 :[%s]\n", strerror(err));
        exit(1);
    }


    err = pthread_create(&thread2, &attr2, &run, (void *)&arg2);
    if (err != 0){
        printf("\n can't create thread2 :[%s]\n", strerror(err));
        exit(1);
    }


    err = pthread_create(&thread3, &attr3, &run, (void *)&arg3);
    if (err != 0){
        printf("\n can't create thread3 :[%s]\n", strerror(err));
        exit(1);
    }


    err = pthread_create(&thread4, &attr4, &run, (void *)&arg4);
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
    struct arg_struct *args = (arg_struct *) arg;
    int number = args ->num;
    int *times = ((int *)malloc(sizeof(int)));
    *times = 0;
    pthread_t id = pthread_self();
    while (counter < max_access_onbuffer) {
        // entery
        for (int i = 0; i < 3; i++) {
            flags[number] = i;
            turns[i] = number;
            while (others(number,i) == 1 && turns[i] == number){
                if(counter >= max_access_onbuffer)
                    break;
            }
        }


        if(counter < max_access_onbuffer ){
            printf("\n TID: %lld, PID: %d,Buffer: %d \n" ,id,getpid(),counter);
            counter ++;
            (*times)++;
        }
        // exit
        flags[number] = -1;

        for(int i = 0 ; i < 0XFFFFF;i++);
    }
    printf("\n TID: %lld worked on buffer %d times \n",id,*times);
    return times;
}

int others(int i , int count){
    for (int k = 0; k < 4; ++k) {
        if(k != i){
            if(flags[k] >= count){
                return 1;
            }
        }
    }
    return 0;
}