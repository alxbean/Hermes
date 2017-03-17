/*************************************************************************
    > File Name: msgpk_common.c
    > Author: shuaixiang
    > Mail: shuaixiang@yuewen.com
    > Created Time: Sun 18 Dec 2016 04:06:30 PM CST
************************************************************************/

#include <pthread.h>
#include <stdio.h>
#include "msgpk_common.h"
#include "msgpk_define.h"

//free tree bfs

struct bfs_queue* bfs_queue_new(){/*{{{*/
    struct bfs_queue* bq = (struct bfs_queue*) malloc(sizeof(*bq));
    bq->head = NULL;
    bq->tail = NULL;
    pthread_mutex_init(&bq->mutex, NULL);

    return bq;
}/*}}}*/

int bfs_queue_destroy(struct bfs_queue **pbq){/*{{{*/
    if (NULL == pbq){
        perror("bpq:");
        return -1;
    }

    struct bfs_queue* bq = *pbq;
    if (NULL == bq){
        perror("bq:");
        return -1;
    }

    while (bq->head != NULL)
        bfs_queue_pop(bq);

    free(bq);
    *pbq = NULL;

    return 0;
}/*}}}*/

int bfs_queue_push(struct bfs_queue *bq, struct msgpk_object* obj){/*{{{*/
    if (NULL == obj){
        perror("obj:");
        return -1;
    }

    struct bfs_queue_node* new_node = (struct bfs_queue_node*) malloc(sizeof(*new_node));
    new_node->obj = obj;
    new_node->next_node = NULL;

    pthread_mutex_lock(&bq->mutex);
    if (NULL == bq->tail){
        bq->head = new_node;
        bq->tail = new_node;
    } else {
        bq->tail->next_node = new_node;
        bq->tail = new_node;
    }
    pthread_mutex_unlock(&bq->mutex);

    return 0;
}/*}}}*/

struct msgpk_object* bfs_queue_pop(struct bfs_queue *bq){/*{{{*/
    pthread_mutex_lock(&bq->mutex);
    if (NULL == bq->head){
        printf("queue is empty\n");
        pthread_mutex_unlock(&bq->mutex);
        return NULL;
    } else {
        struct bfs_queue_node* node = bq->head;
        bq->head = bq->head->next_node;
        if (NULL == bq->head)
            bq->tail = NULL;
        pthread_mutex_unlock(&bq->mutex);
        struct msgpk_object* obj = node->obj;
        free(node);
        return obj;
    }
}/*}}}*/
