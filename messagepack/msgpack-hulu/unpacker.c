/*************************************************************************
    > File Name: unpacker.c
    > Author: shuaixiang
    > Mail: shuaixiang@yuewen.com
    > Created Time: Mon 07 Mar 2016 07:23:15 AM UTC
 ************************************************************************/

#include <stdio.h>
#include "parse_msg.h"

 struct Object{
     char *buffer;
     int offset;
     int len;
 };

int which(char *head){
    if ( (*head & 0x80) == 0){
        printf("positive fixint\n");
        return 1;
    }
    if( (*head & 0xE0) == 0xE0){
        printf("negative fixint\n");
        return 1;
    }
    if( (*head & 0xE0) == 0xA0){
        printf("fixRaw\n");
        return 1;
    }
    if( (*head & 0xF0) == 0x90){
        printf("fixarray\n");
        return 1;
    }
    if( (*head & 0xf0) == 0x80){
        printf("FixMap\n");
        return 1;
    }

    switch(*head & 0xFF){
        case 0xC0:
            printf("NIL\n");
            return 1;
        case 0xC2:
            printf("boolean false\n");
            return 1;
        case 0xC3:
            printf("boolean true\n");
            return 1; 
        case 0xCA:
            printf("float\n");
            return 1;
        case 0xCB:
            printf("DOUBLE\n");
            return 1;
        case 0xCC:
            printf("unsigned int 8\n");
            return 1;
        case 0xCD:
            printf("unsigned int 16\n");
            return 1;
        case 0xCE:
            printf("unsigned int 32\n");
            return 1;
        case 0xCF:
            printf("unsigned int 64\n"); 
            return 1;
        case 0xD0:
            printf("signed int 8\n");
            return 1;
        case 0xD1:
            printf("signed int 16\n");
            return 1;
        case 0xD2:
            printf("signed int 32\n");
            return 1;
        case 0xD3:
            printf("signed int 64\n");
            return 1;
        case 0xC4:
            printf("bin 8\n");
            return 1; 
        case 0xC5:
            printf("bin 16\n");
            return 1;
        case 0xC6:
            printf("bin 32\n");
            return 1;
        case 0xD9:
            printf("str8\n");
            return 1;
        case 0xDA:
            printf("raw 16\n");
            return 1;
        case 0xDB:
            printf("raw 32\n");
            return 1;
        case 0xDC:
            printf("array 16\n");
            return 1;
        case 0xDD:
            printf("array 32\n");
            return 1;
        case 0xDE:
            printf("map 16\n");
            return 1;
        case 0xDF:
            printf("map 32\n");
            return 1;
        default:
            printf("not found\n");
            return 0;
    }

}

void unSerializer(char *buffer){
    if(NULL == buffer){
        printf("buffer is null~!\n");
        return;
    }

    which(buffer);
}

//int main(){
//
//}
