/*************************************************************************
    > File : packer.c
    > Author: shuaixiang
    > Mail: shuaixiang@yuewen.com
    > Created Time: Mon 07 Mar 2016 07:23:11 AM UTC
 ************************************************************************/

#include <stdio.h>
//#include "unpacker.c"
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

int PackAppendBuffer(PackBuffer *pb, const ubyte_t *buf, size_t len){
    if(pb->alloc - pb->off < len){
        size_t nsize = (pb->alloc) ? pb->alloc*2 : INIT_BUFFER_SIZE;
        while(nsize < pb->off + len){
            size_t tmp_nsize = nsize * 2;
            if (tmp_nsize <= nsize){
                nsize = pb->off + len;
                break;
            }
            nsize = tmp_nsize;
        }
    
        ubyte_t *tmp = (ubyte_t *)realloc(pb->buffer, nsize);
        if(!tmp)
         return -1;

        pb->buffer = (ubyte_t*)tmp;
        pb->alloc = nsize;
    }

    memcpy(pb->buffer + pb->off, buf, len);
    pb->off += len;
    return 0;
}

void PackString(PackBuffer *pb, size_t len){
   if(len < 32){
       ubyte_t head = 0xa0 | (ubyte_t)len; 
       PackAppendBuffer(pb, &TAKE8_8(head), 1); 
   } else if(len < 256){
       ubyte_t buf[2];
       buf[0] = 0xd9;
       buf[1] = ((ubyte_t *)&len)[0];
       PackAppendBuffer(pb, buf, 2);
   } else if(len < 65536){
       ubyte_t buf[3];
       buf[0] = 0xda;
       buf[1] = ((ubyte_t *)&len)[1];
       buf[2] = ((ubyte_t *)&len)[0];
       PackAppendBuffer(pb, buf, 3); 
   } else{
       ubyte_t buf[5];
       buf[0] = 0xdb;
       buf[1] = ((ubyte_t *)&len)[3];
       buf[2] = ((ubyte_t *)&len)[2];
       buf[3] = ((ubyte_t *)&len)[1];
       buf[4] = ((ubyte_t *)&len)[0];
   }
}

void PackStringBody(PackBuffer *pb, const void* body, size_t len){
    PackAppendBuffer(pb, (const ubyte_t*)body, len);
}

void PackFixNumPositive(PackBuffer *pb, uint8_t d){
    PackAppendBuffer(pb, &TAKE8_8(d), 1);
}

void PackFixNumNegative(PackBuffer *pb, int8_t d){
    PackAppendBuffer(pb, &TAKE8_8(d), 1);
}

void PackFixInt8_u(PackBuffer *pb, uint8_t d){
    ubyte_t buf[2] = {0xcc, TAKE8_8(d)};
    PackAppendBuffer(pb, buf, 2);
}

void PackFixInt16_u(PackBuffer *pb, uint16_t d){
    ubyte_t buf[3];
    buf[0] = 0xcd;
    buf[1] = ((ubyte_t *)&d)[1];
    buf[2] = ((ubyte_t *)&d)[0];
    PackAppendBuffer(pb, buf, 3);
}

void PackFixInt32_u(PackBuffer *pb, uint32_t d){
    ubyte_t buf[5];
    buf[0] = 0xce;
    buf[1] = ((ubyte_t *)&d)[3];
    buf[2] = ((ubyte_t *)&d)[2];
    buf[3] = ((ubyte_t *)&d)[1];
    buf[4] = ((ubyte_t *)&d)[0];
    PackAppendBuffer(pb, buf, 5);
}

void PackFixInt64_u(PackBuffer *pb, uint64_t d){
    ubyte_t buf[9];
    buf[0] = 0xce;
    buf[1] = ((ubyte_t *)&d)[7];
    buf[2] = ((ubyte_t *)&d)[6];
    buf[3] = ((ubyte_t *)&d)[5];
    buf[4] = ((ubyte_t *)&d)[4];
    buf[5] = ((ubyte_t *)&d)[3];
    buf[6] = ((ubyte_t *)&d)[2];
    buf[7] = ((ubyte_t *)&d)[1];
    buf[8] = ((ubyte_t *)&d)[0];
    PackAppendBuffer(pb, buf, 9);
}

void PackFixInt8(PackBuffer *pb, int8_t d){
    ubyte_t buf[2] = {0xd0, TAKE8_8(d)};
    PackAppendBuffer(pb, buf, 2);
}

void PackFixInt16(PackBuffer *pb, int16_t d){
    ubyte_t buf[3];
    buf[0] = 0xd1;
    buf[1] = ((ubyte_t *)&d)[1];
    buf[2] = ((ubyte_t *)&d)[0];
    PackAppendBuffer(pb, buf, 3);
}

void PackFixInt32(PackBuffer *pb, int32_t d){
    ubyte_t buf[5];
    buf[0] = 0xd2;
    buf[1] = ((ubyte_t *)&d)[3];
    buf[2] = ((ubyte_t *)&d)[2];
    buf[3] = ((ubyte_t *)&d)[1];
    buf[4] = ((ubyte_t *)&d)[0];
    PackAppendBuffer(pb, buf, 5);
}

void PackFixInt64(PackBuffer *pb, int64_t d){
    ubyte_t buf[9];
    buf[0] = 0xd3;
    buf[1] = ((ubyte_t *)&d)[7];
    buf[2] = ((ubyte_t *)&d)[6];
    buf[3] = ((ubyte_t *)&d)[5];
    buf[4] = ((ubyte_t *)&d)[4];
    buf[5] = ((ubyte_t *)&d)[3];
    buf[6] = ((ubyte_t *)&d)[2];
    buf[7] = ((ubyte_t *)&d)[1];
    buf[8] = ((ubyte_t *)&d)[0];
    PackAppendBuffer(pb, buf, 9);
}

void PackNil(PackBuffer *pb){
    static const ubyte_t d = 0xc0;
    PackAppendBuffer(pb, &d, 1);
}

void PackTrue(PackBuffer *pb){
    static const ubyte_t d = 0xc3;
    PackAppendBuffer(pb, &d, 1);
}

void PackFalse(PackBuffer *pb){
    static const ubyte_t d = 0xc2;
    PackAppendBuffer(pb, &d, 1);
}

void PackFloat(PackBuffer *pb, float d){
    ubyte_t buf[5];
    union {
        float f; uint32_t i;
    } mem;
    mem.f = d;
    buf[0] = 0xca;
    buf[1] = ((ubyte_t *)&mem.i)[3];
    buf[2] = ((ubyte_t *)&mem.i)[2];
    buf[3] = ((ubyte_t *)&mem.i)[1];
    buf[4] = ((ubyte_t *)&mem.i)[0];
    PackAppendBuffer(pb, buf, 5);
}

void PackDouble(PackBuffer *pb, double d){
    ubyte_t buf[9];
    union{
        double f; uint64_t i;
    } mem;
    mem.f = d;
    buf[0] = 0xcb;
    buf[1] = ((ubyte_t *)&mem.i)[7];
    buf[2] = ((ubyte_t *)&mem.i)[6];
    buf[3] = ((ubyte_t *)&mem.i)[5];
    buf[4] = ((ubyte_t *)&mem.i)[4];
    buf[5] = ((ubyte_t *)&mem.i)[3];
    buf[6] = ((ubyte_t *)&mem.i)[2];
    buf[7] = ((ubyte_t *)&mem.i)[1];
    buf[8] = ((ubyte_t *)&mem.i)[0];
    PackAppendBuffer(pb, buf, 9);
}

void PackArray(PackBuffer *pb, size_t n){
    if(n < 16){
        ubyte_t d = 0x90 | (ubyte_t)n;
        PackAppendBuffer(pb, &TAKE8_8(d), 1);
    } else if(n < 65536){
        ubyte_t buf[3];
        buf[0] = 0xdc;
        buf[1] = ((ubyte_t *)&n)[1];
        buf[2] = ((ubyte_t *)&n)[0];
        PackAppendBuffer(pb, buf, 3);
    } else{
        ubyte_t buf[5];
        buf[0] = 0xdd;
        buf[1] = ((ubyte_t *)&n)[3];
        buf[2] = ((ubyte_t *)&n)[2];
        buf[3] = ((ubyte_t *)&n)[1];
        buf[4] = ((ubyte_t *)&n)[0];
        PackAppendBuffer(pb, buf, 5);
    }
}

void PackMap(PackBuffer *pb, size_t n){
    if(n < 16){
        ubyte_t d = 0x80 | (ubyte_t)n;
        PackAppendBuffer(pb, &TAKE8_8(d), 1);
    } else if(n < 65536){
        ubyte_t buf[3];
        buf[0] = 0xde;
        buf[1] = ((ubyte_t *)&n)[1];
        buf[2] = ((ubyte_t *)&n)[0];
        PackAppendBuffer(pb, buf, 3);
    } else{
        ubyte_t buf[5];
        buf[0] = 0xdf;
        buf[1] = ((ubyte_t *)&n)[3];
        buf[2] = ((ubyte_t *)&n)[2];
        buf[3] = ((ubyte_t *)&n)[1];
        buf[4] = ((ubyte_t *)&n)[0];
        PackAppendBuffer(pb, buf, 5);
    }
}

void PackBin(PackBuffer *pb, size_t len){
    if(len < 256){
        ubyte_t buf[2];
        buf[0] = 0xc4;
        buf[1] = (uint8_t)len;
        PackAppendBuffer(pb, buf, 3);
    } else if(len < 65536){
        ubyte_t buf[3];
        buf[0] = 0xc5;
        buf[1] = ((ubyte_t *)&len)[1];
        buf[2] = ((ubyte_t *)&len)[0];
        PackAppendBuffer(pb, buf, 3);
    } else{
        ubyte_t buf[5];
        buf[0] = 0xc6;
        buf[1] = ((ubyte_t *)&len)[3];
        buf[2] = ((ubyte_t *)&len)[2];
        buf[3] = ((ubyte_t *)&len)[1];
        buf[4] = ((ubyte_t *)&len)[0];
        PackAppendBuffer(pb, buf, 5);
    }
}

void PackBinBody(PackBuffer *pb, const void *body, size_t len){
    PackAppendBuffer(pb, (const ubyte_t *) body, len);
}

void PackExt(PackBuffer *pb, size_t len, int8_t type){/*{{{*/
    switch(len){
        case 1:{
            ubyte_t buf[2];
            buf[0] = 0xd4;
            buf[1] = type;
            PackAppendBuffer(pb, buf, 2);
        } break;
        case 2:{
            ubyte_t buf[2];
            buf[0] = 0xd5;
            buf[1] = type;
            PackAppendBuffer(pb, buf, 2);
        } break;
        case 4:{
            ubyte_t buf[2];
            buf[0] = 0xd6;
            buf[1] = type;
            PackAppendBuffer(pb, buf, 2);
        } break;
        case 8:{
            ubyte_t buf[2];
            buf[0] = 0xd7;
            buf[1] = type;
            PackAppendBuffer(pb, buf, 2);
        } break;
        case 16:{
            ubyte_t buf[2];
            buf[0] = 0xd8;
            buf[1] = type;
            PackAppendBuffer(pb, buf, 2);
        } break;
        default:
            if(len <256){
                ubyte_t buf[3];
                buf[0] = 0xc7;
                buf[1] = (ubyte_t)len;
                buf[2] = type;
                PackAppendBuffer(pb, buf, 3);
            } else if(len < 65536){
                ubyte_t buf[4];
                buf[0] = 0xc8;
                buf[1] = ((ubyte_t *)&len)[1];
                buf[2] = ((ubyte_t *)&len)[0];
                buf[3] = type;
                PackAppendBuffer(pb, buf, 4);
            } else{
                ubyte_t buf[6];
                buf[0] = 0xc9;
                buf[1] = ((ubyte_t *)&len)[3];
                buf[2] = ((ubyte_t *)&len)[2];
                buf[3] = ((ubyte_t *)&len)[1];
                buf[4] = ((ubyte_t *)&len)[0];
                buf[5] = type;
                PackAppendBuffer(pb, buf, 6);
            }
            break;
    }
}/*}}}*/

void PackExtBody(PackBuffer *pb, const void *body, size_t len){
    PackAppendBuffer(pb, (const ubyte_t *)body, len);
}


void PackMessage(PackBuffer *pb, Object *obj){/*{{{*/
    if(obj->isKey == TRUE){
        switch(obj->key_type){
            case OBJ_TYPE_STR:
                PackString(pb, obj->key_len);
                PackStringBody(pb, obj->key.str_val, obj->key_len);
                printf("str_val:%s\n", obj->key.str_val);
                break;
            case OBJ_TYPE_INT8:
                PackFixInt8(pb, obj->key.int8_val);
                printf("int8: %d\n", obj->key.int8_val);
                break;
            case OBJ_TYPE_INT16:
                PackFixInt16(pb, obj->key.int16_val);
                printf("int16: %d\n", obj->key.int16_val);
                break;
            case OBJ_TYPE_INT32:
                PackFixInt32(pb, obj->key.int32_val);
                printf("int32: %d\n", obj->key.int32_val);
                break;
            case OBJ_TYPE_INT64:
                PackFixInt64(pb, obj->key.int64_val);
                printf("int64: %ld\n", obj->key.int64_val);
                break;
            case OBJ_TYPE_UINT8:
                PackFixInt8_u(pb, obj->key.uint8_val);
                printf("uint8: %u\n", obj->key.uint8_val);
                break;
            case OBJ_TYPE_UINT16:
                PackFixInt16_u(pb, obj->key.uint16_val); 
                printf("uint16: %u\n", obj->key.uint16_val);
                break;
            case OBJ_TYPE_UINT32:
                PackFixInt32_u(pb, obj->key.uint32_val);
                printf("uint32: %u\n", obj->key.uint32_val);
                break;
            case OBJ_TYPE_UINT64:
                PackFixInt64_u(pb, obj->key.uint64_val);
                printf("uint64: %lu\n", obj->key.uint64_val);
                break;
            case OBJ_TYPE_POSITIVE_INT:
                PackFixNumPositive(pb, obj->key.uint8_val);
                printf("positive int: %u\n", obj->key.uint8_val);
                break;
            case OBJ_TYPE_NEGATIVE_INT:
                PackFixNumNegative(pb, obj->key.int8_val);
                printf("negative int: %d\n", obj->key.int8_val);
                break;
            default:
                break;
        }
    }
                                                  
    switch(obj->obj_type){
        case OBJ_TYPE_STR:
            PackString(pb, obj->obj_len);
            PackStringBody(pb, obj->value.str_val, obj->obj_len);
            printf("str_val:%s\n", obj->value.str_val);
            break;
        case OBJ_TYPE_NIL:
            PackNil(pb);
            printf("NULL\n");
            break;
        case OBJ_TYPE_TRUE:
            PackTrue(pb);
            printf("TRUE:%d\n", obj->value.bool_val);
            break;
        case OBJ_TYPE_FALSE:
            PackFalse(pb);
            printf("FALSE:%d\n", obj->value.bool_val);
            break;
        case OBJ_TYPE_BIN:
            PackBin(pb, obj->obj_len);
            PackBinBody(pb, &obj->value, obj->obj_len);
            printf("BIN: %s\n", obj->value.bin_val);
            break;
        case OBJ_TYPE_FLOAT:
            PackFloat(pb, obj->value.float_val);
            printf("float: %f\n", obj->value.float_val);
            break;
        case OBJ_TYPE_DOUBLE:
            PackDouble(pb, obj->value.double_val);
            printf("double: %lf\n", obj->value.double_val);
            break;
        case OBJ_TYPE_POSITIVE_INT:
            PackFixNumPositive(pb, obj->value.uint8_val);
            printf("positive int: %u\n", obj->value.uint8_val);
            break;
        case OBJ_TYPE_NEGATIVE_INT:
            PackFixNumNegative(pb, obj->value.int8_val);
            printf("negative int: %d\n", obj->value.int8_val);
            break;
        case OBJ_TYPE_INT8:
            PackFixInt8(pb, obj->value.int8_val);
            printf("int8: %d\n", obj->value.int8_val);
            break;
        case OBJ_TYPE_INT16:
            PackFixInt16(pb, obj->value.int16_val);
            printf("int16: %d\n", obj->value.int16_val);
            break;
        case OBJ_TYPE_INT32:
            PackFixInt32(pb, obj->value.int32_val);
            printf("int32: %d\n", obj->value.int32_val);
            break;
        case OBJ_TYPE_INT64:
            PackFixInt64(pb, obj->value.int64_val);
            printf("int64: %ld\n", obj->value.int64_val);
            break;
        case OBJ_TYPE_UINT8:
            PackFixInt8_u(pb, obj->value.uint8_val);
            printf("uint8: %u\n", obj->value.uint8_val);
            break;
        case OBJ_TYPE_UINT16:
            PackFixInt16_u(pb, obj->value.uint16_val); 
            printf("uint16: %u\n", obj->value.uint16_val);
            break;
        case OBJ_TYPE_UINT32:
            PackFixInt32_u(pb, obj->value.uint32_val);
            printf("uint32: %u\n", obj->value.uint32_val);
            break;
        case OBJ_TYPE_UINT64:
            PackFixInt64_u(pb, obj->value.uint64_val);
            printf("uint64: %lu\n", obj->value.uint64_val);
            break;
        case OBJ_TYPE_ARRAY:
            PackArray(pb, obj->obj_len);
            printf("Array: %d\n", obj->obj_len);
            break;
        case OBJ_TYPE_MAP:
            PackMap(pb, obj->obj_len);
            printf("Map: %d\n", obj->obj_len);
            break;
        case OBJ_TYPE_EXT:
            PackExt(pb, obj->obj_len, 0x00);
            printf("EXT: %d\n", obj->obj_len);
            break;
        default:
            break;
    }

    if(obj->child != NULL){
        PackMessage(pb, obj->child);
    }

    if(obj->next != NULL){
        PackMessage(pb, obj->next);
    }
        
}/*}}}*/

PackBuffer *MessagePacker(Object *obj){
        /* creates buffer and serializer instance. */
        PackBuffer *pb = NewPackBuffer(); 
        PackMessage(pb, obj);

        return pb;
}

void print(const ubyte_t *buf, unsigned int len){
    size_t i = 0;
    for(; i < len; ++i)
       printf("0x%02x ", 0xff & buf[i]);
    printf("\n");
}

//int main(){
//    ubyte_t str[] = {0xD9, 0x23, 0x61, 0x62, 0x63, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6D, 0x6D, 0x6D, 0x6D, 0x6D, 0x73, 0x73, 0x73, 0x73, 0x73, 0x73, 0x73, 0x73, 0x73,  0x73, 0x73, 0x73, 0x73, 0x73, 0x73, 0x73, 0x73, 0x73};
//    ubyte_t array[] = {0x93, 0x01, 0x02, 0x03};
//    ubyte_t float_val[] = {0xCA, 0x43, 0x5C, 0x00, 0x00};
//    ubyte_t map[] = {0x82, 0x02, 0xA5, 0x68, 0x65, 0x6C, 0x6C, 0x6F, 0x03, 0xA5, 0x77, 0x6F, 0x72, 0x6C, 0x64};
//    
//    //char *ret_str = parseString(str, &off);
//    //printf("%s\n", ret_str);
//    Context *ctx = (Context *)calloc(1, sizeof(Context));
//    ctx->root = NewObject(); 
//    ctx->node = ctx->root;
//    //ctx->buf = array;
//    //ctx->buf = float_val;
//    //ctx->buf = ext;
//    ctx->buf = map;
//    printf("==============original===================\n");
//    print((const ubyte_t*)map, (unsigned int )15);
//    printf("==============building===================\n");
//    ParseDispatcher(ctx);
//    printf("==============visit======================\n");
//    PackBuffer *pb = MessagePacker(ctx->root);
//    printf("==============result======================\n");
//    print(pb->buffer, pb->off);
//
//    //ctx->buf = float_val;
//
//}
