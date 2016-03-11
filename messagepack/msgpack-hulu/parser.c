/*************************************************************************
    > File Name: parse_msg.c
    > Author: shuaixiang
    > Mail: shuaixiang@yuewen.com
    > Created Time: Fri 11 Mar 2016 03:24:11 AM UTC
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#include "parse_msg.h"
#define _byte unsigned char

char *parseString(_byte *buf, int *off){
    _byte head = buf[0];        
    char *str = NULL;
    int len = 0;

    if ((head & 0xE0) == 0xA0){
        len = head &0x1F;
        printf("len: %d\n", len);
        str = (char *) malloc(sizeof(char)*len);
        memcpy(str, (buf + 1), len);
        off += len + 1;
        return str;
    }
    
    switch(head & 0xFF){
        case 0xD9: 
            len = *(buf+1);
            printf("len: %d\n", len);
            str = (char *) malloc(sizeof(char)*len);
            memcpy(str, (buf + 2), len);
            off += len + 1;
            return str;
        case 0xDA:
            len = (*(buf+1)<<8) + *(buf+2);
            printf("len: %d\n", len);
            str = (char *) malloc(sizeof(char)*len);
            memcpy(str, (buf+3), len);
            off += len + 1;
            return str;
        case 0xDB:
            len = (*(buf + 1)<<24) + (*(buf + 2)<<16) + (*(buf + 3)<<8) + *(buf + 4);
            printf("len: %d\n", len);
            str = (char *) malloc(sizeof(char)*len);
            memcpy(str, (buf+5), len);
            off += len+ 1;
            return str;
    }

    return str;
}

int parseBool(_byte *buf, int *off){
    _byte head = *buf;
    *off +=  1;
    if(head == 0xC2)
        return 0;
    if(head == 0xC3)
        return 1;

    return -1; 
}

void *parseNil(_byte *buf, int *off){
    _byte head = *buf;
    *off += 1;
    if(head == 0xC0)
        return NULL;
    return NULL;
}

int parseInt(_byte *buf, int *off){
    char head = *buf;
    int len = 0;
    
    if( (head & 0x80) == 0){
       int val = (*buf) & 0x7F; 
       *off += 1;
       return val;
    }

    if( (head & 0xE0) == 0xE0){
        int val = (*buf) & 0x1F;
        *off += 1;
        return -val;
    }

    switch(head){
        case(0xCC):
            len = *(buf_+ 1);
        case(0xCD):
        case(0xCE):
        case(0xCF):
        case(0xD0):
        case(0xD1):
        case(0xD2):
        case(0xD3):
    }
}

int main(){
    _byte ext[] = {0xC7, 0x11, 0x00, 0xA4, 0x6E, 0x61, 0x6D, 0x65, 0xA6, 0xE5, 0x91, 0xB5, 0xE5, 0x91, 0xB5, 0xA3, 0x61, 0x67, 0x65, 0x0A};
    _byte str[] = {0xD9, 0x29, 0x61, 0x62, 0x63, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6D, 0x6D, 0x6D, 0x6D, 0x6D, 0x73, 0x73, 0x73, 0x73, 0x73, 0x73, 0x73, 0x73, 0x73,  0x73, 0x73, 0x73, 0x73, 0x73, 0x73, 0x73, 0x73, 0x73};
    
    int off = 0;
    char *ret_str = parseString(str, &off);
    printf("%s\n", ret_str);
}

