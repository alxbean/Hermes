/*************************************************************************
    > File Name: test.c
    > Author: shuaixiang
    > Mail: shuaixiang@yuewen.com
    > Created Time: Mon 14 Mar 2016 08:37:23 AM UTC
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdarg.h>
#include "include/packTree.h"
#include "include/unpacker.h"

int main(){
//----------------------packTree----------------------
TreeCTX *ctx = InitPackTree();
char a[100] = "helloworld";
char a1[100] = "hello";
char a2[100] = "world";
PackTree_String(ctx, a, strlen(a)); 

PackTree_Int(ctx, 1); 

PackTree_ArrayBegin(ctx);
PackTree_Int(ctx, 2);
PackTree_Int(ctx, 3);
PackTree_Int(ctx, 3);
PackTree_ArrayEnd(ctx);

PackTree_MapBegin(ctx);
PackMap_String_Int(ctx, a1, strlen(a),  1);
PackMap_String_Int(ctx, a2, strlen(a),  2);
PackTree_MapEnd(ctx);

char b[100] = "end";
PackTree_String(ctx, b, strlen(b)); 

printf("\n================TREE==================\n");
printTree(ctx->root, 0);
printf("\n================JSON==================\n");
printJSON(ctx->root);
printf("\n================BUILD==================\n");
PackBuffer *pb = MessagePacker(ctx->root);
print(pb->buffer, pb->off);

//----------------------packer------------------------    /*{{{*/
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

    //ctx->buf = float_val;/*}}}*/

//----------------------unpacker---------------------------/*{{{*/
//    ubyte_t ext[] = {0xC7, 0x11, 0x00, 0xA4, 0x6E, 0x61, 0x6D, 0x65, 0xA6, 0xE5, 0x91, 0xB5, 0xE5, 0x91, 0xB5, 0xA3, 0x61, 0x67, 0x65, 0x0A};
//    ubyte_t str[] = {0xD9, 0x29, 0x61, 0x62, 0x63, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6D, 0x6D, 0x6D, 0x6D, 0x6D, 0x73, 0x73, 0x73, 0x73, 0x73, 0x73, 0x73, 0x73, 0x73,  0x73, 0x73, 0x73, 0x73, 0x73, 0x73, 0x73, 0x73, 0x73};
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
//    ctx->buf = ext;
//    ParseDispatcher(ctx);
//
//    //ctx->buf = float_val;
//    //printf("%f\n", ParseFloat(ctx));/*}}}*/

    return 0;
}
