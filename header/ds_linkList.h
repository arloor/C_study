//
// Created by arloor on 17-7-23.
//

#ifndef C_STUDY_DS_LINKLIST_H
#define C_STUDY_DS_LINKLIST_H
typedef struct node {
    int data;
    struct node *next;
} LinkList;


/**
 * 单链表初始化
 * 初始化头节点
 * @param head
 * @return
 */
int Initlist(LinkList *head);

/**
 * 创建有n个元素的链表
 * 尾插法
 * 标头节点为空
 * @param n
 * @return 表头结点
 */
LinkList *creatList(int n);

/**
 * 找到第i位的节点，注意第0为空
 * @param head
 * @param i
 * @return
 */
LinkList *find(LinkList *head, int i);

/**
 * 按值查找，返回节点或者NULL
 * @param head
 * @param x
 * @return
 */
LinkList *locate(LinkList *head, int x);

/**
 * 在值为k的节点前插入值为x的节点
 * @param head
 * @param x
 * @param k
 */
void insert_qian(LinkList *head, int x, int k);

/**
 * 在值为k的节点后插入值为x的节点
 * @param head
 * @param x
 * @param k
 */
void insert_hou(LinkList *head, int x, int k);

/**
 * 删除第i个节点
 * @param head
 * @param i
 * @return
 */
LinkList *deletei(LinkList *head, int i);


#endif //C_STUDY_DS_LINKLIST_H
