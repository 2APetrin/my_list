#include "list_header.h"

int main(void)
{
    struct ptr_list list = {};
    list_ctor(&list);

    list_insert_after(&list, NULL, 12);
    list_insert_after(&list, list.head, 13);
    list_insert_after(&list, list.head, 13);
    list_insert_after(&list, list.head, 13);
    list_insert_after(&list, list.head, 13);

    printf("cap = %d\n", list.capacity);

    list_dtor(&list);

    return 0;
}