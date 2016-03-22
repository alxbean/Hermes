/*************************************************************************
    > File Name: test.c
    > Author: shuaixiang
    > Mail: shuaixiang@yuewen.com
    > Created Time: Mon 14 Mar 2016 08:37:23 AM UTC
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef unsigned char uint8_t;

typedef struct {
    uint8_t size;
    const char *ptr;
} msgpack_object_str;


typedef union{
    int a;
    msgpack_object_str str; 
} msgpack_object_union;

typedef struct {
    uint8_t TYPE;
    msgpack_object_union via;
} msgpack_object;

char * k(char * b){
    printf("%s\n",b);
    char a[] = {'1', '2', '3'};
    printf("%s\n",a);
    return b;
}


int main(){
    uint8_t test[] = {0xAA, 0x68, 0x65, 0x6C, 0x6C, 0x6F, 0x77, 0x6F, 0x72, 0x6C, 0x64};

    char a[] = {'1', '2', '3'};

    unsigned char t[] = {0x07, 0x5B, 0xCD, 0x15}; 
    printf("%d ", (int32_t)t);
}
