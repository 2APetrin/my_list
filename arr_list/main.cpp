#include "list_header.h"

int main(void)
{
    struct my_list list = {};
    list_ctor(&list);

    print_list(&list);
    insert_after(&list, 3, 12);
    
    print_list(&list);
    insert_after(&list, 1, 13);
    
    print_list(&list);
    insert_after_tail(&list, 69);

    print_list(&list);
    insert_before_head(&list, 88);

    double x = 0;

    print_list(&list);
    list_pop_tail(&list, &x);

    printf("value %lg\n", x);

    print_list(&list);
    list_pop_head(&list, &x); // не работает

    printf("value %lg\n", x);

    print_list(&list);
    
    list_dtor(&list);
    return 0;
}