/*************************************************************************
    > File Name: parse_msg.h
    > Author: shuaixiang
    > Mail: shuaixiang@yuewen.com
    > Created Time: Fri 11 Mar 2016 03:22:39 AM UTC
 ************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "unpacker.h"

#ifdef __cplusplus
extern "C" {
#endif
    typedef struct PackBuffer{
        size_t off;
        ubyte_t *buffer;
        size_t alloc;
    }PackBuffer; 
    
//Interfce
PackBuffer* MessagePacker(Object *obj);

#ifdef __cplusplus
}
#endif
