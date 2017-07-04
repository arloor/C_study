

#include "memory_alloc.h"
#include "static_var_use.h"
#include <stdio.h>
#include <stdlib.h>

int main() {

    struct func{
        void (*f)();//函数指针
        char name[20];//函数名
        char descip[150];//函数描述
    };

    //todo:每完成一个函数，请在此添加函数的结构体，参见上方定义
    //todo:要求函数必须是无参无返回值的
    /*
     struct func exit_while={NULL,"exit","退出程序的运行"};
     */

    struct func exit_while={NULL,"exit","退出程序的运行"};
    struct func memory_alloc_func={memory_alloc,"memory_alloc","分配内存——calloc和realloc的使用"};
    struct func use_static_func={use_static_function,"use_static_function","使用静态变量的例子"};


    struct func func_table[][20]={
            {exit_while},
            {memory_alloc_func},
            {use_static_func}
    };


    //以下不用修改
    //--------------------------------------------------------------
    while(1){
        printf("函数列表如下：\n");//取名时函数名限制长度为20
        for(int i=0;i<sizeof(func_table)/sizeof(func_table[0]);i++){
            printf("%d: %s\t\t%s\n",i,func_table[i]->name,func_table[i]->descip);
        }
        printf("请输入要运行的函数编号：\n");

        int i=0;
        scanf("%d",&i);

        printf("\n下面运行\n%s:\n%s\n\n",func_table[i]->name,func_table[i]->descip);
        if(i==0)
            exit(0);
        printf("----------------------运行开始------------------------\n");

        void (*function)();

        function=func_table[i]->f;
        function();
        printf("----------------------运行结束------------------------\n");
        printf("\n继续选择函数\n");
    }
}

