/*************************************************************************
    > File Name: PackTree.c
    > Author: shuaixiang
    > Mail: shuaixiang@yuewen.com
    > Created Time: Tue 05 Apr 2016 06:56:02 AM UTC
 ************************************************************************/

#include <stdio.h>
#include "include/packTree.h"

#define STACKSIZE 100

static Object * PackStack[STACKSIZE];
static int top = 0;//Mutex

TreeCTX * InitPackTree(){
        top = 0;
        TreeCTX *ctx = (TreeCTX *) calloc(1, sizeof(TreeCTX));
        Object *root = NewObject();
        if(NULL == root){
            return NULL;
        }

        ctx->root = root;
        ctx->node = root;
        ctx->isChild = TRUE;
        return ctx;
}

static void PushStack(Object *obj){
    PackStack[top++] = obj;
}

static Object * PopStack(){
    if( top > 0){
        top--;
        return PackStack[top];
    } else {
        return PackStack[top];
    }
}

void PackNode_String(TreeCTX *ctx, string_t str, size_t len){
    Object *obj = NewObject();
    if( NULL == obj){
        return;
    }
    obj->obj_type = OBJ_TYPE_STR; 
    obj->value.str_val = (string_t) malloc(sizeof(char)*len);
    memcpy(obj->value.str_val, str, len);

    if(TRUE == ctx->isChild){
        ctx->node->child = obj;
        ctx->isChild = FALSE;
    } else {
        ctx->node->next = obj;
    }

    ctx->node = obj;
}

void PackNode_Char(TreeCTX *ctx, char d){
    Object *obj = NewObject();
    if( NULL == obj){
        return;
    }
    obj->obj_type = OBJ_TYPE_INT8;
    obj->value.int8_val = d;

    if(TRUE == ctx->isChild){
        ctx->node->child = obj;
        ctx->isChild = FALSE;
    } else {
        ctx->node->next = obj;
    }
    ctx->node = obj;
}

void PackNode_Short(TreeCTX *ctx, short d){
    Object *obj = NewObject();
    if( NULL == obj){
        return;
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

    if(TRUE == ctx->isChild){
        ctx->node->child = obj;
        ctx->isChild = FALSE;
    } else {
        ctx->node->next = obj;
    }
    ctx->node = obj;
}

void  PackNode_Int(TreeCTX *ctx, int d){
    Object *obj = NewObject();
    if( NULL == obj){
        return;
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

    if(TRUE == ctx->isChild){
        ctx->node->child = obj;
        ctx->isChild = FALSE;
    } else {
        ctx->node->next = obj;
    }
    ctx->node = obj;
}

void  PackNode_Long(TreeCTX *ctx, long d){
    Object *obj = NewObject();
    if( NULL == obj){
        return;
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

    if(TRUE == ctx->isChild){
        ctx->node->child = obj;
        ctx->isChild = FALSE;
    } else {
        ctx->node->next = obj;
    }
    ctx->node = obj;

}

void  PackNode_LongLong(TreeCTX *ctx, long long d){
    Object *obj = NewObject();
    if( NULL == obj){
        return;
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

    if(TRUE == ctx->isChild){
        ctx->node->child = obj;
        ctx->isChild = FALSE;
    } else {
        ctx->node->next = obj;
    }
    ctx->node = obj;
}

void PackNode_UnsignedChar(TreeCTX *ctx, unsigned char d){
    Object *obj = NewObject();
    if( NULL == obj){
        return;
    }
    obj->obj_type = OBJ_TYPE_UINT8;
    obj->value.uint8_val = d;

    if(TRUE == ctx->isChild){
        ctx->node->child = obj;
        ctx->isChild = FALSE;
    } else {
        ctx->node->next = obj;
    }
    ctx->node = obj;
}

void PackNode_UnsignedShort(TreeCTX *ctx, unsigned short d){
    Object *obj = NewObject();
    if( NULL == obj){
        return;
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

    if(TRUE == ctx->isChild){
        ctx->node->child = obj;
        ctx->isChild = FALSE;
    } else {
        ctx->node->next = obj;
    }
    ctx->node = obj;
}

void PackNode_UnsignedInt(TreeCTX *ctx, unsigned int d){
    Object *obj = NewObject();
    if( NULL == obj){
        return;
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

    if(TRUE == ctx->isChild){
        ctx->node->child = obj;
        ctx->isChild = FALSE;
    } else {
        ctx->node->next = obj;
    }
    ctx->node = obj;
}

void PackNode_UnsignedLong(TreeCTX *ctx, unsigned long d){
    Object *obj = NewObject();    
    if( NULL == obj){
        return;
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

    if(TRUE == ctx->isChild){
        ctx->node->child = obj;
        ctx->isChild = FALSE;
    } else {
        ctx->node->next = obj;
    }
    ctx->node = obj;
}

void PackNode_UnsignedLongLong(TreeCTX *ctx, unsigned long long d){
    Object *obj = NewObject();
    if( NULL == obj){
        return;
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

    if(TRUE == ctx->isChild){
        ctx->node->child = obj;
        ctx->isChild = FALSE;
    } else {
        ctx->node->next = obj;
    }
    ctx->node = obj;
}

void PackNode_Nil(TreeCTX *ctx){
    Object *obj = NewObject();
    if( NULL == obj){
        return;
    }
    obj->obj_type = OBJ_TYPE_NIL;
    obj->value.bin_val = 0;

    if(TRUE == ctx->isChild){
        ctx->node->child = obj;
        ctx->isChild = FALSE;
    } else {
        ctx->node->next = obj;
    }
    ctx->node = obj;
}

void PackNode_True(TreeCTX *ctx){
    Object *obj = NewObject();
    if( NULL == obj){
        return;
    }
    obj->obj_type = OBJ_TYPE_TRUE;
    obj->value.bool_val = TRUE;

    if(TRUE == ctx->isChild){
        ctx->node->child = obj;
        ctx->isChild = FALSE;
    } else {
        ctx->node->next = obj;
    }
    ctx->node = obj;
}

void PackNode_False(TreeCTX *ctx){
    Object *obj = NewObject();
    if( NULL == obj){
        return;
    }
    obj->obj_type = OBJ_TYPE_FALSE;
    obj->value.bool_val = FALSE;
    
    if(TRUE == ctx->isChild){
        ctx->node->child = obj;
        ctx->isChild = FALSE;
    } else {
        ctx->node->next = obj;
    }
    ctx->node = obj;
}

void PackNode_Float(TreeCTX *ctx, float d){
    Object *obj = NewObject();
    if( NULL == obj){
        return;
    }
    obj->obj_type = OBJ_TYPE_FLOAT; 
    obj->value.float_val = d;

    if(TRUE == ctx->isChild){
        ctx->node->child = obj;
        ctx->isChild = FALSE;
    } else {
        ctx->node->next = obj;
    }
    ctx->node = obj;
}

void PackNode_Double(TreeCTX *ctx, double d){
    Object *obj = NewObject();
    if( NULL == obj){
        return;
    }
    obj->obj_type = OBJ_TYPE_DOUBLE;
    obj->value.double_val = d;

    if(TRUE == ctx->isChild){
        ctx->node->child = obj;
        ctx->isChild = FALSE;
    } else {
        ctx->node->next = obj;
    }
    ctx->node = obj;
}

void PackNode_Bin(TreeCTX *ctx, ubyte_t * b, size_t len){
    Object *obj = NewObject();
    if( NULL == obj){
        return;
    }
    obj->obj_type = OBJ_TYPE_BIN;
    obj->value.bin_val = (ubyte_t *) malloc(sizeof(ubyte_t)*len);
    memcpy(obj->value.bin_val, b, len);

    if(TRUE == ctx->isChild){
        ctx->node->child = obj;
        ctx->isChild = FALSE;
    } else {
        ctx->node->next = obj;
    }
    ctx->node = obj;
}

void PackNode_ArrayBegin(TreeCTX *ctx){
    Object *obj = NewObject();
    if( NULL == obj){
        return;
    }

    obj->obj_type = OBJ_TYPE_ARRAY;
    ctx->node->next = obj;
    ctx->node = obj;
    ctx->isChild = TRUE;
    PushStack(ctx->node);
}

void PackNode_ArrayEnd(TreeCTX *ctx){
    ctx->node = PopStack();
}

void PackNode_MapBegin(TreeCTX *ctx){
    Object *obj = NewObject();
    if( NULL == obj){
        return;
    }

    obj->obj_type = OBJ_TYPE_MAP;
    ctx->node->next = obj;
    ctx->node = obj;
    ctx->isChild = TRUE;
    PushStack(ctx->node);
}

void PackNode_MapEnd(TreeCTX *ctx){
   ctx->node = PopStack(); 
}

//Object* PackNode_Ext(PackBuffer *pb, size_t len, int8_t type);

