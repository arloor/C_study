//
// Created by arloor on 17-7-13.
//

#include "header/thread_prac2_rwlock.h"
#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <zconf.h>

struct item {
    char *name;
    int count;
};

int count;

pthread_rwlock_t rwlock;
pthread_t xie;
pthread_t du[10];

static void *thr_xie(void *arg);

static void *thr_du(void *arg);

void thread_prac2_rwlock() {
    count = 0;
    setbuf(stdout, NULL);
    //初始化
    pthread_rwlock_init(&rwlock, NULL);

    struct item item1;
    item1.count = 1;
    item1.name = "item";

    //创建读线程和写线程。

    for (int i = 0; i < sizeof(du) / sizeof(pthread_t); i++) {
        pthread_create(&du[i], NULL, thr_du, NULL);
    }
    pthread_create(&xie, NULL, thr_xie, NULL);
    sleep(5);

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