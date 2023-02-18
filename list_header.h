#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

#define LOCATION __PRETTY_FUNCTION__, __FILE__, __LINE__
#define list_ctor(list) list_ctor_((list), {(#list), LOCATION})


//! @brief type of data inside list
typedef double elem;


//! @brief extern logfile variable
extern FILE * logfile; 


//! @brief minimum length of our list
const unsigned LIST_MIN_LEN = 32;


//! @brief value on place of deleted/free elements
const elem POISON = NAN;


//! @struct struct of elements in list array
//! @brief contains indexes of previous and next elements
//!
//! @var val  - value that is inside list element
//! @var next - index of next element
//! @var prev - index of previous element

struct list_elem
{
    elem val;
    int  next;
    //int  prev;
};


//! @struct struct of our list
//! @brief contains elements of list and indexes of first and last element
//!
//! @var data - ptr to array of list elements structures
//! @var tail - index of last elem
//! @var head - index of first elem
//! @var info - struct with informaion about our variable

struct my_list
{
    struct list_elem * data;
    int tail;
    int head;

    var_info info;
};


//! @struct location of calling function
//! @brief locaion of call
//!
//! @var func - function, where calling function is
//! @var file - file, where calling function is
//! @var line - line, where calling function is

struct location_info
{
    const char * func;
    const char * file;
    size_t       line;
};


//! @struct variable information
//! @brief  struct with information about variable for ctor
//! 
//! @var name - struct variable name
//! @var func - function where variable was created
//! @var file - file where variable was created
//! @var line - number of line where variable was created

struct var_info
{
    const char * name;
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

int list_ctor_(my_list * list, struct var_info creation_params);
