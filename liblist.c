#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "liblist.h"

// use for testing only
#define V_PRINTF(str, ...) if(VERBOSE == 1) printf((str), __VA_ARGS__)
#define VERBOSE 0

//
// GETTERS
//
#pragma region getters
list_item *list_get_final(list_item *intlist){
    list_item *cur_item = intlist;
    while(cur_item->next != NULL)
        cur_item = cur_item->next;
    return cur_item;
}

list_item *list_get_item(list *item_list, size_t pos){
    if(pos > item_list->size)
        return NULL;
    
    list_item *cur_item = item_list->first;
    for(int i = 0; i < pos ; i++)
        cur_item = cur_item->next;
    return cur_item;
}
#pragma endregion getters

//
// SETTERS
//
#pragma region setters
// creates list item with next = NULL and val = 0
list_item *list_create_item(void *item_value){
    list_item *new_item;
    new_item = malloc(sizeof(list));
    new_item->val = item_value;
    new_item->next = NULL;
    return new_item;
}

// this is faster than appending one by one, as we just move through very quickly
list_item *list_prealloc(size_t item_count, size_t node_size){
    list_item *initial_item = list_create_item(NULL);
    //list_item **ret_list = &initial_item;
    list_item *cur_item = initial_item;

    for(size_t i = item_count - 1; i > 0; i--){
        cur_item->next = list_create_item(0);
        cur_item = cur_item->next;
#if VERBOSE == 1
        if(!(i % 50))
            printf("Items remaining: %lu of %lu\n",i,item_count);
#endif
    }
    return initial_item;
    //return *ret_list;
}

void list_append_item(list *item_list, void *append_value){
    item_list->last->next = list_create_item(malloc(item_list->node_size));
    item_list->last = item_list->last->next;
    // copy so the user can pass a pointer of a variable or allocated space
    memcpy(item_list->last->val,append_value,item_list->node_size);
    item_list->size++;
    item_list->index_stale = 1;
}

void list_insert_item(list *item_list, size_t pos, void *insert_value){
    list_item *cur_item;
    list_item *new_item = list_create_item(malloc(item_list->node_size));
    memcpy(new_item->val,insert_value,item_list->node_size);

    if(pos > 0){
        // NULL is returned if the object is out of range
        if((cur_item = list_get_item(item_list,pos)) == NULL)
            return;
        list_item *prev_item = list_get_item(item_list,pos - 1);
        prev_item->next = new_item;
    }
    else{
        if((cur_item = item_list->first) == NULL)
            return;
        item_list->first = new_item;
    }
    new_item->next = cur_item;
    
    item_list->size++;
    item_list->index_stale = 1;
}

// removes the item at the designated pos
void list_remove_item(list *item_list, size_t pos){
    list_item *cur_item;
    if(pos > 0){
        // NULL is returned if the object is out of range
        if((cur_item = list_get_item(item_list,pos)) == NULL)
            return;
        list_item *prev_item = list_get_item(item_list,pos - 1);
        prev_item->next = cur_item->next;
    }
    else{
        if((cur_item = item_list->first) == NULL)
            return;
        item_list->first = item_list->first->next;
    }
    free(cur_item->val);
    free(cur_item);
    item_list->size -= 1;
    item_list->index_stale = 1;
} 

// create an array of pointers pointing to every item in a list
void list_build_index(list *item_list){
    // if we rebuild, the old index must be modified
    if(item_list->index != NULL)
        item_list->index = realloc(item_list->index,sizeof(list_item*) * item_list->size);
    else
        item_list->index = malloc(sizeof(list_item*) * item_list -> size);
    list_item *cur_item = item_list->first;
    for(int i = 0; i < item_list->size; i++){
        item_list->index[i] = cur_item;
        cur_item = cur_item->next;
        V_PRINTF("Items indexed: %i of %i\r",i+1,item_list->size);
    }
    V_PRINTF("%s","\n");
    item_list->index_stale = 0;
} 

list *list_create(size_t list_size, size_t node_size){
    list *ret_list = malloc(sizeof(list));
    ret_list->first = list_prealloc(list_size,node_size);
    ret_list->last = list_get_final(ret_list->first);
    ret_list->size = list_size;
    ret_list->node_size =  node_size;
    // sets index and index_stale
    list_build_index(ret_list);
    return ret_list;
} 

// clears the entire list
void list_free(list *item_list){
    list_item *cur_item;
    int i = 1;
    while((cur_item = item_list->first) != NULL){
        V_PRINTF("Freeing item %i of %i\r", i++, item_list->size);
        item_list->first = item_list->first->next;
        free(cur_item->val);
        free(cur_item);
    } 
    V_PRINTF("%s","\n");
    // clean up everything but node size
    item_list->first = NULL;
    item_list->last = NULL;
    item_list->size = 0;
    if(item_list->index != NULL)
        free(item_list->index);
    item_list->index = NULL;
    item_list->index_stale = 0;
} 
#pragma endregion setters