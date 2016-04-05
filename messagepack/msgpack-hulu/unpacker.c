/*************************************************************************
    > File Name: unparker.c
    > Author: shuaixiang
    > Mail: shuaixiang@yuewen.com
    > Created Time: Fri 11 Mar 2016 03:24:11 AM UTC
 ************************************************************************/
#include "include/unpacker.h"

#define STR_LEN 100

//declare
static void ParseEXT(Context *ctx);
static void ParseMap(Context *ctx);
static void ParseArray(Context *ctx);
static void ParseBin(Context *ctx);
static void ParseString(Context *ctx);
static void ParseBool(Context *ctx);
static void ParseNil(Context *ctx);
static void ParseInteger(Context *ctx);
static void ParseFloat(Context *ctx);
static void ParseDispatcher(Context *ctx);

//define
static void ParseEXT(Context *ctx){/*{{{*/
    ubyte_t *index = ctx->buf + ctx->off;
    int *off = &ctx->off;
    ubyte_t head = *index & 0xFF;
    int len = 0;

    switch(head){
        case 0xD4:
        {
            len = 1; 
            *off += 2;
            int start = *off;
            Object *parent = ctx->node;
            parent->obj_len = len;

            while((*off - start) < len){
               Object *new_node = NewObject();
               if(*off == start)
                   parent->child = new_node;
               else
                   ctx->node->next = new_node;
               ctx->node = new_node;
               ctx->node->isKey = TRUE; 
               ParseDispatcher(ctx);//key
               ctx->node->isKey = FALSE; 
               ParseDispatcher(ctx);//value
               ctx->node = new_node;
               ctx->node->isKey = TRUE;//set flag key-value
            }
            
            break;
        }
        case 0xD5:
        {
            len = 2; 
            *off += 2;
            int start = *off;
            Object *parent = ctx->node;
            parent->obj_len = len;

            while((*off - start) < len){
               Object *new_node = NewObject();
               if(*off == start)
                   parent->child = new_node;
               else
                   ctx->node->next = new_node;
               ctx->node = new_node;
               ctx->node->isKey = TRUE; 
               ParseDispatcher(ctx);//key
               ctx->node->isKey = FALSE; 
               ParseDispatcher(ctx);//value
               ctx->node = new_node;
               ctx->node->isKey = TRUE;//set flag key-value
            }
            
            break;
        }
        case 0xD6:
        {
            len = 4; 
            *off += 2;
            int start = *off;
            Object *parent = ctx->node;
            parent->obj_len = len;

            while((*off - start) < len){
               Object *new_node = NewObject();
               if(*off == start)
                   parent->child = new_node;
               else
                   ctx->node->next = new_node;
               ctx->node = new_node;
               ctx->node->isKey = TRUE; 
               ParseDispatcher(ctx);//key
               ctx->node->isKey = FALSE; 
               ParseDispatcher(ctx);//value
               ctx->node = new_node;
               ctx->node->isKey = TRUE;//set flag key-value
            }
            
            break;

        }
        case 0xD7:
        {
            len = 8; 
            *off += 2;
            int start = *off;
            Object *parent = ctx->node;
            parent->obj_len = len;

            while((*off - start) < len){
               Object *new_node = NewObject();
               if(*off == start)
                   parent->child = new_node;
               else
                   ctx->node->next = new_node;
               ctx->node = new_node;
               ctx->node->isKey = TRUE; 
               ParseDispatcher(ctx);//key
               ctx->node->isKey = FALSE; 
               ParseDispatcher(ctx);//value
               ctx->node = new_node;
               ctx->node->isKey = TRUE;//set flag key-value
            }
            
            break;
        }
        case 0xD8:
        {
            len = 16; 
            *off += 2;
            int start = *off;
            Object *parent = ctx->node;
            parent->obj_len = len;

            while((*off - start) < len){
               Object *new_node = NewObject();
               if(*off == start)
                   parent->child = new_node;
               else
                   ctx->node->next = new_node;
               ctx->node = new_node;
               ctx->node->isKey = TRUE; 
               ParseDispatcher(ctx);//key
               ctx->node->isKey = FALSE; 
               ParseDispatcher(ctx);//value
               ctx->node = new_node;
               ctx->node->isKey = TRUE;//set flag key-value
            }
            
            break;

        }
        case 0xC7:
        {
            len = *(index + 1); 
            *off += 3;
            int start = *off;
            Object *parent = ctx->node;
            parent->obj_len = len;

             while((*off - start) < len){
                Object *new_node = NewObject();
                if(*off == start)
                    parent->child = new_node;
                else
                    ctx->node->next = new_node;
                ctx->node = new_node;
                ctx->node->isKey = TRUE; 
                ParseDispatcher(ctx);//key
                ctx->node->isKey = FALSE; 
                ParseDispatcher(ctx);//value
                ctx->node = new_node;
                ctx->node->isKey = TRUE;//set flag key-value
            }
            
            break;
        }
        case 0xC8:
        {
            len = (*(index + 1) << 8) | *(index + 2); 
            *off += 4;
            int start = *off;
            Object *parent = ctx->node;

            while((*off - start) < len){
                Object *new_node = NewObject();
                if(*off == start)
                    parent->child = new_node;
                 else
                    ctx->node->next = new_node;
                 ctx->node = new_node;
                 ctx->node->isKey = TRUE; 
                 ParseDispatcher(ctx);//key
                 ctx->node->isKey = FALSE; 
                 ParseDispatcher(ctx);//value
                 ctx->node = new_node;
                 ctx->node->isKey = TRUE;//set flag key-value
            }

            break;
        }
        case 0xC9:
        {
            len = (*(index + 1) << 24) | (*(index + 2) << 16) | (*(index + 3) << 8) | *(index + 4); 
            *off += 6;
            int start = *off;
            Object *parent = ctx->node;

            while((*off - start) < len){
                Object *new_node = NewObject();
                if(*off == start)
                    parent->child = new_node;
                 else
                    ctx->node->next = new_node;
                ctx->node = new_node;
                ctx->node->isKey = TRUE; 
                ParseDispatcher(ctx);//key
                ctx->node->isKey = FALSE; 
                ParseDispatcher(ctx);//value
                ctx->node = new_node;
                ctx->node->isKey = TRUE;//set flag key-value
            }

            break;
        }

        default:
        {
            printf("0x%x unimplement\n", head);
        }
    }
   
}/*}}}*/

static void ParseMap(Context *ctx){/*{{{*/
    ubyte_t *index = ctx->buf + ctx->off;
    int *off = &ctx->off;
    ubyte_t head = *index & 0xFF;
    int len = 0, i = 0;
    
    if((head & 0xF0) == 0x80){
        len = 0x0F & head;
        *off += 1;
        Object *parent = ctx->node;
        parent->obj_len = len;
        for(i = 0; i < len; i++){
            Object *new_node = NewObject();
            if(0 == i)
                parent->child = new_node;
            else
                ctx->node->next = new_node;
            ctx->node = new_node;
            ctx->node->isKey = TRUE;
            ParseDispatcher(ctx);//key
            ctx->node->isKey = FALSE;
            ParseDispatcher(ctx);//value
            ctx->node = new_node;
            ctx->node->isKey = TRUE;//set flag key-value
        }

        return;
    }

    if(head == 0xDE){
        len = (*(index + 1) << 8) | *(index + 2); 
        *off += 3;
        Object *parent = ctx->node;
        parent->obj_len = len;
        for(i = 0; i < len; i++){
            Object *new_node = NewObject();
            if(0 == i)
                parent->child = new_node;
            else
                ctx->node->next = new_node;
            ctx->node = new_node;
            ctx->node->isKey = TRUE;
            ParseDispatcher(ctx);//key
            ctx->node->isKey = FALSE;
            ParseDispatcher(ctx);//value
            ctx->node = new_node;
            ctx->node->isKey = TRUE;//set flag key-value
        }

        return;
    }

    if(head == 0xDF){
        len = (*(index + 1) << 24) | (*(index + 2) << 16) | (*(index + 3) << 8) | *(index + 4); 
        *off += 5;
        Object *parent = ctx->node;
        parent->obj_len = len;
        for(i = 0; i < len; i++){
            Object *new_node = NewObject();
            if(0 == i)
                parent->child = new_node;
            else
                ctx->node->next = new_node;
            ctx->node = new_node;
            ctx->node->isKey = TRUE;
            ParseDispatcher(ctx);//key
            ctx->node->isKey = FALSE;
            ParseDispatcher(ctx);//value
            ctx->node = new_node;
            ctx->node->isKey = TRUE;//set flag key-value
        }

        return;
    }

    printf("0x%x unimplement\n", head);
}/*}}}*/

static void ParseArray(Context *ctx){/*{{{*/
    ubyte_t *index = ctx->buf + ctx->off;
    int *off = &ctx->off;
    ubyte_t head = *index & 0xFF;
    int len = 0, i = 0;

    if((head & 0xF0) == 0x90){
        len = 0x0F & head;
        *off += 1;
        Object *parent = ctx->node;
        parent->obj_len = len;
        for(i = 0; i < len; i++){
            Object *new_node = NewObject();
            if(0 == i)
                parent->child = new_node;
            else
                ctx->node->next = new_node;
            ctx->node = new_node;
            ParseDispatcher(ctx);
            ctx->node = new_node;//reset ctx->node as the new_node
        }
        return;
    }
    if(head == 0xDC){
        len = (*(index + 1) << 8) | *(index + 2); 
        *off += 3;
        Object *parent = ctx->node;
        parent->obj_len = len;
        for(i = 0; i < len; i++){
            Object *new_node = NewObject();
            if(0 == i)
                parent->child = new_node;
            else
                ctx->node->next = new_node;
            ctx->node = new_node;
            ParseDispatcher(ctx);
            ctx->node = new_node;//reset ctx->node as the new_node
        }
        return;
    }
    if(head == 0xDD){
        len = (*(index + 1) << 24) | (*(index + 2) << 16) | (*(index + 3) << 8) | *(index + 4); 
        *off += 5;
        Object *parent = ctx->node;
        parent->obj_len = len;
        for(i = 0; i < len; i++){
            Object *new_node = NewObject();
            if(0 == i)
                parent->child = new_node;
            else
                ctx->node->next = new_node;
            ctx->node = new_node;
            ParseDispatcher(ctx);
            ctx->node = new_node;//reset ctx->node as the new_node
        }
        return;
    }

    printf("0x%x unimplement\n", head);
}/*}}}*/

static void ParseBin(Context *ctx){/*{{{*/
    ubyte_t *index = ctx->buf + ctx->off;
    int *off = &ctx->off;
    ubyte_t head = *index & 0xFF;
    ubyte_t *bin= NULL;
    int len = 0;
    
    switch(head){
        case 0xC4: 
            len = *(index+1);
            ctx->node->obj_len = len;
            printf("len: %d\n", len);
            bin = (ubyte_t *) malloc(sizeof(ubyte_t)*len);
            memcpy(bin, (index + 2), len);
            ctx->node->value.bin_val = bin;
            *off += (len + 1);
            break;
        case 0xC5:
            len = (*(index+1)<<8) | *(index+2);
            printf("len: %d\n", len);
            bin = (ubyte_t *) malloc(sizeof(ubyte_t)*len);
            memcpy(bin, (index + 3), len);
            ctx->node->value.bin_val = bin;
            *off += (len + 3);
            break;
        case 0xC6:
            len = (*(index + 1)<<24) | (*(index + 2)<<16) | (*(index + 3)<<8) | *(index + 4);
            printf("len: %d\n", len);
            bin = (ubyte_t*) malloc(sizeof(ubyte_t)*len);
            memcpy(bin, (index + 5), len);
            ctx->node->value.bin_val = bin;
            *off += (len+ 5);
            break;
        default:
            printf("0x%x unimplement\n", head);
    }
}/*}}}*/

static void ParseString(Context *ctx){/*{{{*/
    ubyte_t *index = ctx->buf + ctx->off;
    int *off = &ctx->off;
    ubyte_t head = *index & 0xFF;
    string_t str = NULL;
    int len = 0;

    if ((head & 0xE0) == 0xA0){
        len = head &0x1F;
        printf("len: %d\n", len);
        str = (char *) malloc(sizeof(char)*len);
        memcpy(str, (index + 1), len);
        *off += (len + 1);
        if(ctx->node->isKey == FALSE){
            ctx->node->obj_len = len;
            ctx->node->value.str_val = str;
        }else{
            ctx->node->key_len = len;
            ctx->node->key.str_val = str;
        }
        return;
    }
    
    switch(head){
        case 0xD9: 
            len = *(index+1);
            ctx->node->obj_len = len;
            printf("len: %d\n", len);
            str = (char *) malloc(sizeof(char)*len);
            memcpy(str, (index + 2), len);
            *off += (len + 2);
            if(ctx->node->isKey == FALSE){
                ctx->node->obj_len = len;
                ctx->node->value.str_val = str;
            }else{
                ctx->node->key_len = len;
                ctx->node->key.str_val = str;
            }
            return;
        case 0xDA:
            len = (*(index + 1)<<8) | *(index+2);
            ctx->node->obj_len = len;
            printf("len: %d\n", len);
            str = (char *) malloc(sizeof(char)*len);
            memcpy(str, (index + 3), len);
            *off += (len + 3);
            if(ctx->node->isKey == FALSE){
                ctx->node->obj_len = len;
                ctx->node->value.str_val = str;
            }else{
                ctx->node->key_len = len;
                ctx->node->key.str_val = str;
            }
            return;
        case 0xDB:
            len = (*(index + 1)<<24) | (*(index + 2)<<16) | (*(index + 3)<<8) | *(index + 4);
            ctx->node->obj_len = len;
            printf("len: %d\n", len);
            str = (char *) malloc(sizeof(char)*len);
            memcpy(str, (index + 5), len);
            *off += (len + 5);
            if(ctx->node->isKey == FALSE){
                ctx->node->obj_len = len;
                ctx->node->value.str_val = str;
            }else{
                ctx->node->key_len = len;
                ctx->node->key.str_val = str;
            }
            return;
        default:
            printf("0x%x unimplement\n", head);
    }
}/*}}}*/

static void ParseBool(Context *ctx){/*{{{*/
    ubyte_t *index = ctx->buf + ctx->off;
    int *off = &ctx->off;
    ubyte_t head = *index;
    *off +=  1;
    if(head == 0xC2)
        ctx->node->value.bool_val = TRUE;
    else if(head == 0xC3)
        ctx->node->value.bool_val = FALSE;
    else
        printf("0x%x unimplement\n", head);
}/*}}}*/

static void ParseNil(Context *ctx){/*{{{*/
    ubyte_t *index = ctx->buf + ctx->off;
    int *off = &ctx->off;
    ubyte_t head = *index;
    *off += 1;
    if(head == 0xC0){
        ctx->node->value.bin_val = 0;
        return; 
    }
    else
        printf("0x%x unimplement\n", head);

}/*}}}*/

static void ParseInteger(Context *ctx){/*{{{*/
    ubyte_t *index = ctx->buf + ctx->off;
    int *off = &ctx->off;
    ubyte_t head = *index & 0xFF;
    int i = 0;
    
    if( (head & 0x80) == 0){
        uint8_t val = (uint8_t)(*index);
        *off += 1;
        if(ctx->node->isKey == FALSE){
            ctx->node->value.uint8_val = val;
        }
        else{
            ctx->node->key.uint8_val  = val;
        }
        return;
    }

    if( (head & 0xE0) == 0xE0){
        int8_t val = (*index);
        *off += 1;
        if(ctx->node->isKey == FALSE){
            ctx->node->value.int8_val = val;
        }
        else{
            ctx->node->key.int8_val = val;
        }
       return;
    }

    switch(head)
    {
        case 0xCC:
        {
            uint8_t uval_8 = (uint8_t) *(index + 1);
            printf("val: %u\n", uval_8);
            *off += 2;
            if(ctx->node->isKey == FALSE){
                ctx->node->value.uint8_val = uval_8;
            }
            else{
                ctx->node->key.uint8_val = uval_8;
            }
            break;
        }
            
        case 0xCD:
        {
            uint16_t uval_16 = (uint16_t)((*(index + 1) << 8) | *(index + 2));
            printf("val: %u\n", uval_16);
            *off += 3;
            if(ctx->node->isKey == FALSE){
                ctx->node->value.uint16_val = uval_16;
            }
            else{
                ctx->node->key.uint16_val  = uval_16;
            }
            break;
        }
        case 0xCE:
        {
            uint32_t uval_32 = (uint32_t)((*(index + 1) << 24) | (*(index + 2) << 16) | (*(index + 3) << 8) | *(index + 4));
            printf("val: %u\n", uval_32);
            *off += 5;
            if(ctx->node->isKey == FALSE){
                ctx->node->value.uint32_val= uval_32;
            }
            else{
                ctx->node->key.uint32_val = uval_32;
            }
            break;
        }
        case 0xCF:
        {
            uint64_t uval_64 = 0; 
            for(i = 0; i < 8; i++){
                uint64_t tmp = *(index + 8 - i );
                uval_64 |= tmp << (i * 8);
            }
            printf("val: %lu\n", uval_64);
            *off += 9;
            if(ctx->node->isKey == FALSE){
                ctx->node->value.uint64_val= uval_64;
            }
            else{
                ctx->node->key.uint64_val = uval_64;
            }
        }
        case 0xD0:
        {
            int8_t val_8 = (int8_t) *(index + 1);
            printf("val: %d\n", val_8);
            *off += 2;
            if(ctx->node->isKey == FALSE){
                ctx->node->value.int8_val = val_8;
            }
            else{
                ctx->node->key.int8_val = val_8;
            }
            break;
        }

        case 0xD1:
        {
            int16_t val_16 = (int16_t) ((*(index + 1) << 8) | *(index + 2));
            printf("val: %d\n", val_16);
            *off += 3;
            if(ctx->node->isKey == FALSE){
                ctx->node->value.int16_val = val_16;
            }
            else{
                ctx->node->key.int16_val = val_16;
            }
            break;
        }

        case 0xD2:
        {
            int32_t val_32 = (int32_t) ((*(index + 1) << 24) | (*(index + 2) << 16) | (*(index + 3) << 8) | *(index + 4));
            printf("val: %d\n", val_32);
            *off += 5;
            if(ctx->node->isKey == FALSE){
                ctx->node->value.int32_val = val_32;
            }
            else{
                ctx->node->key.int32_val = val_32;
            }
            break;
        }

        case 0xD3:
        {
            int64_t val_64 = *(index + 1);
            for(i = 0; i < 8; i++){
                int64_t tmp = *(index + 8 - i );
                val_64 |= tmp << (i * 8);
            }
            printf("val: %ld\n", val_64);
            *off += 9;
            if(ctx->node->isKey == FALSE){
                ctx->node->value.int64_val = val_64;
            }
            else{
                ctx->node->key.int64_val = val_64;
            }
        }
        default:
            printf("0x%x unimplement\n", head);
    }
}/*}}}*/

static void ParseFloat(Context *ctx){/*{{{*/
    ubyte_t *index = ctx->buf + ctx->off;
    int *off = &ctx->off;
    ubyte_t head = *index;
    union{
        float float_tmp;
        ubyte_t float_buf[4]; 
        double double_tmp;
        ubyte_t double_buf[8];
    } float_union;

    if(head == 0xCA){
        int i = 0;
        for(i = 0; i < 4; i++){
            float_union.float_buf[i] = *(index + 4 - i);  
        }
        *off += 5;
        ctx->node->value.float_val = float_union.float_tmp;
        return;
    }
    if(head == 0xCB){
        int i  = 0;
        for(i = 0; i < 8; i++){
            float_union.double_buf[i] = *(index + 8 - i);
        }
        *off += 9;
        ctx->node->value.double_val = float_union.double_tmp;
        return;
    }
        printf("0x%x unimplement\n", head);
}/*}}}*/

static void ParseDispatcher(Context *ctx){/*{{{*/
    ubyte_t *index = ctx->buf + ctx->off;
    ubyte_t head = *index;
    if ( (head & 0x80) == 0){
        if(ctx->node->isKey == TRUE) 
            ctx->node->key_type = OBJ_TYPE_POSITIVE_INT;
        else
            ctx->node->obj_type = OBJ_TYPE_POSITIVE_INT;
            
        ParseInteger(ctx);
        printf("positive fixint\n");
        return;
    }
    if( (head & 0xE0) == 0xE0){
        if(ctx->node->isKey == TRUE) 
            ctx->node->key_type = OBJ_TYPE_NEGATIVE_INT;
        else
            ctx->node->obj_type = OBJ_TYPE_NEGATIVE_INT;
        ParseInteger(ctx);
        printf("negative fixint\n");
        return;
    }
    if( (head & 0xE0) == 0xA0){
        if(ctx->node->isKey == TRUE) 
            ctx->node->key_type = OBJ_TYPE_STR;
        else
            ctx->node->obj_type = OBJ_TYPE_STR;
        ParseString(ctx);
        printf("fixStr\n");
        return;
    }
    if( (head & 0xF0) == 0x90){
        ctx->node->obj_type = OBJ_TYPE_ARRAY;
        ParseArray(ctx);
        printf("fixarray\n");
        return;
    }
    if( (head & 0xF0) == 0x80){
        ctx->node->obj_type = OBJ_TYPE_MAP;
        ParseMap(ctx);
        printf("FixMap\n");
        return;
    }

    switch(head & 0xFF){
        case 0xC0:
            ctx->node->obj_type = OBJ_TYPE_NIL;
            ParseNil(ctx);
            printf("NIL\n");
            return;
        case 0xC2:
            ctx->node->obj_type = OBJ_TYPE_FALSE;
            ParseBool(ctx);
            printf("boolean false\n");
            return;
        case 0xC3:
            ctx->node->obj_type = OBJ_TYPE_TRUE;
            ParseBool(ctx);
            printf("boolean true\n");
            return;
        case 0xCA:
            ctx->node->obj_type = OBJ_TYPE_FLOAT;
            ParseFloat(ctx);
            printf("float\n");
            return;
        case 0xCB:
            ctx->node->obj_type = OBJ_TYPE_DOUBLE;
            ParseFloat(ctx);
            printf("DOUBLE\n");
            return;
        case 0xCC:
            if(ctx->node->isKey == TRUE) 
                ctx->node->key_type = OBJ_TYPE_UINT8;
            else
                ctx->node->obj_type = OBJ_TYPE_UINT8;
            ParseInteger(ctx);
            printf("unsigned int 8\n");
            return;
        case 0xCD:
            if(ctx->node->isKey == TRUE) 
                ctx->node->key_type = OBJ_TYPE_UINT16;
            else
                ctx->node->obj_type = OBJ_TYPE_UINT16;
            ParseInteger(ctx);
            printf("unsigned int 16\n");
            return;
        case 0xCE:
            if(ctx->node->isKey == TRUE) 
                ctx->node->key_type = OBJ_TYPE_UINT32;
            else
                ctx->node->obj_type = OBJ_TYPE_UINT32;
            ParseInteger(ctx);
            printf("unsigned int 32\n");
            return;
        case 0xCF:
            if(ctx->node->isKey == TRUE) 
                ctx->node->key_type = OBJ_TYPE_UINT64;
            else
                ctx->node->obj_type = OBJ_TYPE_UINT64;
            ParseInteger(ctx);
            printf("unsigned int 64\n"); 
            return;
        case 0xD0:
            if(ctx->node->isKey == TRUE) 
                ctx->node->key_type = OBJ_TYPE_INT8;
            else
                ctx->node->obj_type = OBJ_TYPE_INT8;
            ParseInteger(ctx);
            printf("signed int 8\n");
            return;
        case 0xD1:
            if(ctx->node->isKey == TRUE) 
                ctx->node->key_type = OBJ_TYPE_INT16;
            else
                ctx->node->obj_type = OBJ_TYPE_INT16;
            ParseInteger(ctx);
            printf("signed int 16\n");
            return;
        case 0xD2:
            if(ctx->node->isKey == TRUE) 
                ctx->node->key_type = OBJ_TYPE_INT32;
            else
                ctx->node->obj_type = OBJ_TYPE_INT32;
            ParseInteger(ctx);
            printf("signed int 32\n");
            return;
        case 0xD3:
            if(ctx->node->isKey == TRUE) 
                ctx->node->key_type = OBJ_TYPE_INT64;
            else
                ctx->node->obj_type = OBJ_TYPE_INT64;
            ParseInteger(ctx);
            printf("signed int 64\n");
            return;
        case 0xC4:
            ctx->node->obj_type = OBJ_TYPE_BIN;
            ParseBin(ctx);
            printf("bin 8\n");
            return;
        case 0xC5:
            ctx->node->obj_type = OBJ_TYPE_BIN;
            ParseBin(ctx);
            printf("bin 16\n");
            return;
        case 0xC6:
            ctx->node->obj_type = OBJ_TYPE_BIN;
            ParseBin(ctx);
            printf("bin 32\n");
            return;
        case 0xD9:
            if(ctx->node->isKey == TRUE) 
                ctx->node->key_type = OBJ_TYPE_STR;
            else
                ctx->node->obj_type = OBJ_TYPE_STR;
            ParseString(ctx);
            printf("str8\n");
            return;
        case 0xDA:
            if(ctx->node->isKey == TRUE) 
                ctx->node->key_type = OBJ_TYPE_STR;
            else
                ctx->node->obj_type = OBJ_TYPE_STR;
            ParseString(ctx);
            printf("str 16\n");
            return;
        case 0xDB:
            if(ctx->node->isKey == TRUE) 
                ctx->node->key_type = OBJ_TYPE_STR;
            else
                ctx->node->obj_type = OBJ_TYPE_STR;
            ParseString(ctx);
            printf("str 32\n");
            return;
        case 0xDC:
            ctx->node->obj_type = OBJ_TYPE_ARRAY;
            ParseArray(ctx);
            printf("array 16\n");
            return;
        case 0xDD:
            ctx->node->obj_type = OBJ_TYPE_ARRAY;
            ParseArray(ctx);
            printf("array 32\n");
            return;
        case 0xDE:
            printf("map 16\n");
            return;
        case 0xDF:
            ctx->node->obj_type = OBJ_TYPE_MAP;
            ParseMap(ctx);
            printf("map 32\n");
            return;
        case 0xC7:
            ctx->node->obj_type = OBJ_TYPE_EXT;
            ParseEXT(ctx);
            printf("ext 8\n");
            return;
        case 0xC8:
            ctx->node->obj_type = OBJ_TYPE_EXT;
            ParseEXT(ctx);
            printf("ext 16\n");
            return;
        case 0xC9:
            ctx->node->obj_type = OBJ_TYPE_EXT;
            ParseEXT(ctx);
            printf("ext 32\n");
            return;
        default:
            printf("not found\n");
    }
}/*}}}*/

Object * MessageUnpacker(ubyte_t *buf, int len){
    Context *ctx = (Context *)calloc(1, sizeof(Context));
    ctx->buf = buf;
    while(ctx->off < len){
        int tmp_off = ctx->off;
        Object *new_node = NewObject();
        if(ctx->off == 0)
            ctx->root = new_node;
        else
            ctx->node->next = new_node;
        ctx->node = new_node;
        ParseDispatcher(ctx);
        if(ctx->off == tmp_off)
            break;
    }

    return ctx->root;
}
