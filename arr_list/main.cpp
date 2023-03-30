#include "list_header.h"
#include "list_logs.h"

// написать дампирование, реаллокацию, линеаризацию

int main(void)
{
    open_log_file();

    struct my_list list = {};
    list_ctor(&list);

    insert_after(&list, 3, 12);
    insert_after(&list, 1, 10);
    insert_after(&list, 2, -1);
    insert_after(&list, 3, 112);
    insert_after(&list, 2, 45);
    //print_list(&list);

    list_dtor(&list);
    return 0;
}