#pragma once
#include "list_header.h"

#define list_dump(list) list_dump_((list), list_verify((list)), {LOCATION})

#define ASSERT(cond)                                                 \
if (!(cond))                                                         \
{                                                                    \
    printf("\nError in %s in line %d in function %s in file %s\n\n", \
           #cond, __LINE__, __PRETTY_FUNCTION__, __FILE__),          \
    abort();                                                         \
}                                                                                                                                       \


//! @brief logfile
//!
extern FILE * log_file;


//! @brief graphviz file
//!
extern FILE * graphviz_file;


//! @brief extern counter for graphviz pngs
//!
extern int graphviz_png_count;


//! @brief type of printed node
//!
enum node_type
{
    ZERO      = 0,
    HEAD_TAIL = 1,
    MIDDLE    = 2,
    FREE      = 3
};


//! @brief colors for arrows
//!
enum arrow_colors
{
    RED   = 0xFF0F0F,
    BLUE  = 0x170FFF,
    GREEN = 0x3CAA3C
};


//! @brief error codes for list
//!
enum list_errors
{
    BAD_POS_INS_AFTER  = (1 << 0),
    CURR_ZERO_POS      = (1 << 1),
    CAP_LESS_ZERO      = (1 << 2),
    BAD_FREE           = (1 << 3),
    BAD_HEAD           = (1 << 4),
    BAD_TAIL           = (1 << 5),
    BAD_DATA_PTR       = (1 << 6),
    BAD_POS_INS_BEFORE = (1 << 7),
    BAD_POS_POP        = (1 << 8),
    BAD_LIST_INFO      = (1 << 9),
    BAD_LIST_STATUS    = (1 << 10)
};

//! @brief number of list_errors members 
//! dont forget to modify it when you modify list errors
const int error_count = 11;


//! @brief opens graphviz file
//!
//! @return 1 if error, 0 if ok
//!
int open_grapgviz_file(void);


//! @brief closes graphviz file
//!
//! @return 1 if error, 0 if ok
//!
int close_grapgviz_file(void);


//! @brief initialises graphviz file
//!
//! @param [in] list - ptr to our list object
//!
//! @return 1 if error, 0 if ok
//!
int init_graphviz_file(struct my_list * list);


//! @brief prints add_node command into graphviz file
//!
//! @param [in] node - ptr to vizualizing node object
//! @param [in] index - index of our node
//! @param [in] type - node type
//!
//! @return 1 if error, 0 if ok
//!
int graphviz_add_node(struct list_elem * node, int index, node_type type);


//! @brief finds color from mode type
//!
//! @param [in] type - type of our node
//!
//! @return code of needed color and 0 if error
//!
int get_color(node_type type);


//! @brief links nodes in graphviz png
//!
//! @param [in] index1 - index of first element (from)
//! @param [in] index2 - index of second element (where)
//!
//! @return 1 if error, 0 if ok
//!
int link_nodes(int index1, int index2, int color);


//! @brief connects tail n head nodes with list info
//! 
//! @param [in] head_ind - index of head
//! @param [in] tail_ind - index of tail
//! @param [in] free_ind - index of first free element 
//!
//! @return 1 if error, 0 if ok
//!
int link_head_n_tail_n_free(int head_ind, int tail_ind, int free_ind);


//! @brief checks our list for errors before or after using it in function
//!
//! @param [in] list - ptr to our list object
//!
//! @return error code if there are errors, 0 if list is ok
//!
unsigned list_verify(struct my_list * list);


//! @brief takes error code from list_verify and dump info into log
//!
//! @param [in] list     - ptr to our list object
//! @param [in] err_code - error code to dump
//! @param [in] loc_inf  - file, function and line where dump was called
//!
//! @return 1 if error, 0 if ok
//!
unsigned list_dump_(struct my_list * list, unsigned err_code, location_info loc_inf); //--not written


//! @brief gets error number and translates it into logfile
//!
//! @param [in] err_code - number that contains happened errors
//! @param [in] loc_inf  - struct with dump location
//!
//! @return 1 if error, 0 if ok
//!
int error_translate(unsigned err_code, location_info loc_inf);


//! @brief opens log_file and writes <html> in it
int open_log_file(void);


//! @brief closes log_file and writes </html> in it
int close_log_file(void);