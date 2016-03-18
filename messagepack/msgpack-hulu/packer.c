/*************************************************************************
    > File Name: packer.c
    > Author: shuaixiang
    > Mail: shuaixiang@yuewen.com
    > Created Time: Mon 07 Mar 2016 07:23:11 AM UTC
 ************************************************************************/

#include <stdio.h>
#include <msgpack.h>
#include "parser.c"

void VisitMessageTree(Object *obj){/*{{{*/
    if(obj->name != NULL)
                printf("name:%s ", obj->name);
    switch(obj->type){
        case MSGPACK_OBJECT_STR:
            printf("str_val:%s\n", obj->str_val);
            break;
        case MSGPACK_OBJECT_NIL:
            printf("NULL");
            break;
        case MSGPACK_OBJECT_BOOLEAN:
            printf("bool: %d\n", obj->int_val);
            break;
        case MSGPACK_OBJECT_POSITIVE_INTEGER:
            printf("bool: %d\n", obj->int_val);
            break;
        case MSGPACK_OBJECT_NEGATIVE_INTEGER:
            printf("bool: %d\n", obj->int_val);
            break;
        case MSGPACK_OBJECT_FLOAT:
            printf("float: %f\n", obj->float_val);
            break;
        case MSGPACK_OBJECT_BIN:
            printf("bin: %s\n", obj->bin_val);
            break;
        default:
            break;
    }

    if(obj->child != NULL){
        switch(obj->type){
            case MSGPACK_OBJECT_ARRAY:
                printf("Array:\n");
                break;
            case MSGPACK_OBJECT_MAP:
                printf("Map:\n");
                break;
            case MSGPACK_OBJECT_EXT:
                printf("EXT:\n");
                break;
            default:
                break;
        }
        VisitMessageTree(obj->child);
    }

    if(obj->next != NULL){
        VisitMessageTree(obj->next);
    }
        
}/*}}}*/

void PackMessage(msgpack_packer *pk, Object* obj){/*{{{*/
    if(obj->name != NULL){
            msgpack_pack_nil(pk);
            printf("name:%s ", obj->name);
    }
    switch(obj->type){
        case MSGPACK_OBJECT_STR:
            printf("str_val:%s\n", obj->str_val);
            break;
        case MSGPACK_OBJECT_NIL:
            printf("NULL");
            break;
        case MSGPACK_OBJECT_BOOLEAN:
            printf("bool: %d\n", obj->int_val);
            break;
        case MSGPACK_OBJECT_POSITIVE_INTEGER:
            printf("bool: %d\n", obj->int_val);
            break;
        case MSGPACK_OBJECT_NEGATIVE_INTEGER:
            printf("bool: %d\n", obj->int_val);
            break;
        case MSGPACK_OBJECT_FLOAT:
            printf("float: %f\n", obj->float_val);
            break;
        case MSGPACK_OBJECT_BIN:
            printf("bin: %s\n", obj->bin_val);
            break;
        default:
            break;
    }

    if(obj->child != NULL){
        switch(obj->type){
            case MSGPACK_OBJECT_ARRAY:
                printf("Array:\n");
                break;
            case MSGPACK_OBJECT_MAP:
                printf("Map:\n");
                break;
            case MSGPACK_OBJECT_EXT:
                printf("EXT:\n");
                break;
            default:
                break;
        }
        VisitMessageTree(obj->child);
    }

    if(obj->next != NULL){
        VisitMessageTree(obj->next);
    }

}/*}}}*/

char const * MessagePacker(Object *obj){
        /* creates buffer and serializer instance. */
        msgpack_sbuffer* buffer = msgpack_sbuffer_new();
        msgpack_packer* pk = msgpack_packer_new(buffer, msgpack_sbuffer_write);
        PackMessage(pk, obj);
        return buffer->data;
}

int main(){
    ubyte_t str[] = {0xD9, 0x29, 0x61, 0x62, 0x63, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6D, 0x6D, 0x6D, 0x6D, 0x6D, 0x73, 0x73, 0x73, 0x73, 0x73, 0x73, 0x73, 0x73, 0x73,  0x73, 0x73, 0x73, 0x73, 0x73, 0x73, 0x73, 0x73, 0x73};
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
    ctx->buf = map;
    printf("==============building===================\n");
    ParseDispatcher(ctx);
    printf("==============visit======================\n");
    VisitMessageTree(ctx->root);

    //ctx->buf = float_val;

}
