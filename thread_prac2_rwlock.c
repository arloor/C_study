//
// Created by arloor on 17-7-13.
//

#include "header/thread_prac2_rwlock.h"
#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <zconf.h>


int count;//被写和读的计数器

pthread_rwlock_t rwlock;//读写锁
pthread_t xie;//少写
pthread_t du[10];//多读

static void *thr_xie(void *arg);

static void *thr_du(void *arg);

void thread_prac2_rwlock() {
    count = 0;
    setbuf(stdout, NULL);//设置缓冲方式
    //初始化锁
    pthread_rwlock_init(&rwlock, NULL);


    //创建读线程和写线程。

    for (int i = 0; i < sizeof(du) / sizeof(pthread_t); i++) {
        pthread_create(&du[i], NULL, thr_du, NULL);
    }
    pthread_create(&xie, NULL, thr_xie, NULL);

    sleep(5);//5秒钟给子线程执行

    //取消线程
    for (int i = 0; i < sizeof(du) / sizeof(pthread_t); i++) {
        pthread_cancel(du[i]);
    }
    pthread_cancel(xie);

    pthread_rwlock_destroy(&rwlock);
}

void *thr_xie(void *arg) {
    while (1) {
        pthread_rwlock_wrlock(&rwlock);
        count++;
        printf("将count写为：%d\n", count);
        pthread_rwlock_unlock(&rwlock);
        sleep(1);
    }
    return (void *) 0;
}

void *thr_du(void *arg) {
    while (1) {
        pthread_rwlock_rdlock(&rwlock);
        printf("线程%lu\t读到%d\n", (unsigned long) pthread_self(), count);
        pthread_rwlock_unlock(&rwlock);
        sleep(1);

    }
    return (void *) 0;
}