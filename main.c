

#include "header/memory_alloc.h"
#include "header/static_var_use.h"
#include "header/fget_read_line_from_stream.h"
#include <stdio.h>
#include <stdlib.h>

int main() {

    struct func{
        void (*f)();//函数指针
        char name[50];//函数名
        char descip[250];//函数描述
    };

    //todo:每完成一个函数，请在此添加函数的结构体，参见上方定义
    //todo:要求函数必须是无参无返回值的
    /*
     struct func exit_while={NULL,"exit","退出程序的运行"};
     */
    //
    struct func exit_while={NULL,"exit","退出程序的运行"};
    struct func memory_alloc_func={memory_alloc,"memory_alloc","分配内存——calloc和realloc的使用"};
    struct func use_static_func={use_static_function,"use_static_function","使用静态变量的例子"};
    struct func fget_read_line_from_stream_func={fget_read_line_from_stream,"fget_read_line_from_stream","从文件流（标准输入）读取输入"};


    struct func func_table[][20]={
            {exit_while},
            {memory_alloc_func},
            {use_static_func},
            {fget_read_line_from_stream_func}
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
        char ch;
        while ((ch = getchar()) != '\n' && ch != EOF);//清空缓冲区的一般方法（最好方法）

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

