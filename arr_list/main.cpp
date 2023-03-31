#include "list_header.h"
#include "list_logs.h"


int main(void)
{
    open_log_file();

    struct my_list list = {};
    list_ctor(&list);

    double var = 0.0;

    insert_after(&list, 3, 12);
    insert_after(&list, 1, 10);
    insert_after(&list, 2, -1);
    insert_after(&list, 3, 112);
    insert_after(&list, 2, 45);
    list_pop(&list, 3, &var);

    //printf("elem - %d\n", list_elem_search(&list, 10));
    //printf("logical elem - %d\n", search_index_element_based_on_its_logical_index_this_function_is_slooow_do_not_use_it_btw(&list, 3));
    //printf("%lg\n", var);

    list_dtor(&list);
    close_log_file();
    return 0;
}