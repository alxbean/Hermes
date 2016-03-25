/*************************************************************************
    > File Name: msghulu_define.h
    > Author: shuaixiang
    > Mail: shuaixiang@yuewen.com
    > Created Time: Mon 07 Mar 2016 08:05:25 AM UTC
 ************************************************************************/
#include <stdint.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif
    typedef unsigned char ubyte_t ;
    typedef unsigned char byte_t ;
    typedef char *string_t;
    typedef enum{
        TRUE = 1,
        FALSE = 0
    }bool_t;

    static union{
        char a[4];
        unsigned long ul;
    }endian={{'L','?', '?', 'B'}};

    #define ENDIAN ((char)endian.ul)

#ifdef __cplusplus
}
#endif
