//
// Created by arloor on 17-7-13.
//

#include "header/thread_prac3_cond.h"
#include<stdio.h>
#include <pthread.h>
#include <unistd.h>

//多线程，apue第11章
//编译时需要加上 –lpthread;或者修改CMakeLists.txt

void *thr_signal(void *arg);

void *thr_wait(void *arg);

pthread_t signal_t[10];
pthread_t wait_t[5];//两组线程 分别为等待线程和通知线程。等待线程消耗资源，通知线程增加资源。
static int count = 0;//这就是上面说的资源，也就是条件变量中的“条件”

pthread_cond_t qready;
pthread_mutex_t mutex;

static void mutex_clean(void *mutex);

void thread_prac3_cond() {
    count = 1;

    //条件和互斥量初始化
    pthread_cond_init(&qready, NULL);
    pthread_mutex_init(&mutex, NULL);

    //创建两组线程——int pthread_create(pthread_t *tidp,const pthread_attr_t *attr);
    //这里的线程属性，而线程的参数都被设为了NULL
    for (int i = 0; i < sizeof(signal_t) / sizeof(pthread_t); i++) {
        pthread_create(&signal_t[i], NULL, thr_signal, NULL);
    }
    for (int i = 0; i < sizeof(wait_t) / sizeof(pthread_t); i++) {
        pthread_create(&wait_t[i], NULL, thr_wait, NULL);
    }

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&qready);
    sleep(5);

    for (int i = 0; i < sizeof(signal_t) / sizeof(pthread_t); i++) {
        pthread_cancel(signal_t[i]);
    }
    for (int i = 0; i < sizeof(wait_t) / sizeof(pthread_t); i++) {
        pthread_cancel(wait_t[i]);
    }

    sleep(1);//5秒钟给子线程执行
    return;
}


void *thr_signal(void *arg) {
    pthread_cleanup_push(mutex_clean, &mutex) ;
            while (1) {
                pthread_mutex_lock(&mutex);
                if (count <= 5) {
                    count++;
                    printf("线程%lu: count++,变为：%d\n", pthread_self(), count);
                }

                if (count > 0) {
                    pthread_cond_signal(&qready);
                }
                pthread_mutex_unlock(&mutex);
                sleep(1);
            }
    pthread_cleanup_pop(1);
}


void *thr_wait(void *arg) {
    pthread_cleanup_push(mutex_clean, &mutex) ;
            while (1) {
                pthread_mutex_lock(&mutex);
                while (count <= 0) {
                    pthread_cond_wait(&qready, &mutex);
                }
                count--;
                printf("线程%lu: count--,变为：%d\n", pthread_self(), count);
                pthread_mutex_unlock(&mutex);
                sleep(1);
            }
    pthread_cleanup_pop(1);
    return (void *) 0;
}

static void mutex_clean(void *mutex) {
    printf("\t清除未被取消的锁(重要)\n");
    pthread_mutex_unlock(&mutex);
}
