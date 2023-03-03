#include "list_header.h"

int main(void)
{
    struct my_list list = {};
    list_ctor(&list);

    print_list(&list);
    insert_after(&list, 3, 12);
    
    print_list(&list);
    insert_after(&list, 1, 13);
    
    for (unsigned i = 0; i < LIST_MIN_LEN - 1; i++)
    {
        print_list(&list);
        insert_before(&list, 2, 26);
    }
    
    print_list(&list);
    insert_before(&list, 2, 26);
    double val = 0.0;

    for (unsigned i = 1; i < LIST_MIN_LEN; i++)
    {
        print_list(&list);
        list_pop(&list, (int) i, &val);
    }
    

    print_list(&list);
    list_pop(&list, 2, &val);

    print_list(&list);
    list_pop(&list, 1, &val);

    printf("val = %lg\n", val);

    print_list(&list);

    list_dtor(&list);
    return 0;
}