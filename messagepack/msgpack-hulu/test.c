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

double average(int count, ...){
    va_list ap;
    int j;
    double tot = 0;
    va_start(ap, count);
    for(j=0; j<count; j++){
        tot += va_arg(ap, double);
    }

    va_end(ap);

    return tot;
}

int main(){
    double k = average(3, 1.1, 2.2, 3.3);
    printf("%f\n", k);
    return 0;
}
