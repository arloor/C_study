//
// Created by arloor on 17-7-12.
//

#include "header/thread1_prac1.h"
#include<stdio.h>
#include <pthread.h>
#include <unistd.h>

//多线程，apue第11章
//编译时需要加上 –lpthread;或者修改CMakeLists.txt
/**
 * 线程相关函数
 * pthread_t 这是标示线程的id
 * 判断两个线程是否是同一个线程——int pthread_equal(pthread_t tid1,pthread_t tid2);相等返回非0。
 * 得到线程的ID——pthread_t pthread_self(void);
 * 创建线程——int pthread_create(pthread_t *tidp,const pthread_attr_t *attr),
 *                              void *(*start_rtn)(void *),void *arg)。成功返回0
 *                              tidp：新建线程的ID会被设置成tidp指向的内存单元。
 *                              attr：用于定制线程的属性，可以设置为NULL，默认线程属性。
 *                              start_rtn：新创建的线程将会从start_rtn函数的地址开始运行。
 *                              arg： 上面的start_rtn的参数（只有一个）。
 *                              新创建的线程可以访问进程的地址空间，并且继承调用线程（主线程）的浮点环境和先好屏蔽字（第10章），但是挂起信号集会被屏蔽
 *
 * 线程退出——void ptheard_exit(void *rval_ptr); rval_ptr保存返回码（如果被其他线程取消，rval_ptr指向PTHREAD_CANCELED）
 * 线程join——int pthread_join(pthread_t thread,void **rval_ptr); 与其他线程绑定，必须等待被帮顶线程结束、取消才，调用线程才能结束。
 *                                                              ravel_ptr返回所绑定的线程的退出码。
 *                                                              如果对返回状态不感兴趣可以设为NULL
 * 取消另一线程——int pthread_cnacel(pthread_t tid);成功返回0
 * 增加线程清理成立程序——void pthread_cleanup_push(void (*rtn)(void *),void *arg);
 * 删除线程清理程序——void pthread_cleanup_pop(int execute);如果execute为0,则清理程序弹出时不执行，否则弹出时执行。
 * 上面的两个函数必须·配对使用，push的宏实现中包含一个{，pop包含一个}
 * 线程清理程序的执行是与注册顺序相反的
 * @return
 */
void *thread1(void *arg);

void *thread2(void *arg);

void th2_cleanup(void *arg);

pthread_t id1;
pthread_t id2;//作为全局比较好，因为所有线程都可能需要访问吧

void thread_prac1() {

    void *rval_ptr;//用来保存线程退出状态

    //创建线程——int pthread_create(pthread_t *tidp,const pthread_attr_t *attr);
    //这里的线程属性，而线程的参数都被设为了NULL
    //关于线程属性，请看thread_prac2
    pthread_create(&id1, NULL, thread1, NULL);
    pthread_create(&id2, NULL, thread2, NULL);
    pthread_join(id2, &rval_ptr);//rval_ptr保存线程2的退出码
    printf("\n线程id2的退出码为：%d\n", rval_ptr);

    //sleep(10);//上面使用了join的方式;如果不使用join，为了保证两个子线程能执行完，主线程需要sleep一段时间。
    return;
}


void *thread1(void *arg) {
    //printf("%lu\n",(unsigned long)pthread_self());//打印线程编号
    for (;;) {
        printf("线程1正在运行111111111\n");
        sleep(1);
    }
}

void *thread2(void *arg) {
    //printf("%lu\n",(unsigned long)pthread_self());//打印线程编号
    //增加线程清理成立程序——void pthread_cleanup_push(void (*rtn)(void *),void *arg);
    pthread_cleanup_push(th2_cleanup, NULL) ;//与下面pop的配对
            int i = 0;
            for (;;) {
                printf("线程2正在运行2222222222222222222222222222222\n");
                sleep(1);
                i++;
                if (i == 3) {
                    pthread_cancel(id1);//取消线程1
                    printf("\t线程1被线程2取消\n");
                }
                if (i == 6) {
                    pthread_exit((void *) 2);//线程2退出
                }
            }
            //与上面的push配对,执行线程清理程序
    pthread_cleanup_pop(1);//尽管这条命令在线程退出之后，但是能够被调用到
}

void th2_cleanup(void *arg) {
    printf("\t线程2使用pthread_exit退出\n");
}