#include "list_header.h"
#include "list_logs.h"

// написать дампирование, реаллокацию, линеаризацию
// дописать дампирование и забить хуй

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
    //print_list(&list);

    printf("%lg\n", var);

    list_dtor(&list);
    close_log_file();
    return 0;
}