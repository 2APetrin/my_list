#include "list_header.h"

int list_ctor_(my_list * list, struct var_info creation_params)
{
    assert(list);
    assert(creation_params.file);
    assert(creation_params.func);
    assert(creation_params.name);

    list->info = creation_params;
    list->data = (struct list_elem *) calloc (LIST_MIN_LEN, sizeof(struct list_elem));
    list->head = 0;
    list->tail = 0;

    for (unsigned i = 1; i < LIST_MIN_LEN; i++)
    {
        list->data[i].next = -1;
        list->data[i].val  = POISON;
    }

    return 0;
}