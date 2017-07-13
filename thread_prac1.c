//
// Created by arloor on 17-7-12.
//

#include "header/thread_prac1.h"
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
 *
 *
 * 互斥量相关：
 * 互斥量静态初始化：pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;
 * 互斥量动态初始化：int pthread_mutex_init(pthread_mutext_t *restict mutex,
 *                                          const pthread_mutexattr_t attr);
 *                                          使用默认的互斥量属性时，attr设为NULL
 * 互斥量清除：int pthread_mutex_destroy(pthread_mutex_t *mutex);
 *
 * 对互斥量加锁：int pthread_mutex_lock(pthread_mutex_t *mutex);
 * 对互斥量解锁：int pthread_mutex_unlock(pthread_mutex_t *mutex);
 * 尝试加锁（加锁失败不会被阻塞，但是会返回EBUSY）：int pthread_mutex_trylock(pthread_mutex_t *mutex);
 *
 * @return
 */
void *thread1(void *arg);

void *thread2(void *arg);

void th2_cleanup(void *arg);

pthread_t id1;
pthread_t id2;//作为全局比较好，因为所有线程都可能需要访问吧

static int count = 0;//计数器，两个线程都将使用
//为了保护这个临界区，使用互斥量保护
pthread_mutex_t mutex;//=PTHREAD_MUTEX_INITIALIZER;//静态进行初始化。这里需要进行动态的初始化

void thread_prac1() {
    count = 1;

    pthread_mutex_init(&mutex, NULL);//创建锁

    void *rval_ptr;//用来保存线程退出状态

    //创建线程——int pthread_create(pthread_t *tidp,const pthread_attr_t *attr);
    //这里的线程属性，而线程的参数都被设为了NULL
    //关于线程属性，请看thread_prac2
    printf("开启两个线程，共享计数器（临界区）,使用互斥量来保护计数器\n");
    pthread_create(&id1, NULL, thread1, NULL);
    pthread_create(&id2, NULL, thread2, NULL);
    pthread_join(id2, &rval_ptr);//rval_ptr保存线程2的退出码
    printf("线程id2的退出码为：%d\n", rval_ptr);

    pthread_cancel(id1);//取消线程1
    printf("\t主线程取消线程1\n");
    fflush(stdout);
    //为了互斥量不出错，尽量在主线程取消其他线程，不要子线程取消子线程。

    pthread_mutex_destroy(&mutex);//清除锁
    //sleep(10);//上面使用了join的方式;如果不使用join，为了保证两个子线程能执行完，主线程需要sleep一段时间。
    return;
}


void *thread1(void *arg) {
    //printf("%lu\n",(unsigned long)pthread_self());//打印线程编号
    for (;;) {
        pthread_mutex_lock(&mutex);
        printf("线程1正在运行，当前计数器为：%d\n", count++);
        fflush(stdout);
        pthread_mutex_unlock(&mutex);
        sleep(1);//注意：两个线程的sleep都放在锁外，否则会造成两个线程的执行数量不一致：
        //因为在锁内sleep，sleep的时间还持有锁
    }
}

void *thread2(void *arg) {
    //printf("%lu\n",(unsigned long)pthread_self());//打印线程编号
    //增加线程清理成立程序——void pthread_cleanup_push(void (*rtn)(void *),void *arg);
    pthread_cleanup_push(th2_cleanup, NULL) ;//与下面pop的配对
            int i = 0;
            for (;;) {
                pthread_mutex_lock(&mutex);
                printf("线程2正在运行，当前计数器为：%d\n", count++);
                fflush(stdout);
                //pthread_mutex_unlock(&mutex);//解锁放在这个位置不对，思考如下：
                //下面有取消线程1的操作
                //线程1被取消了，线程1的解锁操作就没有办法进行了，所以存在死锁（线程2一直等待着线程1解锁呢）
                i++;
                pthread_mutex_unlock(&mutex);//解锁放在这才对
                if (i == 6) {
                    pthread_exit((void *) 2);//线程2退出
                }
                sleep(1);//注意：两个线程的sleep都放在锁外，否则会造成两个线程的执行数量不一致：
                //因为在锁内sleep，sleep的时间还持有锁
            }
            //与上面的push配对,执行线程清理程序
    pthread_cleanup_pop(1);//尽管这条命令在线程退出之后，但是能够被调用到
}

void th2_cleanup(void *arg) {
    printf("\t线程2使用pthread_exit退出\n");
    fflush(stdout);
}