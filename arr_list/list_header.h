#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

#define LOCATION __PRETTY_FUNCTION__, __FILE__, __LINE__
#define list_ctor(list) list_ctor_((list), {(#list), LOCATION})


//! @brief type of data inside list
//!
typedef double elem;


//! @brief minimum length of our list
//!
const unsigned LIST_MIN_LEN = 16;


//! @brief value on place of deleted/free elements
//!
const elem POISON = NAN;


//! @brief accuracy for equald
//!
const double EPSYLON = 0.00001;


//! @struct variable information
//! @brief  struct with information about variable for ctor
//! 
//! @var name - struct variable name
//! @var func - function where variable was created
//! @var file - file where variable was created
//! @var line - number of line where variable was created
//!
struct var_info
{
    const char * name;
    const char * func;
    const char * file;
    size_t       line;
};


//! @struct struct of elements in list array
//! @brief contains indexes of previous and next elements
//!
//! @var val  - value that is inside list element
//! @var next - index of next element
//! @var prev - index of previous element
//!
struct list_elem
{
    elem val;
    int  next;
    int  prev;
};


//! @struct struct of our list
//! @brief contains elements of list and indexes of first and last element
//!
//! @var data - ptr to array of list elements structures
//! @var tail - index of last elem
//! @var head - index of first elem
//! @var free - index of first free list element (free head)
//! @var info - struct with informaion about our variable
//!
struct my_list
{
    struct list_elem * data;
    unsigned capacity;
    int tail;
    int head;
    int free;

    int status;

    var_info info;
};


//! @struct location of calling function
//! @brief locaion of call
//!
//! @var func - function, where calling function is
//! @var file - file, where calling function is
//! @var line - line, where calling function is
//!
struct location_info
{
    const char * func;
    const char * file;
    size_t       line;
};


//! @brief creates data arrange and initializes head and tail. Also inits data elements
//!
//! @param [out] list            - ptr to our list object
//! @param [in]  creation_params - information about our list object creation
//!
//! @return 1 if error, 0 if ok
//!
int list_ctor_(struct my_list * list, struct var_info creation_params);


//! @brief deletes our list anf frees all allocated memory
//!
//! @param [in] list - ptr to our list object
//!
//! @return 1 if error in destruction, 0 if ok
//!
int list_dtor(struct my_list * list);


//! @brief adds an element to list after choosen element
//!
//! @param [out] list - ptr to our list object
//! @param [in]  curr - physical index of element where pushing element will be added after
//! @param [in]  val  - value of element
//!
//! @return 1 if error, 0 if ok
//!
int insert_after(struct my_list * list, unsigned curr, elem val);


//! @brief adds an element to list before choosen element
//!
//! @param [out] list - ptr to our list object
//! @param [in]  curr - physical index of element where pushing element will be added after
//! @param [in]  val  - value of element
//!
//! @return 1 if error, 0 if ok
//!
int insert_before(struct my_list * list, unsigned curr, elem val);


//! @brief gets index of first free element
//! 
//! @param [in] list - ptr to our list object
//!
//! @return 0 if there are no free elements and -1 * index of free elem if there is that elem
//!
int find_free_ind(struct my_list * list);


//! @brief gets val from node and deletes it
//!
//! @param [out] list - ptr to our list object
//! @param [out]  val - ptr where to put value from node
//!
//! @return 1 if error, 0 if ok
//!
int list_pop(struct my_list * list, int curr, elem * val);


//! @brief prints in stdout our data arange
//!
//! @param [out] list - ptr to our list object
//!
//! @return 1 if error, 0 if ok
//!
int print_list(struct my_list * list);


//! @brief add element to tail
//!
//! @param [out] list - ptr to our list object
//! @param [in]  val  - value to put into list
//!
//! @return 1 if error, 0 if ok
//!
int insert_after_tail(struct my_list * list, elem val);


//! @brief add element before head
//!
//! @param [out] list - ptr to our list object
//! @param [in]  val  - value to put into list
//!
//! @return 1 if error, 0 if ok
//!
int insert_before_head(struct my_list * list, elem val);


//! @brief pops tail element
//!
//! @param [out] list - ptr to our list object
//! @param [out] val  - ptr where to put value from node
//!
//! @return 1 if error, 0 if ok
//!
int list_pop_tail(struct my_list * list, elem * value);


//! @brief pops head element
//!
//! @param [out] list - ptr to our list object
//! @param [out] val  - ptr where to put value from node
//!
//! @return 1 if error, 0 if ok
//!
int list_pop_head(struct my_list * list, elem * value);


//! @brief gets ptr to head node
//!
//! @param [out] list - ptr to our list object
//!
//! @return ptr to head node of our list
//!
int list_get_head(struct my_list * list);


//! @brief gets ptr to tail node
//!
//! @param [out] list - ptr to our list object
//!
//! @return ptr to tail node of our list
//!
int list_get_tail(struct my_list * list);


//! @brief gets ptr to node after choosen
//!
//! @param [out] list - ptr to our list object
//!
//! @return ptr to node after choosen node
//!
int list_get_after(struct my_list * list, int curr);


//! @brief gets ptr to node before choosen
//!
//! @param [out] list - ptr to our list object
//!
//! @return ptr to node before choosen node
//!
int list_get_before(struct my_list * list, int curr);


//! @brief searches index of first element that have same val as argument
//!
//! @param [in] list - ptr to our list object
//! @param [in] val  - value to search
//!
//! @return index of first element that have same val as argument
//!
int list_elem_search(struct my_list * list, elem val);


//! @brief checks if two double values are close enough to each othes to be equal
//!
int equald(double val1, double val2);


//! @brief search elem elem on logical index
//!
//! @param [in] list - ptr to our list object
//! @param [in] logical_index - logical index
//!
//! @return physical index of logical index element
//!
int search_index_element_based_on_its_logical_index_this_function_is_slooow_do_not_use_it_btw(struct my_list * list, int logical_index);
