//
// Created by arloor on 17-7-23.
//

#include <stdlib.h>
#include <stdio.h>
#include "header/ds_linkList.h"

/**
 * 单链表初始化
 * 初始化头节点
 * @param head
 * @return
 */
int Initlist(LinkList *head) {
    if ((head = (LinkList *) malloc(sizeof(LinkList))) == NULL)
        return 0;
    head->next = NULL;
    return 1;
}

/**
 * 创建有n个元素的链表
 * 尾插法
 * 标头节点为空
 * @param n
 * @return 表头结点
 */
LinkList *creatList(int n) {
    int x, k;
    LinkList *head, *r, *p;
    p = (LinkList *) malloc(sizeof(LinkList));
    head = p;
    p->next = NULL;
    r = p;
    for (k = 0; k < n; k++) {
        printf("请输入第%d位的数字\n", k);
        scanf("%d", &x);
        fflush(stdin);
        p = (LinkList *) malloc(sizeof(LinkList));
        p->data = x;
        p->next = NULL;
        r->next = p;
        r = r->next;
    }
    return head;
}

/**
 * 找到第i位的节点，注意第0为空
 * @param head
 * @param i
 * @return
 */
LinkList *find(LinkList *head, int i) {
    int j;
    LinkList *p;
    p = head->next;
    j = 1;
    while ((p != NULL) && (j < i)) {
        p = p->next;
        j++;
    }
    return p;
}

/**
 * 按值查找，返回节点或者NULL
 * @param head
 * @param x
 * @return
 */
LinkList *locate(LinkList *head, int x) {
    LinkList *p;
    p = p->next;
    while (p) {
        if (p->data != x) {
            p = p->next;
        } else break;
    }
    return p;
}


/**
 * 在值为k的节点前插入值为x的节点
 * @param head
 * @param x
 * @param k
 */
void insert_qian(LinkList *head, int x, int k) {
    LinkList *p, *s;
    s = (LinkList *) malloc(sizeof(LinkList));//生成新的节点
    s->data = x;
    p = head->next;
    if (p == NULL) {//若为空表则新节点作为唯一的节点
        head->next = s;
        s->next = NULL;
    } else {
        while (p && p->data != k)
            p = p->next;
        if (p->data == k) {
            s->next = p->next;
            p->next = s;
        } else {//如果没有找到值为k的节点，将新节点插入到表尾
            p->next = s;
            s->next = NULL;
        }

    }
}

/**
 * 在值为k的节点后插入值为x的节点
 * @param head
 * @param x
 * @param k
 */
void insert_hou(LinkList *head, int x, int k) {
    LinkList *q, *p, *s;
    s = (LinkList *) malloc(sizeof(LinkList));
    s->data = x;
    if (head->next == NULL) {//若位空表，新节点作为唯一节点
        head->next = s;
        s->next = NULL;
    } else {
        q = head;
        p = head->next;
        while (p != NULL) {
            if (p->data != k) {
                q = p;
                p = p->next;
            } else break;
        }
        if (p != NULL) {
            q->next = s;
            s->next = p;
        } else {//若没有找到节点，则在表尾插入
            q->next = s;
            s->next = NULL;
        }
    }
}

/**
 * 删除第i个节点
 * @param head
 * @param i
 * @return
 */
LinkList *deletei(LinkList *head, int i) {
    LinkList *p;
    int j;
    p = head->next;
    j = 1;
    while (p && j < i - 1) {
        p = p->next;
        j++;
    }
    if (p != NULL && p->next != NULL) {
        p->next = p->next->next;
    } else return NULL;
    return head;
}