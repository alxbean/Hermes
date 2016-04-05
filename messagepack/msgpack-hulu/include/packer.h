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

//basic pack method
void PackString(PackBuffer *pb, size_t len);
void PackStringBody(PackBuffer *pb, const void* body, size_t len);
void PackFixNumPositive(PackBuffer *pb, uint8_t d);
void PackFixNumNegative(PackBuffer *pb, int8_t d);
void PackFixInt8_u(PackBuffer *pb, uint8_t d);
void PackFixInt16_u(PackBuffer *pb, uint16_t d);
void PackFixInt32_u(PackBuffer *pb, uint32_t d);
void PackFixInt64_u(PackBuffer *pb, uint64_t d);
void PackFixInt8(PackBuffer *pb, int8_t d);
void PackFixInt16(PackBuffer *pb, int16_t d);
void PackFixInt16(PackBuffer *pb, int16_t d);
void PackFixInt32(PackBuffer *pb, int32_t d);
void PackFixInt64(PackBuffer *pb, int64_t d);
void PackNil(PackBuffer *pb);
void PackTrue(PackBuffer *pb);
void PackFalse(PackBuffer *pb);
void PackFloat(PackBuffer *pb, float d);
void PackDouble(PackBuffer *pb, double d);
void PackArray(PackBuffer *pb, size_t n);
void PackMap(PackBuffer *pb, size_t n);
void PackBin(PackBuffer *pb, size_t len);
void PackBinBody(PackBuffer *pb, const void *body, size_t len);
void PackExt(PackBuffer *pb, size_t len, int8_t type);
void PackExtBody(PackBuffer *pb, const void *body, size_t len);

#ifdef __cplusplus
}
#endif
