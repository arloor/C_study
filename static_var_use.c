//
// Created by arloor on 17-7-5.
//

#include "header/static_var_use.h"
#include <stdio.h>

void test();
/**
 * 静态变量使用static关键字
 * 只会初始化一次
 * 函数结束后不会销毁
 * 只在声明其的函数中可见，但是是全局的，可以使用全局变量的方式来使用（没懂）
 * @return
 */

void use_static_function(){
    for(int i=0;i<25;i++){
        test();
    }
}

void test(){
    // count只会在开始时初始化一次,而且运行结束不销毁，从而实现了内部计数器
    // 当然在外部函数也可以定义i作为计数器
    static int count=0;
    printf("count: %d\n",count);
    count++;
}