#include <stdio.h>
#include <assert.h>
#include <stdlib.h>


#define LOCATION __PRETTY_FUNCTION__, __FILE__, __LINE__
#define list_ctor(list) list_ctor_((list), {(#list), LOCATION})
#define list_dump(list) list_dump_((list), list_verify((list)), {LOCATION})


//! @brief type of our node values
//!
typedef double elem;


//! @brief node struct in list
//!
struct ptr_node
{
    elem val;
    struct ptr_node * next;
    struct ptr_node * prev;
};


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


//! @struct struct of our list
//! @brief main structure of our list
//!
struct ptr_list
{
    struct ptr_node * head;
    struct ptr_node * tail; 
    int capacity; 

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


//! @brief initializes ptr_list struct
//!
//! @param [out] list - ptr to our list object
//! @param [in]  creation_params - information about our list object creation
//!
//! @return 0 if ok, 1 if any errors
//!
int list_ctor_(struct ptr_list * list, struct var_info creation_params);


//! @brief destroys list object
//!
//! @param [in] list - ptr to our list object
//!
//! @return 0 if ok, 1 if any errors
//!
int list_dtor(struct ptr_list * list);


//! @brief adds node after choosen node ptr
//! 
//! @param [in] list - ptr to our list object
//! @param [in] curr_node - ptr to node to add after
//! @param [in] val - value to push into node
//!
//! @return 0 if ok, 1 if any errors
//!
int list_insert_after(struct ptr_list * list, struct ptr_node * curr_node, elem val);
