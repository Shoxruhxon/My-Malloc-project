#ifndef MY_MALLOC_H
#define MY_MALLOC_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <sys/mman.h>   
typedef struct Encipher_str
{
    size_t length_s;
    bool absolve;
    void* point_ret;
} Encipher_str;


void fill_wnull(void* ray1, int g_sz){
   memset( ray1, 0, g_sz); 
}
#endif