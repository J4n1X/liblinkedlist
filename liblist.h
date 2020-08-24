#ifndef liblist_h__
#define liblist_h__
#include <stdint.h>

typedef struct _list_item_s{
    void *val;
    size_t size;
    struct _list_item_s *next;
}list_item;

typedef struct _list_s{
    list_item *first;
    list_item *last;
    size_t size;
    list_item **index;
    uint8_t index_stale;
} list;

extern list_item *list_get_final(list_item *intlist);
extern list_item *list_get_item(list *item_list, size_t pos);

extern list_item *list_create_item(void *item_value, size_t node_size);
extern list_item *list_prealloc(size_t item_count, size_t node_size);
extern void list_set_item(list_item *node, void *node_value, size_t node_size);
extern void list_append_item(list *item_list, void *append_value, size_t node_size);
extern void list_insert_item(list *item_list, size_t pos, void *insert_value, size_t node_size);
extern void list_remove_item(list *item_list, size_t pos);
extern void list_build_index(list *item_list);
extern list *list_create(size_t list_size, size_t node_size);
extern void list_free(list *item_list);
#endif // ifndef liblist_h__
