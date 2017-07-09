//
// Created by arloor on 17-7-5.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "header/fget_read_line_from_stream.h"

/**
 * 主要使用
 * char *fgets(char *s, int size, FILE*stream);
 * fgets从stream中读取最多size-1大小的内容到s指定的buffer中，当遇到换行符或EOF时读取结束。
 * 读取成功时，返回s地址；失败时返回null。需要注意的是，fgets会在所读取的内容后面添加'\0'，这样，fgets读取的内容中会包括行末尾的'\n'字符。
 * 如果要获取读取字符串的长度，可以调用strlen函数获得。
 *
 * 总结：自动加\0,最多size-1,事先分配空间： char* buff =(char*)malloc(size);
 * 注意：这段代码设计到了清空缓冲区的操作（见35左右）：while((ch = getchar()) != '\n' && ch != EOF);//清空缓冲区的一般方法
 * 什么时候需要清空缓冲区：需要清空缓冲区的情况：没有消耗完缓冲区，然而以后的指令还需要读缓冲区
 * @return
 */
void fget_read_line_from_stream(){
    //int size = 10;//看看有什么不同,这种情况就是所说的size不够大，也就是消耗不完缓冲区，需要清空的情况
    int size=1024;
    //注意声明了指针也要申请空间，不然根本就没用
    //char* buff = NULL;错误
    char* buff =(char*)malloc(size);//这个malloc很重要

    // read lines
    printf("请输入一行，共需读取5次才能结束（在程序定义的size足够大的情况下需要输入五次）\n");
    int i=0;
    while(NULL != fgets(buff, size, stdin)){
        printf("Read line with len: %d\n", strlen(buff));
        printf("%s\n", buff);
        i++;
        if(i>5){
            //！！！当超过计数5时。清空缓冲区，不然下面会出问题：直接退出了
            //总结：需要清空缓冲区的情况：没有消耗完缓冲区，然而以后的指令还需要读缓冲区
            int ch;//一定要是int 因为EOF是-1
            while((ch = getchar()) != '\n' && ch != EOF);//清空缓冲区的一般方法（最好方法）
            return;
        }
    }
    // free buff
    free(buff);
}