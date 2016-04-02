/*************************************************************************
    > File Name: unpacker.h
    > Author: shuaixiang
    > Mail: shuaixiang@yuewen.com
    > Created Time: Fri 11 Mar 2016 03:22:39 AM UTC
 ************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hulu_define.h"

#ifdef __cplusplus
extern "C" {
#endif
    typedef struct Context{
        Object *root;
        Object *node;
        ubyte_t *buf;
        int off;
    }Context; 

//Interfce
Object * MessageUnpacker(ubyte_t *buf, int len);

#ifdef __cplusplus
}
#endif
