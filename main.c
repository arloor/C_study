#include "header/memory_alloc.h"
#include "header/static_var_use.h"
#include "header/fget_read_line_from_stream.h"
#include "header/pointer.h"
#include "header/non_buffer_io.h"
#include "header/std_io.h"
#include "header/thread_prac1.h"
#include "header/thread_prac2_rwlock.h"
#include "header/thread_prac3_cond.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_FUNC_NUM 100//定义最多有100个函数
#define MAX_FUNC_NAME_LENGTH 28//定义函数名最长

int main() {

    struct func{
        void (*f)();//函数指针
        char name[MAX_FUNC_NAME_LENGTH];//函数名
        char descip[250];//函数描述
    };

    //todo:每完成一个函数，请在此添加函数的结构体，参见上方定义
    //todo:要求函数必须是无参无返回值的
    /*
     struct func new={NULL,"exit","退出程序的运行"};
        thread_prac3_cond
     */

    struct func exit_while={NULL,"exit","退出程序的运行"};
    struct func memory_alloc_func={memory_alloc,"memory_alloc","分配内存——calloc和realloc的使用"};
    struct func use_static_func={use_static_function,"use_static_function","使用静态变量的例子"};
    struct func fget_read_line_from_stream_func = {fget_read_line_from_stream, "fget_read_line_from_stream",
                                                   "从标准输入读取输入"};
    struct func pointer_func = {pointer, "pointer", "指针的实例：引用字符和字符串并打印"};
    struct func non_buff_io_func = {non_buff_io, "non_buff_io", "不带缓冲的IO：open read close......"};
    struct func std_io_func = {std_io, "std_io", "标准IO的实例"};
    struct func thread_prac1_func = {thread_prac1, "thread_prac1", "线程的创建 退出 连接 线程清理程序（清除锁） 使用互斥量"};
    struct func thread_prac2_rwlock_func = {thread_prac2_rwlock, "thread_prac2_rwlock", "线程：读写锁的实践"};
    struct func thread_prac3_cond_func = {thread_prac3_cond, "thread_prac3_cond", "条件变量——线程同步"};


    struct func func_table[][MAX_FUNC_NUM] = {
            {exit_while},
            {memory_alloc_func},
            {use_static_func},
            {fget_read_line_from_stream_func},
            {pointer_func},
            {non_buff_io_func},
            {std_io_func},
            {thread_prac1_func},
            {thread_prac2_rwlock_func},
            {thread_prac3_cond_func}
    };


    printf("这里展示了apue学习的代码\n数据结构学习的代码没有可运行的函数\n复用时请找到前缀为ds_的.h .c文件\n\n");
    //以下不用修改
    //--------------------------------------------------------------
    while(1){
        select_func:
        printf("函数列表如下：\n");//取名时函数名限制长度为20

        for(int i=0;i<sizeof(func_table)/sizeof(func_table[0]);i++){
            printf("%d: %-25s\t\t%s\n", i, func_table[i]->name, func_table[i]->descip);
        }
        printf("请输入要运行的函数编号：\n");

        int i=0;
        scanf("%d",&i);


        if (i < (unsigned) sizeof(func_table) / sizeof(struct func) / MAX_FUNC_NUM) {//
            printf("\n下面运行\n%s:\n%s", func_table[i]->name, func_table[i]->descip);
            if (i == 0) {
                exit(0);
            }
            printf("\n\n");

            printf("----------------------运行开始------------------------\n");

            void (*function)();


            function = func_table[i]->f;
            function();
            printf("----------------------运行结束------------------------\n");
            printf("\n继续选择函数\n");
        } else printf("\n请输入正确的函数编号\n");
        int ch;//一定要是int 因为EOF是-1
        while ((ch = getchar()) != '\n' && ch != EOF);//清空缓冲区的一般方法（最好方法）,以免影响等会的scanf
    }
}




