/*************************************************************************
    > File Name: hulu_define.c
    > Author: shuaixiang
    > Mail: shuaixiang@yuewen.com
    > Created Time: Tue 05 Apr 2016 07:36:20 AM UTC
************************************************************************/
#include <stdlib.h>
#include "include/hulu_define.h"

Object * NewObject(){
    Object *new_node = (Object *)calloc(1, sizeof(Object));
    if(NULL == new_node){
        perror("NewObject:");
        return NULL;
    }

    new_node->isKey = FALSE;
    return new_node;
}
