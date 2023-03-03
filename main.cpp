#include "list_header.h"

int main(void)
{
    struct my_list list = {};
    list_ctor(&list);

    insert_after(&list, 3, 12);
    insert_after(&list, 1, 13);
    insert_after(&list, 2, 43);
    insert_before(&list, 2, 26);

    list_dtor(&list);
    return 0;
}