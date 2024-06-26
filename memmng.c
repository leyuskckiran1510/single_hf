#ifdef MAIN
    #define IMPLE_MEMMNG
    
#endif

#ifndef __MEMMNG__
    #include <stdbool.h>
    #include <stdint.h>
    #include <stdlib.h>

        #define __MEMMNG__

        static uint __DEFER = 0;
        #define calloc(x,y) track(calloc((x),(y)));
        #define malloc(x) track(malloc((x)))
        #define reallocarray(x,y,z) track(reallocarray(detrack((x)),(y),(z)))
        #define realloc(x,y) track(realloc(detrack((x)),(y)))
        #define MAX_MALLOCS 100
        #define defer __DEFER+=1;
        #define return {free_recent_n(__DEFER);__DEFER=0;}return
    
        #define print(...) printf(__VA_ARGS__);

    void *track(void *);
    void* detrack(void *);
    void clear();
    void free_recent();
    void free_recent_n(uint x);
    void magic_init();




#ifdef IMPLE_MEMMNG
#include <string.h>
#include <stdio.h>
#include <errno.h>
static void* __MALLOCS[MAX_MALLOCS] = {0};
static uint __MALLOC_PT = 0;

void* track(void *ptr){
    if (ptr == NULL) {
        fprintf(stderr, "Error Allocating memeory %s", strerror(errno));
        exit(errno);
      } else {
        __MALLOCS[__MALLOC_PT++] =ptr;
        return ptr; 
      }
}

void repack_mallocs(uint i){
    for(uint j=i;i<__MALLOC_PT-1;j++){
        __MALLOCS[j]=__MALLOCS[j+1];
    }
    __MALLOC_PT--;
}

void* detrack(void *ptr){
    for (uint i = 0; i < __MALLOC_PT; i++)
    {
       if(__MALLOCS[i]==ptr){
            __MALLOCS[i]=NULL;
            repack_mallocs(i);
            return ptr;
       }
    }
    return ptr;
}


void clear(){
    for (uint i = 0; i < __MALLOC_PT; ++i){
        if(__MALLOCS[i]!=NULL){
            free(__MALLOCS[i]);
            __MALLOCS[i]= NULL;
        }
    }
}
void free_recent(){
    if(__MALLOC_PT<=0){
        return;
    }
    __MALLOC_PT-=1;
    if(__MALLOCS[__MALLOC_PT]!=NULL){
        free(__MALLOCS[__MALLOC_PT]);
    }
    __MALLOCS[__MALLOC_PT] = NULL;
}

void free_recent_n(uint x){
    for (uint i = 0; i < x; ++i)
        free_recent();
}

void magic_init(){
    atexit(clear);
    for (int i=0;i<MAX_MALLOCS;i++)
        __MALLOCS[i] = NULL;
}
#endif
#endif



#ifdef MAIN 
/*

sample case of how to use memmng

*/

char * test(){
    char *big_array = malloc(sizeof(100000));
    defer; //to deallocate the recently allocated memeory
    return big_array ;
}


int main(){
    magic_init(); // deallocate all the allocated memory
                    // this is not much necessary in morden operating system
                    // as all morden OSes does this automaitcally when program
                   // goes out of context
    char * c =test();
    c[1000]='p';
    printf("%s\n",c);
}



#endif