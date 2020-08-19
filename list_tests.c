#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "liblist.h"

#ifdef VERBOSE
#undef VERBOSE
#endif
#define VERBOSE 1

int main(int argc, char *argv[]){
    if(argc != 2){
        puts("Argument error!");
        return 1;
    }
    char *errstr;
    uint32_t cycles = strtoul(argv[1], &errstr, 10);
    if(errstr == NULL ||  cycles > 1000000){
        puts("Argument error! Conversion failed or number too large for Arg 1. Exiting...");
        exit(2);
    } 
    uint32_t node_size = 4; 
    if(errstr != NULL){
        list *main_list = list_create(cycles,node_size);
        list_item *cur_item = main_list->first;
        for(int i = 0; i < main_list->size; i++){
            cur_item->val = malloc(main_list->node_size);
            memcpy(cur_item->val,&i,main_list->node_size);
            cur_item = cur_item->next;
        }
        // this will allow for faster access later, but takes long to create
        list_remove_item(main_list,0);
        list_build_index(main_list);

        #if VERBOSE == 1 
        for(int i = 0; i <main_list->size; i++)
            printf("%i ", *(int*)main_list->index[i]->val );
        printf("\n");
        #endif

        list_free(main_list);
        return 0;
    } else{
        puts("Argument error! Conversion failed for Arg 2. Exiting...");
        return 2;
    }
}
