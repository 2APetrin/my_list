#include "list_header.h"


int list_ctor_(struct ptr_list * list, struct var_info creation_params)
{
    assert(list);
    assert(creation_params.file);
    assert(creation_params.func);
    assert(creation_params.name);

    list->head = NULL;
    list->tail = NULL;
    list->capacity = 0;

    list->info = creation_params;
    list->status = 0;

    return 0;
}


int list_dtor(struct ptr_list * list)
{
    assert(list);
    assert(list->info.file);
    assert(list->info.name);
    assert(list->info.func);

    struct ptr_node * next_node = list->head->next;
    if (list->head) free(list->head);

    for (int i = 0; i < list->capacity - 2; i++)
    {
        free(next_node->prev);
        next_node = next_node->next;
    }

    if (list->tail) free(list->tail);

    list->capacity = 0;
    list->head = NULL;
    list->tail = NULL;
    list->info.file = NULL;
    list->info.func = NULL;
    list->info.name = NULL;
    list->info.line = 0;
    list->status = 0;
    
    return 0;
}


int list_insert_after(struct ptr_list * list, struct ptr_node * curr_node, elem val)
{
    assert(list);
    assert(list->info.file);
    assert(list->info.name);
    assert(list->info.func);
 
    if (!list->head && !list->tail) // самый первый элемент
    {
        list->head = (struct ptr_node *) calloc (1, sizeof(struct ptr_node));
        list->tail = list->head;
        list->head->next = list->head;
        list->head->prev = list->head;
        list->head->val  = val;
        list->capacity = 1;

        printf("first\n");

        return 0;
    }

    if (curr_node == list->tail) // в конец списка
    {
        struct ptr_node * new_node = (struct ptr_node *) calloc (1, sizeof(struct ptr_node));
    
        new_node->val = val;
        new_node->prev = curr_node;
        new_node->next = curr_node->next;
        curr_node->next->prev = new_node;
        curr_node->next = new_node;
        list->capacity++;

        list->tail = new_node;

        printf("tail\n");

        return 0;
    }

    if (curr_node != list->tail) // внутрь списка
    {
        struct ptr_node * new_node = (struct ptr_node *) calloc (1, sizeof(struct ptr_node));
    
        new_node->val = val;
        new_node->prev = curr_node;
        new_node->next = curr_node->next;
        curr_node->next->prev = new_node;
        curr_node->next = new_node;
        list->capacity++;

        printf("into\n");

        return 0;
    }

    printf("Something went wrong\n");
    return 1;
}