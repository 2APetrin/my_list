#include "list_header.h"

int list_ctor_(struct my_list * list, struct var_info creation_params)
{
    assert(list);
    assert(creation_params.file);
    assert(creation_params.func);
    assert(creation_params.name);

    list->info = creation_params;
    list->data = (struct list_elem *) calloc (LIST_MIN_LEN, sizeof(struct list_elem));
    list->head = 0;
    list->tail = 0;

    for (unsigned i = 1; i < LIST_MIN_LEN; i++) // в версии с prev добавить его сюда
    {
        list->data[i].val  = POISON;
    }

    for (unsigned i = 1; i < LIST_MIN_LEN - 1; i++) // переделать p.s. зачем?
    {
        list->data[i].next = -1 * (i + 1);
    }

    list->data[LIST_MIN_LEN - 1].next = 0;

    list_dump(list);

    return 0;
}

int list_dtor(struct my_list * list)
{
    assert(list);
    assert(list->data);

    list_dump(list);

    for (int i = 0; i < LIST_MIN_LEN; i++) // в версии с prev добавить его сюда // в версии с реаллокацией поменять константу на длину списка
    {
        list->data[i].val  = POISON;
        list->data[i].next = 0;
    }

    free(list->data);

    list->data = NULL;
    list->info.file = NULL;
    list->info.func = NULL;
    list->info.name = NULL;
    list->head = 0;
    list->tail = 0;

    return 0;
}


int list_push(struct my_list * list, unsigned curr, elem val)
{
    assert(list);
    assert(list->data);

    list_dump(list);

    
}