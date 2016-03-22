/*************************************************************************
    > File Name: parse_msg.h
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
    typedef enum{
        OBJ_TYPE_STR = 0x00,
        OBJ_TYPE_BIN = 0x01,
        OBJ_TYPE_INT8 = 0x02,
        OBJ_TYPE_UINT8 = 0x03,
        OBJ_TYPE_INT16 = 0x04,
        OBJ_TYPE_UINT16 = 0x05,
        OBJ_TYPE_INT32 = 0x06,
        OBJ_TYPE_UINT32 = 0x07,
        OBJ_TYPE_INT64 = 0x08,
        OBJ_TYPE_UINT64 = 0x09,
        OBJ_TYPE_FLOAT = 0x0A,
        OBJ_TYPE_DOUBLE = 0x0B,
        OBJ_TYPE_FALSE = 0X0C,
        OBJ_TYPE_TRUE = 0X0D,
        OBJ_TYPE_NIL = 0x0E,
        OBJ_TYPE_ARRAY = 0x0F,
        OBJ_TYPE_MAP = 0x10,
        OBJ_TYPE_EXT = 0x11
    }Object_Type; 
    
    typedef union Object_Value{
        string_t str_val;
        ubyte_t *bin_val;
        int8_t int8_val;
        uint8_t uint8_val;
        int16_t int16_val;
        uint16_t uint16_val;
        int32_t int32_val;
        uint32_t uint32_val;
        int64_t int64_val;
        uint64_t uint64_val;
        float float_val;
        double double_val;
        bool_t bool_val;
    } Object_Value;

    typedef struct Object{
        bool_t isKey;
        Object_Type key_type;
        Object_Type obj_type;
        struct Object *next;
        struct Object *child;
        Object_Value value;
        int obj_len;
        int key_len;
        Object_Value key;
    } Object;
    
    typedef struct Context{
        Object *root;
        Object *node;
        ubyte_t *buf;
        int off;
    }Context; 
    
//Interfce
    void ParseDispatcher(Context *ctx);
    Object * NewObject();
#ifdef __cplusplus
}
#endif
