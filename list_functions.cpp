#include "list_header.h"

int list_ctor_(struct my_list * list, struct var_info creation_params)
{
    assert(list);
    assert(creation_params.file);
    assert(creation_params.func);
    assert(creation_params.name);

    list->data   = (struct list_elem *) calloc (LIST_MIN_LEN, sizeof(struct list_elem));
    list->info   = creation_params;
    list->status = 0;
    list->head = 0;
    list->tail = 0;
    list->free = 1;

    for (unsigned i = 0; i < LIST_MIN_LEN; i++) // в версии с prev добавить его сюда
    {
        list->data[i].val  = POISON;
    }

    for (unsigned i = 1; i < LIST_MIN_LEN - 1; i++) // переделать p.s. зачем?
    {
        list->data[i].next = (int) (i + 1);
    }
    list->data[LIST_MIN_LEN - 1].next = 0;

    for (unsigned i = 1; i < LIST_MIN_LEN; i++)
    {
        list->data[i].prev = -1;
    }

    list_dump(list);

    return 0;
}

int list_dtor(struct my_list * list)
{
    assert(list);
    assert(list->data);

    list_dump(list);

    for (unsigned i = 0; i < LIST_MIN_LEN; i++) // в версии с реаллокацией поменять константу на длину списка
    {
        list->data[i].val  = POISON;
        list->data[i].next = 0;
        list->data[i].prev = 0;
    }

    free(list->data);

    list->data = NULL;
    list->info.file = NULL;
    list->info.func = NULL;
    list->info.name = NULL;
    list->head = 0;
    list->tail = 0;
    list->free = 0;

    return 0;
}


int find_free_ind(struct my_list * list)
{
    assert(list);
    assert(list->data);

    return list->data[list->free].next;
}


int insert_after(struct my_list * list, unsigned curr, elem val)
{
    assert(list);
    assert(list->data);

    list_dump(list);

    if (curr >= LIST_MIN_LEN)
    {
        printf("current position is out of range in list\n");
        list->status += BAD_CURR_POS;

        list_dump(list);

        return 1;
    }

    if (list->head == 0 && list->tail == 0)
    {
        list->tail = list->free;
        list->free = find_free_ind(list);

        list->data[list->tail].val = val;
        list->data[list->tail].next = 0;
        list->data[list->tail].prev = 0;  

        printf("first insert (after), free index is - %d\n", list->free);

        list->head = list->tail;

        return 0;
    }

    if ((int) curr == list->tail && list->free != 0) // если функция вставки после тейла
    {
        list->data[list->free].val  = val;
        list->data[list->free].prev = list->tail;
        list->data[list->tail].next = list->free;
        
        list->tail = list->free;
        list->free = find_free_ind(list);

        list->data[list->tail].next = 0;

        printf("tail inserted: prev - %d, curr - %d, next - %d, free - %d\n", list->data[list->tail].prev, list->tail, list->data[list->tail].next, list->free);

        return 0;
    }

    if (list->free != 0 && list->data[curr].prev != -1) //если просто в тело списка
    {
        list->data[list->free].val = val;
        
        int temp = list->free;

        list->free = find_free_ind(list);

        list->data[temp].prev = (int)curr;
        list->data[temp].next = list->data[curr].next;
        list->data[curr].next = temp;
        list->data[list->data[temp].next].prev = temp;

        printf("inserted in body: prev - %d, curr - %d, next - %d, val - %lg\n", list->data[temp].prev, temp, list->data[temp].next, list->data[temp].val);

        return 0;
    }

    printf("smth went wrong, go and see log, nothing happened to list\n");

    list_dump(list);
    return 1;
}


int insert_before(struct my_list * list, unsigned curr, elem val)
{
    assert(list);
    assert(list->data);

    list_dump(list);

    if (curr >= LIST_MIN_LEN)
    {
        printf("current position is out of range in list\n");
        list->status += BAD_CURR_POS;

        list_dump(list);

        return 1;
    }

    if (list->head == 0 && list->tail == 0)
    {
        list->tail = list->free;
        list->free = find_free_ind(list);

        list->data[list->tail].val = val;
        list->data[list->tail].next = 0;
        list->data[list->tail].prev = 0;  

        printf("first insert (before), free index is - %d\n", list->free);

        list->head = list->tail;

        return 0;
    }

    if ((int) curr == list->head && list->free != 0) // если функция вставки до головы
    {
        int temp = list->head;
        list->data[list->free].val  = val;
        list->data[list->free].prev = 0;
        list->data[list->head].prev = list->free;
        
        list->head = list->free;
        list->free = find_free_ind(list);

        list->data[list->head].next = temp;

        printf("insert (before): prev - %d, curr - %d, next - %d, val - %lg\n", list->data[temp].prev, temp, list->data[temp].next, list->data[temp].val);

        return 0;
    }

    if (list->data[curr].prev > 0 && list->free != 0)
    {
        list->data[list->free].val  = val;
        list->data[list->free].prev = list->data[curr].prev;
        list->data[list->data[list->free].prev].next = list->free;
        list->data[curr].prev = list->free;
        
        list->free = find_free_ind(list);
        list->data[list->data[curr].prev].next = (int)curr;

        printf("insert (before): prev - %d, curr - %d, next - %d, val - %lg\n", list->data[list->data[curr].prev].prev, list->data[curr].prev, (int)curr, list->data[list->data[curr].prev].val);

        return 0;
    }

    printf("smth went wrong, go and see log, nothing happened to list\n");

    list_dump(list);

    return 1;
}





int list_dump_(struct my_list * list, unsigned err_code, location_info loc_inf)
{
    return 0;
}
unsigned list_verify(struct my_list * list)
{
    return 0;
}