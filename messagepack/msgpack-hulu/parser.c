/*************************************************************************
    > File Name: parse_msg.c
    > Author: shuaixiang
    > Mail: shuaixiang@yuewen.com
    > Created Time: Fri 11 Mar 2016 03:24:11 AM UTC
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned char ubyte_t ;

char *parseString(ubyte_t *buf, int *off){
    ubyte_t head = *buf & 0xFF;
    char *str = NULL;
    int len = 0;

    if ((head & 0xE0) == 0xA0){
        len = head &0x1F;
        printf("len: %d\n", len);
        str = (char *) malloc(sizeof(char)*len);
        memcpy(str, (buf + 1), len);
        *off += (len + 1);
        return str;
    }
    
    switch(head){
        case 0xD9: 
            len = *(buf+1);
            printf("len: %d\n", len);
            str = (char *) malloc(sizeof(char)*len);
            memcpy(str, (buf + 2), len);
            *off += (len + 1);
            return str;
        case 0xDA:
            len = (*(buf+1)<<8) + *(buf+2);
            printf("len: %d\n", len);
            str = (char *) malloc(sizeof(char)*len);
            memcpy(str, (buf+3), len);
            *off += (len + 1);
            return str;
        case 0xDB:
            len = (*(buf + 1)<<24) + (*(buf + 2)<<16) + (*(buf + 3)<<8) + *(buf + 4);
            printf("len: %d\n", len);
            str = (char *) malloc(sizeof(char)*len);
            memcpy(str, (buf+5), len);
            *off += (len+ 1);
            return str;
    }

    return str;
}

int parseBool(ubyte_t *buf, int *off){
    ubyte_t head = *buf;
    *off +=  1;
    if(head == 0xC2)
        return 0;
    else if(head == 0xC3)
        return 1;
    else
        return -1;
}

void *parseNil(ubyte_t *buf, int *off){
    ubyte_t head = *buf;
    *off += 1;
    if(head == 0xC0)
        return NULL;
    return NULL;
}

int parseInt(ubyte_t *buf, int *off){/*{{{*/
    ubyte_t head = *buf & 0xFF;
    unsigned int uval_8 = 0, uval_16 = 0, uval_32 = 0;
    unsigned long long uval_64 = 0;
    signed int val_8 = 0, val_16 = 0, val_32 = 0;
    long long val_64 = 0;
    unsigned long long tmp = 0;
    int i = 0;
    
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
        case 0xCC:
            uval_8 = (unsigned int) *(buf + 1);
            printf("val: %u\n", uval_8);
            *off += 2;
            return uval_8;
            
        case 0xCD:
            uval_16 = (unsigned int)(*(buf + 1) << 8) + *(buf + 2);
            printf("val: %u\n", uval_16);
            *off += 3;
            return uval_16;
            
        case 0xCE:
            uval_32 = (unsigned int)((*(buf + 1) << 24) + (*(buf + 2) << 16) + (*(buf + 3) << 8) + *(buf + 4));
            printf("val: %u\n", uval_32);
            *off += 5;
            return uval_32;

        case 0xCF:
            tmp = *(buf + 1);
            for(i = 0; i < 8; i++){
                tmp = *(buf + 8 - i );
                uval_64 += tmp << (i * 8);
            }
            printf("val: %llu\n", uval_64);
            *off += 9;
            return uval_64;

        case 0xD0:
            val_8 = (int) *(buf + 1);
            printf("val: %d\n", uval_8);
            *off += 2;
            return uval_8;

        case 0xD1:
            val_16 = (int) ((*(buf + 1) << 8) + *(buf + 2));
            printf("val: %d\n", val_16);
            *off += 3;
            return val_16;

        case 0xD2:
            val_32 = (int) ((*(buf + 1) << 24) + (*(buf + 2) << 16) + (*(buf + 3) << 8) + *(buf + 4));
            printf("val: %u\n", val_32);
            *off += 5;
            return val_32;

        case 0xD3:
            tmp = *(buf + 1);
            for(i = 0; i < 8; i++){
                tmp = *(buf + 8 - i );
                val_64 += tmp << (i * 8);
            }
            printf("val: %llu\n", val_64);
            *off += 9;
            return val_64;
    }

    return 0;
}/*}}}*/

float parseFloat(ubyte_t *buf, int *off){
    ubyte_t head = *buf;
    union{
        float float_tmp;
        ubyte_t float_buf[4]; 
        double double_tmp;
        ubyte_t double_buf[8];
    } float_union;

    if(head == 0xCA){
        int i = 0;
        for(i = 0; i < 4; i++){
            float_union.float_buf[i] = *(buf + 4 - i);  
        }
        *off += 5;
        return float_union.float_tmp;
    }
    if(head == 0xCB){
        int i  = 0;
        for(i = 1; i<=8; i++){
            float_union.double_buf[i] = *(buf + 8 - i);
        }
        *off += 9;
        return float_union.double_tmp;
    }

    return 0.0; 
}

int main(){
    ubyte_t ext[] = {0xC7, 0x11, 0x00, 0xA4, 0x6E, 0x61, 0x6D, 0x65, 0xA6, 0xE5, 0x91, 0xB5, 0xE5, 0x91, 0xB5, 0xA3, 0x61, 0x67, 0x65, 0x0A};
    ubyte_t str[] = {0xD9, 0x29, 0x61, 0x62, 0x63, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6D, 0x6D, 0x6D, 0x6D, 0x6D, 0x73, 0x73, 0x73, 0x73, 0x73, 0x73, 0x73, 0x73, 0x73,  0x73, 0x73, 0x73, 0x73, 0x73, 0x73, 0x73, 0x73, 0x73};
    
    int off = 0;
    //char *ret_str = parseString(str, &off);
    //printf("%s\n", ret_str);
    
    ubyte_t float_val[] = {0xCA, 0x43, 0x5C, 0x00, 0x00};
    printf("%f\n", parseFloat(float_val, &off));
}

