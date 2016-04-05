/*************************************************************************
    > File Name: PackTree.c
    > Author: shuaixiang
    > Mail: shuaixiang@yuewen.com
    > Created Time: Tue 05 Apr 2016 06:56:02 AM UTC
 ************************************************************************/

#include <stdio.h>
#include "include/packTree.h"

void PackTree_Child(Object *node, Object *obj){
    if( NULL == node->child ){
        printf("node has no child~!\n");
        return;
    }
    node->child = obj;
}


void PackTree_Next(Object *node, Object *obj){
    if( NULL == node->next ){
        printf("node has no next\n");
        return;
    }
    node->next = obj;
}


Object* PackNode_String(string_t str, size_t len){
    Object *obj = NewObject();
    if( NULL == obj){
        return NULL;
    }
    obj->obj_type = OBJ_TYPE_STR; 
    memcpy(obj->value.str_val, str, len); 
    return obj;
}

Object* PackNode_Char(char d){
    Object *obj = NewObject();
    if( NULL == obj){
        return NULL;
    }
    obj->obj_type = OBJ_TYPE_INT8;
    obj->value.int8_val = d;
    return obj;
}

Object* PackNode_Short(short d){
    Object *obj = NewObject();
    if( NULL == obj){
        return NULL;
    }
    if ( 2 == sizeof(short) ){
        obj->obj_type = OBJ_TYPE_INT16;
        obj->value.int16_val = d;
    } else if ( 4 == sizeof(short) ){
        obj->obj_type = OBJ_TYPE_INT32;
        obj->value.int32_val = d;
    } else{
        obj->obj_type = OBJ_TYPE_INT64;
        obj->value.int64_val = d;
    }
    return obj;
}

Object* PackNode_Int(int d){
    Object *obj = NewObject();
    if( NULL == obj){
        return NULL;
    }
    if ( 2 == sizeof(int) ){
        obj->obj_type = OBJ_TYPE_INT16;
        obj->value.int16_val = d;
    } else if( 4 == sizeof(int) ){
        obj->obj_type = OBJ_TYPE_INT32;
        obj->value.int32_val = d;
    } else{
        obj->obj_type = OBJ_TYPE_INT64;
        obj->value.int32_val = d;
    }

    return obj;
}

Object* PackNode_Long(long d){
    Object *obj = NewObject();
    if( NULL == obj){
        return NULL;
    }
    if ( 2 == sizeof(long) ){
        obj->obj_type = OBJ_TYPE_INT16;
        obj->value.int16_val = d;
    } else if ( 4 == sizeof(long) ){
        obj->obj_type = OBJ_TYPE_INT32;
        obj->value.int32_val = d;
    } else {
        obj->obj_type = OBJ_TYPE_INT64;
        obj->value.int64_val = d;
    }

    return obj;
}

Object* PackNode_LongLong(long long d){
    Object *obj = NewObject();
    if( NULL == obj){
        return NULL;
    }
    if ( 2 == sizeof(long long) ){
        obj->obj_type = OBJ_TYPE_INT16;
        obj->value.int16_val  = d;
    } else if ( 4 == sizeof(long long) ){
        obj->obj_type = OBJ_TYPE_INT32;
        obj->value.int32_val = d;
    } else {
        obj->obj_type = OBJ_TYPE_INT64;
        obj->value.int64_val = d;
    }
    return obj;
}

Object* PackNode_UnsignedChar(unsigned char d){
    Object *obj = NewObject();
    if( NULL == obj){
        return NULL;
    }
    obj->obj_type = OBJ_TYPE_UINT8;
    obj->value.uint8_val = d;
    return obj;
}

Object* PackNode_UnsignedShort(unsigned short d){
    Object *obj = NewObject();
    if( NULL == obj){
        return NULL;
    }
    if ( 2 == sizeof(unsigned short) ){
        obj->obj_type = OBJ_TYPE_UINT16;
        obj->value.uint16_val = d;
    } else if ( 4 == sizeof(unsigned short) ){
        obj->obj_type = OBJ_TYPE_UINT32;
        obj->value.uint32_val = d;
    } else {
        obj->obj_type = OBJ_TYPE_UINT64;
        obj->value.uint64_val = d;
    }

    return obj;
}

Object* PackNode_UnsignedInt(unsigned int d){
    Object *obj = NewObject();
    if( NULL == obj){
        return NULL;
    }
    if ( 2 == sizeof(unsigned int) ){
        obj->obj_type = OBJ_TYPE_UINT16;
        obj->value.uint16_val = d; 
    } else if ( 4 == sizeof(unsigned int) ){
        obj->obj_type = OBJ_TYPE_UINT32;
        obj->value.uint32_val = d;
    } else {
        obj->obj_type = OBJ_TYPE_UINT64;
        obj->value.uint64_val = d;
    }

    return obj;
}

Object* PackNode_UnsignedLong(unsigned long d){
    Object *obj = NewObject();    
    if( NULL == obj){
        return NULL;
    }
    if ( 2 == sizeof(unsigned long) ){
        obj->obj_type = OBJ_TYPE_UINT16;
        obj->value.uint16_val = d;
    } else if ( 4 == sizeof(unsigned long) ){
        obj->obj_type = OBJ_TYPE_UINT32;
        obj->value.uint32_val = d;
    } else {
        obj->obj_type = OBJ_TYPE_UINT64;
        obj->value.uint64_val = d;
    }

    return obj;
}

Object* PackNode_UnsignedLongLong(unsigned long long d){
    Object *obj = NewObject();
    if( NULL == obj){
        return NULL;
    }
    if ( 2 == sizeof(unsigned long long) ){
        obj->obj_type = OBJ_TYPE_UINT16;
        obj->value.uint16_val = d;
    } else if ( 4 == sizeof(unsigned long long) ){
        obj->obj_type = OBJ_TYPE_UINT32;
        obj->value.uint32_val = d;
    } else {
        obj->obj_type = OBJ_TYPE_UINT64;
        obj->value.uint64_val = d;
    }

    return obj;
}

Object* PackNode_Nil(){
    Object *obj = NewObject();
    if( NULL == obj){
        return NULL;
    }
    obj->obj_type = OBJ_TYPE_NIL;
    obj->value.bin_val = 0;
    return obj;
}

Object* PackNode_True(){
    Object *obj = NewObject();
    if( NULL == obj){
        return NULL;
    }
    obj->obj_type = OBJ_TYPE_TRUE;
    obj->value.bool_val = TRUE;
    return obj;
}

Object* PackNode_False(){
    Object *obj = NewObject();
    if( NULL == obj){
        return NULL;
    }
    obj->obj_type = OBJ_TYPE_FALSE;
    obj->value.bool_val = FALSE;
    return obj;
}

Object* PackNode_Float(float d){
    Object *obj = NewObject();
    if( NULL == obj){
        return NULL;
    }
    obj->obj_type = OBJ_TYPE_FLOAT; 
    obj->value.float_val = d;

    return obj;
}

Object* PackNode_Double(double d){
    Object *obj = NewObject();
    if( NULL == obj){
        return NULL;
    }
    obj->obj_type = OBJ_TYPE_DOUBLE;
    obj->value.double_val = d;
    return obj;
}

Object* PackNode_Bin(ubyte_t * b, size_t len){
    Object *obj = NewObject();
    if( NULL == obj){
        return NULL;
    }
    obj->obj_type = OBJ_TYPE_BIN;
    memcpy(obj->value.bin_val, b, len);
    return obj;
}

Object* PackNode_Array(PackBuffer *pb, size_t n);
Object* PackNode_Map(PackBuffer *pb, size_t n);
Object* PackNode_Ext(PackBuffer *pb, size_t len, int8_t type);

