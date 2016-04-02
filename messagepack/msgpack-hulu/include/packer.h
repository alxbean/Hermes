/*************************************************************************
    > File Name: packer.h
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
    typedef struct PackBuffer{
        size_t off;
        ubyte_t *buffer;
        size_t alloc;
    }PackBuffer; 
    
//Interfce
PackBuffer* MessagePacker(Object *obj);
Object * FindNode(Object *root , int argc, ...);
void print(const ubyte_t *buf, unsigned int len);
void printJSON(Object *obj);
void printTree(Object *obj, int space);

#ifdef __cplusplus
}
#endif
