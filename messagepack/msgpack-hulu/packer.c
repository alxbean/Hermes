/*************************************************************************
    > File : packer.c
    > Author: shuaixiang
    > Mail: shuaixiang@yuewen.com
    > Created Time: Mon 07 Mar 2016 07:23:11 AM UTC
 ************************************************************************/

#include <stdio.h>
#include "unpacker.c"
#include "./include/packer.h"

#define INIT_BUFFER_SIZE 8192

//ENDIAN_LITTLE
#define TAKE8_8(d)  ((uint8_t *)&d)[0]
#define TAKE8_16(d) ((uint8_t *)&d)[0]
#define TAKE8_32(d) ((uint8_t *)&d)[0]
#define TAKE8_64(d) ((uint8_t *)&d)[0]

//ENDIAN_BIG

PackBuffer* NewPackBuffer(){
    PackBuffer * pb = (PackBuffer *) calloc(1, sizeof(PackBuffer)); 
    if( NULL == pb){
        perror("NewPackBuffer:");
        return NULL;
    }

    return pb;
}

int PackAppendBuffer(PackBuffer *pb, const char *buf, size_t len){
    if(pb->alloc - pb->off < len){
        void tmp;
        size_t nsize = (pb->alloc) ? pb->alloc*2 : INIT_BUFFER_SIZE;
        while(nsize < pb->off + len){
            size_t tmp_nsize = nsize * 2;
            if (tmp_nize <= nsize){
                nsize = pb->off + len;
                break;
            }
            nsize = tmp_nsize;
        }
    
        tmp = realloc(pb->buffer, nsize);
        if(!tmp)
         return -1;

        pb->buffer = (ubyte_t)tmp;
        pb->alloc = nsize;
    }

    memcpy(pb->buffer + pb->size, buf, len);
    pb->size += len;
    return 0;
}

void PackString(PackBuffer *pb, size_t len){
   if(len < 32){
       ubyte_t head = 0xa0 | (uint8_t)len; 
       PackAppendBuffer(pb, &TAKE8_8(head), 1); 
   } else if(len < 256){
       ubyte_t buf[2];
       buf[0] = 0xd9;
       buf[1] = ((uint8_t *)&len)[0];
       PackAppendBuffer(pb, buf, 2);
   } else if(len < 65536){
       ubyte_t buf[3];
       buf[0] = 0xda;
       buf[1] = ((uint8_t*)&len)[0];
       buf[2] = ((uint8_t*)&len)[1];
       PackAppendBuffer(pb, buf, 3); 
   } else{
       ubyte_t buf[5];
       buf[0] = 0xdb;
       buf[1] = ((uint8_t*)&len)[0];
       buf[2] = ((uint8_t*)&len)[1];
       buf[3] = ((uint8_t*)&len)[2];
       buf[4] = ((uint8_t*)&len)[3];
   }
}

void PackStringBody(PackBuffer *pb, const void* body, size_t len){
    PackAppendBuffer(pb, (const unsigned char*)body, len);
}

void PackMessage(PackBuffer *pb, Object *obj){/*{{{*/
    if(obj->isKey == TRUE){
        switch(obj->key_type){
            case OBJ_TYPE_STR:
                msgpack_pack_str(pk, obj->key_len);
                msgpack_pack_str_body(pk, obj->key.str_val, obj->key_len);
                printf("str_val:%s\n", obj->value.str_val);
                break;
            case OBJ_TYPE_INT8:
                msgpack_pack_int8(pk, obj->key.int8_val);
                printf("int8: %d\n", obj->key.int8_val);
                break;
            case OBJ_TYPE_INT16:
                msgpack_pack_int16(pk, obj->key.int16_val);
                printf("int16: %d\n", obj->key.int16_val);
                break;
            case OBJ_TYPE_INT32:
                msgpack_pack_int32(pk, obj->key.int32_val);
                printf("int32: %d\n", obj->key.int32_val);
                break;
            case OBJ_TYPE_INT64:
                msgpack_pack_int64(pk, obj->key.int64_val);
                printf("int64: %ld\n", obj->key.int64_val);
                break;
            case OBJ_TYPE_UINT8:
                msgpack_pack_uint8(pk, obj->key.uint8_val);
                printf("uint8: %u\n", obj->key.uint8_val);
                break;
            case OBJ_TYPE_UINT16:
                msgpack_pack_uint16(pk, obj->key.uint16_val); 
                printf("uint16: %u\n", obj->key.uint16_val);
                break;
            case OBJ_TYPE_UINT32:
                msgpack_pack_uint32(pk, obj->key.uint32_val);
                printf("uint32: %u\n", obj->key.uint32_val);
                break;
            case OBJ_TYPE_UINT64:
                msgpack_pack_uint64(pk, obj->key.uint64_val);
                printf("uint64: %lu\n", obj->key.uint64_val);
                break;
            default:
                break;
        }
    }
                                                  
    switch(obj->obj_type){
        case OBJ_TYPE_STR:
            msgpack_pack_str(pk, obj->obj_len);
            msgpack_pack_str_body(pk, obj->value.str_val, obj->obj_len);
            printf("str_val:%s\n", obj->value.str_val);
            break;
        case OBJ_TYPE_NIL:
            msgpack_pack_nil(pk);
            printf("NULL\n");
            break;
        case OBJ_TYPE_TRUE:
            msgpack_pack_true(pk);
            printf("TRUE:%d\n", obj->value.bool_val);
            break;
        case OBJ_TYPE_FALSE:
            msgpack_pack_false(pk);
            printf("FALSE:%d\n", obj->value.bool_val);
            break;
        case OBJ_TYPE_BIN:
            msgpack_pack_bin(pk, obj->obj_len);
            msgpack_pack_bin_body(pk, &obj->value, obj->obj_len);
            printf("BIN: %s\n", obj->value.bin_val);
            break;
        case OBJ_TYPE_FLOAT:
            msgpack_pack_float(pk, obj->value.float_val);
            printf("float: %f\n", obj->value.float_val);
            break;
        case OBJ_TYPE_DOUBLE:
            msgpack_pack_double(pk, obj->value.double_val);
            printf("double: %lf\n", obj->value.double_val);
            break;
        case OBJ_TYPE_INT8:
            msgpack_pack_int8(pk, obj->value.int8_val);
            printf("int8: %d\n", obj->value.int8_val);
            break;
        case OBJ_TYPE_INT16:
            msgpack_pack_int16(pk, obj->value.int16_val);
            printf("int16: %d\n", obj->value.int16_val);
            break;
        case OBJ_TYPE_INT32:
            msgpack_pack_int32(pk, obj->value.int32_val);
            printf("int32: %d\n", obj->value.int32_val);
            break;
        case OBJ_TYPE_INT64:
            msgpack_pack_int64(pk, obj->value.int64_val);
            printf("int64: %ld\n", obj->value.int64_val);
            break;
        case OBJ_TYPE_UINT8:
            msgpack_pack_uint8(pk, obj->value.uint8_val);
            printf("uint8: %u\n", obj->value.uint8_val);
            break;
        case OBJ_TYPE_UINT16:
            msgpack_pack_uint16(pk, obj->value.uint16_val); 
            printf("uint16: %u\n", obj->value.uint16_val);
            break;
        case OBJ_TYPE_UINT32:
            msgpack_pack_uint32(pk, obj->value.uint32_val);
            printf("uint32: %u\n", obj->value.uint32_val);
            break;
        case OBJ_TYPE_UINT64:
            msgpack_pack_uint64(pk, obj->value.uint64_val);
            printf("uint64: %lu\n", obj->value.uint64_val);
            break;
        default:
            break;
    }

    if(obj->child != NULL){
        switch(obj->obj_type){
            case OBJ_TYPE_ARRAY:
                msgpack_pack_array(pk, obj->obj_len);
                printf("Array: %d\n", obj->obj_len);
                break;
            case OBJ_TYPE_MAP:
                msgpack_pack_map(pk, obj->obj_len);
                printf("Map: %d\n", obj->obj_len);
                break;
            case OBJ_TYPE_EXT:
                msgpack_pack_ext(pk, obj->obj_len, 0x00);
                printf("EXT: %d\n", obj->obj_len);
                break;
            default:
                break;
        }
        PackMessage(pk, obj->child);
    }

    if(obj->next != NULL){
        PackMessage(pk, obj->next);
    }
        
}/*}}}*/


PackBuffer *MessagePacker(Object *obj){
        /* creates buffer and serializer instance. */
        PackBuffer *pb = NewPackBuffer(); 
        PackMessage(pb, obj);

        return pb;
}

void print(char const *buf, unsigned int len){
    size_t i = 0;
    for(; i < len; ++i)
       printf("0x%02x ", 0xff & buf[i]);
    printf("\n");
}

int main(){
    ubyte_t str[] = {0xD9, 0x23, 0x61, 0x62, 0x63, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6D, 0x6D, 0x6D, 0x6D, 0x6D, 0x73, 0x73, 0x73, 0x73, 0x73, 0x73, 0x73, 0x73, 0x73,  0x73, 0x73, 0x73, 0x73, 0x73, 0x73, 0x73, 0x73, 0x73};
    ubyte_t array[] = {0x93, 0x01, 0x02, 0x03};
    ubyte_t float_val[] = {0xCA, 0x43, 0x5C, 0x00, 0x00};
    ubyte_t map[] = {0x82, 0x02, 0xA5, 0x68, 0x65, 0x6C, 0x6C, 0x6F, 0x03, 0xA5, 0x77, 0x6F, 0x72, 0x6C, 0x64};
    
    //char *ret_str = parseString(str, &off);
    //printf("%s\n", ret_str);
    Context *ctx = (Context *)calloc(1, sizeof(Context));
    ctx->root = NewObject(); 
    ctx->node = ctx->root;
    //ctx->buf = array;
    //ctx->buf = float_val;
    //ctx->buf = ext;
    ctx->buf = str;
    printf("==============original===================\n");
    print((char const *)str, (unsigned int )37);
    printf("==============building===================\n");
    ParseDispatcher(ctx);
    printf("==============visit======================\n");
    msgpack_sbuffer *buf = MessagePacker(ctx->root);
    printf("==============result======================\n");
    print(buf->data, buf->size);

    //ctx->buf = float_val;

}
