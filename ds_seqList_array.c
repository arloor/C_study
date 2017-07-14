//
// Created by arloor on 17-7-14.
//

#include "header/ds_seqList_array.h"
#include<stdio.h>


//------------------------------------顺序表相关接口-----------------------------------------------

//顺序表的初始化：指定顺序表的长度为0
void initList(SeqList *L) {
    L->len = 0;
}

//插入:   下标为[i];      时间复杂度O(n)
int insert(SeqList *L, int i, char x) {
    int j;
    if ((*L).len >= MAXSIZE) {
        printf("顺序表长度overflow\n");
        return NULL;
    } else if ((i < 0) || (i > (*L).len)) {
        printf("插入的位置不合理\n");
        return NULL;
    } else {
        for (j = (*L).len - 1; j >= i; j--) {
            (*L).data[j + 1] = (*L).data[j];
        }//元素后移
        (*L).data[i] = x;
        (*L).len++;
        return 1;
    }
}


//删除: 时间复杂度O(n)
int delete(SeqList *L, int i) {
    int j;
    if ((*L).len == 0) {
        printf("顺序表为空\n");
        return NULL;
    } else if ((i < 0) || (i > (*L).len - 1)) {
        printf("删除的元素不存在\n");
        return NULL;
    } else {
        for (j = i; j < (*L).len - 1; j++) {
            (*L).data[j - 1] = (*L).data[j];
        }//元素前移
        (*L).len--;
        return 1;
    }
}

//按序号取节点值  O(n)
char getNode(SeqList *L, int i) {
    if (i < 0 || i > (*L).len - 1) {
        printf("位置有误");
        return NULL;
    } else return L->data[i];
}

//节点查询操作
int getElem(SeqList *L, int x) {
    int i;
    for (i = 0; i < L->len; i++) {
        if (x == L->data[i]) {
            return i;
        }
        if (i == L->len - 1)
            return -1;
    }
}
