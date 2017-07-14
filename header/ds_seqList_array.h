//
// Created by arloor on 17-7-14.
//

#ifndef C_TEST_SEQLIST_H
#define C_TEST_SEQLIST_H
//数据结构：顺序表——顺序存储
#define MAXSIZE 100 //表空间最大为100
typedef struct {
    char data[MAXSIZE]; //这里的char可以是其他任意的数据类型
    int len;            //顺序表的长度
} SeqList;

//顺序表的初始化：指定顺序表的长度为0
void initList(SeqList *L);


//插入:   下标为[i];      时间复杂度O(n)
int insert(SeqList *L, int i, char x);

//删除: 时间复杂度O(n)
int delete(SeqList *L, int i);

//按序号取节点值  O(n)
char getNode(SeqList *L, int i);


//节点查询操作
int getElem(SeqList *L, int x);

#endif //C_TEST_SEQLIST_H
