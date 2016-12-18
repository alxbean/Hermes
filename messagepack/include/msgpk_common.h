/*************************************************************************
> File Name: msgpk_common.h
> Author: shuaixiang
> Mail: shuaixiang@yuewen.com
> Created Time: Tue 05 Apr 2016 06:21:32 AM UTC
************************************************************************/

#ifndef _MSGPK_COMMON_H_
#define _MSGPK_COMMON_H_

#ifdef __cplusplus
extern "C" {
#endif
    #include <pthread.h>

    struct bfs_queue_node{
        struct msgpk_object* obj;
        struct bfs_queue_node* next_node;
    };
    
    struct bfs_queue{
        struct bfs_queue_node* head;
        struct bfs_queue_node* tail;
        pthread_mutex_t mutex;
    };
    struct bfs_queue* bfs_queue_new();
    int bfs_queue_push(struct bfs_queue* bq, struct msgpk_object* obj);
    struct msgpk_object* bfs_queue_pop(struct bfs_queue *bq);
    int bfs_queue_destroy(struct bfs_queue **pbq);

#ifdef __cplusplus
}
#endif
#endif

