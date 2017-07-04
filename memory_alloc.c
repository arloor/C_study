//
// Created by arloor on 17-7-5.
//

#include <stdlib.h>
#include <stdio.h>
#include "memory_alloc.h"


void memory_alloc(){
    /**
     * 内存分配例子
     * 首先分配一块former_len个int的内存空间
     * 然后realloc一块小于former_len的内存空间
     * 原来的内容会被截断
     */
    int former_len=50;
    int later_len=30;
    int* ptr=(int*)calloc(former_len,sizeof(int));
    if(ptr){//
        printf("分配成功\n");
        for(int i=0;i<former_len;i++){
            *(ptr+i)=i;
            printf("%d\n",ptr[i]);
        }
    }else{
        printf("calloc失败，退出此函数");
        return;
    }
    printf("\n");

    //注意：realloc消耗了ptr,之后就再也不能使用ptr了，也不能free(ptr)
    int* ptem=realloc(ptr,later_len*sizeof(int));
    if(ptem){
        printf("realloc分配成功\n");
        for(int i=0;i<former_len;i++){
            printf("%d\n",ptem[i]);
            if(i==later_len-1)
                printf("此处截断\n");
        }
    }

    free(ptem);
    ptem=NULL;//必须要将指针置为NULL，为了保险
}