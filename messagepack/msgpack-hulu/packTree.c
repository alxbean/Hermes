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

//declare
static void PushStack(Object *obj);
static Object * PopStack();
static Object * PackNode_String(string_t str, size_t len, Object *obj, bool_t isKey);
static Object * PackNode_Char(char d, Object *obj, bool_t isKey);
static Object * PackNode_Short(short d, Object *obj, bool_t isKey);
static Object * PackNode_Int(int d, Object *obj, bool_t isKey);
static Object * PackNode_Long(long d, Object *obj, bool_t isKey);
static Object * PackNode_LongLong(long long d, Object *obj, bool_t isKey);
static Object * PackNode_UnsignedChar(unsigned char d, Object *obj, bool_t isKey);
static Object * PackNode_UnsignedShort(unsigned short d, Object *obj, bool_t isKey);
static Object * PackNode_UnsignedInt(unsigned int d, Object *obj, bool_t isKey);
static Object * PackNode_UnsignedLong(unsigned long d, Object *obj, bool_t isKey);
static Object * PackNode_UnsignedLongLong(unsigned long long d, Object *obj, bool_t isKey);
static Object * PackNode_Nil(Object *obj, bool_t isKey);
static Object * PackNode_True(Object *obj, bool_t isKey);
static Object * PackNode_False(Object *obj, bool_t isKey);
static Object * PackNode_Float(float d, Object *obj, bool_t isKey);
static Object * PackNode_Double(double d, Object *obj, bool_t isKey);
static Object * PackNode_Bin(ubyte_t * b, size_t len, Object *obj, bool_t isKey);

//define
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

//PackNode
static Object * PackNode_String(string_t str, size_t len, Object *obj, bool_t isKey){
    if( NULL == obj){
        return NULL;
    }
    
    if (FALSE == isKey){
        obj->obj_type = OBJ_TYPE_STR; 
        obj->value.str_val = (string_t) malloc(sizeof(char)*len);
        memcpy(obj->value.str_val, str, len);
    } else {
        obj->isKey = isKey;
        obj->key_type = OBJ_TYPE_STR;
        obj->key.str_val = (string_t) malloc(sizeof(char)*len);
        memcpy(obj->key.str_val, str, len);
    }

    return obj;
}

static Object * PackNode_Char(char d, Object *obj, bool_t isKey){
    if( NULL == obj ){
        return NULL;
    }

    if (FALSE == isKey){
        obj->obj_type = OBJ_TYPE_INT8;
        obj->value.int8_val = d;
    } else {
        obj->isKey = isKey;
        obj->key_type = OBJ_TYPE_INT8;
        obj->key.int8_val = d;
    }

    return obj;
}

static Object * PackNode_Short(short d, Object *obj, bool_t isKey){
    if( NULL == obj ){
        return NULL;
    }

    if (FALSE == isKey){
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
    } else {
        obj->isKey = isKey;
        if ( 2 == sizeof(short) ){
            obj->key_type = OBJ_TYPE_INT16;
            obj->key.int16_val = d;
        } else if ( 4 == sizeof(short) ){
            obj->key_type = OBJ_TYPE_INT32;
            obj->key.int32_val = d;
        } else{
            obj->key_type = OBJ_TYPE_INT64;
            obj->key.int64_val = d;
        }
    }

    return obj;
}

static Object * PackNode_Int(int d, Object *obj, bool_t isKey){
    if( NULL == obj){
        return NULL;
    }

    if (FALSE == isKey){
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
    } else {
        obj->isKey = isKey;
        if ( 2 == sizeof(int) ){
            obj->key_type = OBJ_TYPE_INT16;
            obj->key.int16_val = d;
        } else if( 4 == sizeof(int) ){
            obj->key_type = OBJ_TYPE_INT32;
            obj->key.int32_val = d;
        } else{
            obj->key_type = OBJ_TYPE_INT64;
            obj->key.int32_val = d;
        }
    }

    return obj;
}

static Object * PackNode_Long(long d, Object *obj, bool_t isKey){
    if( NULL == obj){
        return NULL;
    }

    if (FALSE == isKey){
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
    } else {
        obj->isKey = isKey;
        if ( 2 == sizeof(long) ){
            obj->key_type = OBJ_TYPE_INT16;
            obj->key.int16_val = d;
        } else if ( 4 == sizeof(long) ){
            obj->key_type = OBJ_TYPE_INT32;
            obj->key.int32_val = d;
        } else {
            obj->key_type = OBJ_TYPE_INT64;
            obj->key.int64_val = d;
        }
    }

    return obj;
}

static Object * PackNode_LongLong(long long d, Object *obj, bool_t isKey){
    if( NULL == obj){
        return NULL;
    }

    if (FALSE == isKey){
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
    } else {
        obj->isKey = isKey;
        if ( 2 == sizeof(long long) ){
            obj->key_type = OBJ_TYPE_INT16;
            obj->key.int16_val  = d;
        } else if ( 4 == sizeof(long long) ){
            obj->key_type = OBJ_TYPE_INT32;
            obj->key.int32_val = d;
        } else {
            obj->key_type = OBJ_TYPE_INT64;
            obj->key.int64_val = d;
        }
    }

    return obj;
}

static Object * PackNode_UnsignedChar(unsigned char d, Object *obj, bool_t isKey){
    if( NULL == obj){
        return NULL;
    }
    
    if (FALSE == isKey){
        obj->obj_type = OBJ_TYPE_UINT8;
        obj->value.uint8_val = d;
    } else {
        obj->isKey = isKey;
        obj->key_type = OBJ_TYPE_UINT8;
        obj->key.uint8_val = d;
    }

    return obj;
}

static Object * PackNode_UnsignedShort(unsigned short d, Object *obj, bool_t isKey){
    if( NULL == obj){
        return NULL;
    }

    if (FALSE == isKey){
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
    } else {
        obj->isKey = isKey;
        if ( 2 == sizeof(unsigned short) ){
            obj->key_type = OBJ_TYPE_UINT16;
            obj->key.uint16_val = d;
        } else if ( 4 == sizeof(unsigned short) ){
            obj->key_type = OBJ_TYPE_UINT32;
            obj->key.uint32_val = d;
        } else {
            obj->key_type = OBJ_TYPE_UINT64;
            obj->key.uint64_val = d;
        }
    }

    return obj;
}

static Object * PackNode_UnsignedInt(unsigned int d, Object *obj, bool_t isKey){
    if( NULL == obj){
        return NULL;
    }

    if (FALSE == isKey){
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
    } else {
        obj->isKey = isKey;
        if ( 2 == sizeof(unsigned int) ){
            obj->key_type = OBJ_TYPE_UINT16;
            obj->key.uint16_val = d; 
        } else if ( 4 == sizeof(unsigned int) ){
            obj->key_type = OBJ_TYPE_UINT32;
            obj->key.uint32_val = d;
        } else {
            obj->key_type = OBJ_TYPE_UINT64;
            obj->key.uint64_val = d;
        }
    }

    return obj;
}

static Object * PackNode_UnsignedLong(unsigned long d, Object *obj, bool_t isKey){
    if( NULL == obj){
        return NULL;
    }

    if (FALSE == isKey){
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
    } else {
        obj->isKey = isKey;
        if ( 2 == sizeof(unsigned long) ){
            obj->key_type = OBJ_TYPE_UINT16;
            obj->key.uint16_val = d;
        } else if ( 4 == sizeof(unsigned long) ){
            obj->key_type = OBJ_TYPE_UINT32;
            obj->key.uint32_val = d;
        } else {
            obj->key_type = OBJ_TYPE_UINT64;
            obj->key.uint64_val = d;
        }
    }

    return obj;

}

static Object * PackNode_UnsignedLongLong(unsigned long long d, Object *obj, bool_t isKey){
    if( NULL == obj){
        return NULL;
    }

    if (FALSE == isKey){
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
    } else {
        obj->isKey = isKey;
        if ( 2 == sizeof(unsigned long long) ){
            obj->key_type = OBJ_TYPE_UINT16;
            obj->key.uint16_val = d;
        } else if ( 4 == sizeof(unsigned long long) ){
            obj->key_type = OBJ_TYPE_UINT32;
            obj->key.uint32_val = d;
        } else {
            obj->key_type = OBJ_TYPE_UINT64;
            obj->key.uint64_val = d;
        }
    }

    return obj;

}

static Object * PackNode_Nil(Object *obj, bool_t isKey){
    if( NULL == obj){
        return NULL;
    }

    if (FALSE == isKey){
        obj->obj_type = OBJ_TYPE_NIL;
        obj->value.bin_val = 0;
    } else {
        obj->isKey = isKey;
        obj->key_type = OBJ_TYPE_NIL;
        obj->key.bin_val = 0;
    }

    return obj;
}

static Object * PackNode_True(Object *obj, bool_t isKey){
    if( NULL == obj){
        return NULL;
    }

    if (FALSE == isKey){
        obj->obj_type = OBJ_TYPE_TRUE;
        obj->value.bool_val = TRUE;
    } else {
        obj->isKey = isKey;
        obj->key_type = OBJ_TYPE_TRUE;
        obj->key.bool_val = TRUE;
    }

    return obj;
}

static Object * PackNode_False(Object *obj, bool_t isKey){
    if( NULL == obj){
        return NULL;
    }

    if (FALSE == isKey){
        obj->obj_type = OBJ_TYPE_FALSE;
        obj->value.bool_val = FALSE;
    } else {
        obj->isKey = isKey;
        obj->key_type = OBJ_TYPE_FALSE;
        obj->key.bool_val = FALSE;
    }
    
    return obj;
}

static Object * PackNode_Float(float d, Object *obj, bool_t isKey){
    if( NULL == obj){
        return NULL;
    }

    if (FALSE == isKey){
        obj->obj_type = OBJ_TYPE_FLOAT; 
        obj->value.float_val = d;
    } else {
        obj->isKey = isKey;
        obj->key_type = OBJ_TYPE_FLOAT; 
        obj->key.float_val = d;
    }

    return obj;
}

static Object * PackNode_Double(double d, Object *obj, bool_t isKey){
    if( NULL == obj){
        return NULL;
    }
    
    if (FALSE == isKey){
        obj->obj_type = OBJ_TYPE_DOUBLE;
        obj->value.double_val = d;
    } else {
        obj->isKey = isKey;
        obj->key_type = OBJ_TYPE_DOUBLE;
        obj->key.double_val = d;
    }

    return obj;

}

static Object * PackNode_Bin(ubyte_t * b, size_t len, Object *obj, bool_t isKey){
    if( NULL == obj){
        return NULL;
    }

    if (FALSE == isKey){
        obj->obj_type = OBJ_TYPE_BIN;
        obj->value.bin_val = (ubyte_t *) malloc(sizeof(ubyte_t)*len);
        memcpy(obj->value.bin_val, b, len);
    } else {
        obj->isKey = isKey;
        obj->key_type = OBJ_TYPE_BIN;
        obj->key.bin_val = (ubyte_t *) malloc(sizeof(ubyte_t)*len);
        memcpy(obj->key.bin_val, b, len);
    }

    return obj;
}



//PackTree
void PackTree_String(TreeCTX *ctx, string_t str, size_t len){
    Object *obj = NewObject();
    if ( NULL == obj )
        return;

    PackNode_String(str, len, obj, FALSE);

    if(TRUE == ctx->isChild){
        ctx->node->child = obj;
        ctx->isChild = FALSE;
    } else {
        ctx->node->next = obj;
    }

    ctx->node = obj;
}

void PackTree_Char(TreeCTX *ctx, char d){
    Object *obj = NewObject();
    if ( NULL == obj )
        return;

    PackNode_Char(d, obj, FALSE);
    if(TRUE == ctx->isChild){
        ctx->node->child = obj;
        ctx->isChild = FALSE;
    } else {
        ctx->node->next = obj;
    }
    ctx->node = obj;
}

void PackTree_Short(TreeCTX *ctx, short d){
    Object *obj = NewObject();
    if ( NULL == obj )
        return;

    PackNode_Short(d, obj, FALSE);

    if(TRUE == ctx->isChild){
        ctx->node->child = obj;
        ctx->isChild = FALSE;
    } else {
        ctx->node->next = obj;
    }

    ctx->node = obj;
}

void PackTree_Int(TreeCTX *ctx, int d){
    Object *obj = NewObject();
    if ( NULL == obj)
        return;

    PackNode_Int(d, obj, FALSE);

    if(TRUE == ctx->isChild){
        ctx->node->child = obj;
        ctx->isChild = FALSE;
    } else {
        ctx->node->next = obj;
    }

    ctx->node = obj;
}

void  PackTree_Long(TreeCTX *ctx, long d){
    Object *obj = NewObject();
    if ( NULL == obj )
        return;

    PackNode_Long(d, obj, FALSE);

    if(TRUE == ctx->isChild){
        ctx->node->child = obj;
        ctx->isChild = FALSE;
    } else {
        ctx->node->next = obj;
    }
    ctx->node = obj;
}

void  PackTree_LongLong(TreeCTX *ctx, long long d){
    Object *obj = NewObject();
    if ( NULL == obj )
        return;
    
    PackNode_LongLong(d, obj, FALSE);

    if(TRUE == ctx->isChild){
        ctx->node->child = obj;
        ctx->isChild = FALSE;
    } else {
        ctx->node->next = obj;
    }
    ctx->node = obj;
}

void PackTree_UnsignedChar(TreeCTX *ctx, unsigned char d){
    Object *obj = NewObject();
    if ( NULL == obj )
        return;

    PackNode_UnsignedChar(d, obj, FALSE);
    if(TRUE == ctx->isChild){
        ctx->node->child = obj;
        ctx->isChild = FALSE;
    } else {
        ctx->node->next = obj;
    }
    ctx->node = obj;
}

void PackTree_UnsignedShort(TreeCTX *ctx, unsigned short d){
    Object *obj = NewObject();
    if ( NULL == obj )
        return;

    PackNode_UnsignedShort(d, obj, FALSE);
    if(TRUE == ctx->isChild){
        ctx->node->child = obj;
        ctx->isChild = FALSE;
    } else {
        ctx->node->next = obj;
    }
    ctx->node = obj;
}

void PackTree_UnsignedInt(TreeCTX *ctx, unsigned int d){
    Object *obj = NewObject();
    if ( NULL == obj )
        return;

    PackNode_UnsignedInt(d, obj, FALSE);

    if(TRUE == ctx->isChild){
        ctx->node->child = obj;
        ctx->isChild = FALSE;
    } else {
        ctx->node->next = obj;
    }
    ctx->node = obj;
}

void PackTree_UnsignedLong(TreeCTX *ctx, unsigned long d){
    Object *obj = NewObject();
    if ( NULL == obj )
        return;

    PackNode_UnsignedLong(d, obj, FALSE);
    if(TRUE == ctx->isChild){
        ctx->node->child = obj;
        ctx->isChild = FALSE;
    } else {
        ctx->node->next = obj;
    }
    ctx->node = obj;
}

void PackTree_UnsignedLongLong(TreeCTX *ctx, unsigned long long d){
    Object *obj = NewObject();
    if ( NULL == obj )
        return;

    PackNode_UnsignedLongLong(d, obj, FALSE);
    if(TRUE == ctx->isChild){
        ctx->node->child = obj;
        ctx->isChild = FALSE;
    } else {
        ctx->node->next = obj;
    }
    ctx->node = obj;
}

void PackTree_Nil(TreeCTX *ctx){
    Object *obj = NewObject();
    if ( NULL == obj )
        return;

    PackNode_Nil(obj, FALSE);
    if(TRUE == ctx->isChild){
        ctx->node->child = obj;
        ctx->isChild = FALSE;
    } else {
        ctx->node->next = obj;
    }
    ctx->node = obj;
}

void PackTree_True(TreeCTX *ctx){
    Object *obj = NewObject();
    if ( NULL == obj )
        return;

    PackNode_True(obj, FALSE);
    if(TRUE == ctx->isChild){
        ctx->node->child = obj;
        ctx->isChild = FALSE;
    } else {
        ctx->node->next = obj;
    }
    ctx->node = obj;
}

void PackTree_False(TreeCTX *ctx){
    Object *obj = NewObject();
    if ( NULL == obj )
        return;

    PackNode_False(obj, FALSE);
    if(TRUE == ctx->isChild){
        ctx->node->child = obj;
        ctx->isChild = FALSE;
    } else {
        ctx->node->next = obj;
    }
    ctx->node = obj;
}

void PackTree_Float(TreeCTX *ctx, float d){
    Object *obj = NewObject();
    if ( NULL == obj )
        return;

    PackNode_Float(d, obj, FALSE);
    if(TRUE == ctx->isChild){
        ctx->node->child = obj;
        ctx->isChild = FALSE;
    } else {
        ctx->node->next = obj;
    }
    ctx->node = obj;
}

void PackTree_Double(TreeCTX *ctx, double d){
    Object *obj = NewObject();
    if ( NULL == obj )
        return;

    PackNode_Double(d, obj, FALSE);
    if(TRUE == ctx->isChild){
        ctx->node->child = obj;
        ctx->isChild = FALSE;
    } else {
        ctx->node->next = obj;
    }
    ctx->node = obj;
}

void PackTree_Bin(TreeCTX *ctx, ubyte_t * b, size_t len){
    Object *obj = NewObject();
    if ( NULL == obj )
        return;
    
    PackNode_Bin(b, len, obj, FALSE);
    if(TRUE == ctx->isChild){
        ctx->node->child = obj;
        ctx->isChild = FALSE;
    } else {
        ctx->node->next = obj;
    }
    ctx->node = obj;
}

void PackTree_ArrayBegin(TreeCTX *ctx){
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

void PackTree_ArrayEnd(TreeCTX *ctx){
    ctx->node = PopStack();
}

void PackTree_MapBegin(TreeCTX *ctx){
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

void PackTree_MapEnd(TreeCTX *ctx){
   ctx->node = PopStack(); 
}

//PackMap
void PackMap_String_Int(TreeCTX *ctx, string_t k, size_t len,  int v){
    Object * obj = NewObject();
    if( NULL == obj){
        return;
    }

    PackNode_String(k, len, obj, TRUE);
    PackNode_Int(v, obj, FALSE);

    if(TRUE == ctx->isChild){
        ctx->node->child = obj;
        ctx->isChild = FALSE;
    } else {
        ctx->node->next = obj;
    }
    ctx->node = obj;
}

void PackMap_String_Long(TreeCTX *ctx, string_t k, size_t len,  long v){
    Object * obj = NewObject();
    if( NULL == obj){
        return;
    }

    PackNode_String(k, len, obj, TRUE);
    PackNode_Long(v, obj, FALSE);

    if(TRUE == ctx->isChild){
        ctx->node->child = obj;
        ctx->isChild = FALSE;
    } else {
        ctx->node->next = obj;
    }
    ctx->node = obj;
}

void PackMap_String_LongLong(TreeCTX *ctx, string_t k, size_t len,  long long v){
    Object * obj = NewObject();
    if( NULL == obj){
        return;
    }

    PackNode_String(k, len, obj, TRUE);
    PackNode_LongLong(v, obj, FALSE);

    if(TRUE == ctx->isChild){
        ctx->node->child = obj;
        ctx->isChild = FALSE;
    } else {
        ctx->node->next = obj;
    }
    ctx->node = obj;
}

void PackMap_String_Float(TreeCTX *ctx, string_t k, size_t len,  float v){
    Object * obj = NewObject();
    if( NULL == obj){
        return;
    }

    PackNode_String(k, len, obj, TRUE);
    PackNode_Float(v, obj, FALSE);

    if(TRUE == ctx->isChild){
        ctx->node->child = obj;
        ctx->isChild = FALSE;
    } else {
        ctx->node->next = obj;
    }
    ctx->node = obj;
}

void PackMap_String_Double(TreeCTX *ctx, string_t k, size_t len, double v){
    Object * obj = NewObject();
    if( NULL == obj){
        return;
    }

    PackNode_String(k, len, obj, TRUE);
    PackNode_Double(v, obj, FALSE);

    if(TRUE == ctx->isChild){
        ctx->node->child = obj;
        ctx->isChild = FALSE;
    } else {
        ctx->node->next = obj;
    }
    ctx->node = obj;
}

void PackMap_String_String(TreeCTX *ctx, string_t k, size_t len,  string_t v, size_t vlen){
    Object * obj = NewObject();
    if( NULL == obj){
        return;
    }

    PackNode_String(k, len, obj, TRUE);
    PackNode_String(v, vlen, obj, FALSE);

    if(TRUE == ctx->isChild){
        ctx->node->child = obj;
        ctx->isChild = FALSE;
    } else {
        ctx->node->next = obj;
    }
    ctx->node = obj;
}

void PackMap_String_Bin(TreeCTX *ctx, string_t k, size_t len, ubyte_t *v, size_t vlen){
    Object * obj = NewObject();
    if( NULL == obj){
        return;
    }

    PackNode_String(k, len, obj, TRUE);
    PackNode_Bin(v, vlen, obj, FALSE);

    if(TRUE == ctx->isChild){
        ctx->node->child = obj;
        ctx->isChild = FALSE;
    } else {
        ctx->node->next = obj;
    }
    ctx->node = obj;
}


void PackMap_Int_Int(TreeCTX *ctx, int k, int v){
    Object * obj = NewObject();
    if( NULL == obj){
        return;
    }

    PackNode_Int(k, obj, TRUE);
    PackNode_Int(v, obj, FALSE);

    if(TRUE == ctx->isChild){
        ctx->node->child = obj;
        ctx->isChild = FALSE;
    } else {
        ctx->node->next = obj;
    }
    ctx->node = obj;
}

void PackMap_Int_Long(TreeCTX *ctx, int k, long v){
    Object * obj = NewObject();
    if( NULL == obj){
        return;
    }

    PackNode_Int(k, obj, TRUE);
    PackNode_Long(v, obj, FALSE);

    if(TRUE == ctx->isChild){
        ctx->node->child = obj;
        ctx->isChild = FALSE;
    } else {
        ctx->node->next = obj;
    }
    ctx->node = obj;
}

void PackMap_Int_LongLong(TreeCTX *ctx, int k, long long v){
    Object * obj = NewObject();
    if( NULL == obj){
        return;
    }

    PackNode_Int(k, obj, TRUE);
    PackNode_LongLong(v, obj, FALSE);

    if(TRUE == ctx->isChild){
        ctx->node->child = obj;
        ctx->isChild = FALSE;
    } else {
        ctx->node->next = obj;
    }
    ctx->node = obj;
}

void PackMap_Int_Float(TreeCTX *ctx, int k, float v){
    Object * obj = NewObject();
    if( NULL == obj){
        return;
    }

    PackNode_Int(k, obj, TRUE);
    PackNode_Float(v, obj, FALSE);

    if(TRUE == ctx->isChild){
        ctx->node->child = obj;
        ctx->isChild = FALSE;
    } else {
        ctx->node->next = obj;
    }
    ctx->node = obj;
}

void PackMap_Int_Double(TreeCTX *ctx, int k, double v){
    Object * obj = NewObject();
    if( NULL == obj){
        return;
    }

    PackNode_Int(k, obj, TRUE);
    PackNode_Double(v, obj, FALSE);

    if(TRUE == ctx->isChild){
        ctx->node->child = obj;
        ctx->isChild = FALSE;
    } else {
        ctx->node->next = obj;
    }
    ctx->node = obj;
}

void PackMap_Int_String(TreeCTX *ctx, int k, string_t v, size_t vlen){
    Object * obj = NewObject();
    if( NULL == obj){
        return;
    }

    PackNode_Int(k, obj, TRUE);
    PackNode_String(v, vlen, obj, FALSE);

    if(TRUE == ctx->isChild){
        ctx->node->child = obj;
        ctx->isChild = FALSE;
    } else {
        ctx->node->next = obj;
    }
    ctx->node = obj;
}

void PackMap_Int_Bin(TreeCTX *ctx, int k, ubyte_t *v, size_t vlen){
    Object * obj = NewObject();
    if( NULL == obj){
        return;
    }

    PackNode_Int(k, obj, TRUE);
    PackNode_Bin(v, vlen, obj, FALSE);

    if(TRUE == ctx->isChild){
        ctx->node->child = obj;
        ctx->isChild = FALSE;
    } else {
        ctx->node->next = obj;
    }
    ctx->node = obj;
}
//Object* PackNode_Ext(PackBuffer *pb, size_t len, int8_t type);

