//
// Created by arloor on 17-7-6.
//

#include "header/pointer.h"
#include<stdio.h>

/**
 * 通过指针打印字符和字符串
 * @return
 */
void pointer() {
    //通过指针输出一个字符
    char ch = 'a';
    char *p = &ch;
    printf("通过指针打印一个char： %c\n", *p);//%c需要char类型，所以指针需要解引用。

    //通过指针输出一个字符串
    char str[] = "this is a string";
    char *str_p = str;//&str[0];//&str[0]=str,都是起始位置
    printf("通过指针打印一个字符串：%s\n", str_p);//%s实际上需要char*类型，所以这里的str_p不需要解引用。

    return;
}