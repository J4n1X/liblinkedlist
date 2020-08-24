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
        for(int i = 0; i < cycles; i++)
            list_set_item(list_get_item(main_list,i),&i,sizeof(i));
        // test adding and removing items
        list_remove_item(main_list,0);
        int insert_val = 420;
        list_insert_item(main_list,0, &insert_val, sizeof(insert_val));
        list_insert_item(main_list,5,&insert_val, sizeof(insert_val));
        list_set_item(list_get_item(main_list,20),&insert_val, node_size);
        // this will allow for faster access later, but takes long to create
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
