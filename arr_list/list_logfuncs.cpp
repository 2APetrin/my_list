#include "list_header.h"
#include "list_logs.h"


FILE * graphviz_file = NULL;
FILE * log_file      = NULL;
int graphviz_png_count = 0;


int open_grapgviz_file(void)
{
    if ((graphviz_file = fopen("../logs/log_graphviz.dot", "w")) == NULL)
    {
        printf("Cannot open graphviz file. Programm shutdown\n");
        return 1;
    }

    return 0;
}


int close_grapgviz_file(void)
{
    ASSERT(graphviz_file);

    fprintf(graphviz_file, "}");
    fclose(graphviz_file);

    return 0;
}


int open_log_file(void)
{
    log_file = fopen("../logs/log_file.html", "w");
    fprintf(log_file, "<html>\n");
    return 0;
}


int close_log_file(void)
{
    ASSERT(log_file);

    fprintf(log_file, "\n</html>\n");
    fclose(log_file);
    return 0;
}


int init_graphviz_file(struct my_list * list)
{
    ASSERT(list);
    ASSERT(graphviz_file);

    fprintf(graphviz_file, "digraph\n{\n    rankdir = LR;\n    list_info[shape = record, label = \"{{capacity = %u | <f0> head = %d | <f1> tail = %d | <f2> free = %d}}\"];\n\n", list->capacity, list->head, list->tail, list->free);

    return 0;
}


int graphviz_add_node(struct list_elem * node, int index, node_type type)
{
    ASSERT(node);
    ASSERT(graphviz_file);

    fprintf(graphviz_file, "    node%d[shape = Mrecord, label = \"{index = %d} | {value = %lg} | {next = %d | prev = %d}\", style = \"filled\", fillcolor = \"#%X\"];\n", index, index, node->val, node->next, node->prev, (unsigned) get_color(type));
    
    return 0;
}


int get_color(node_type type)
{
    switch (type)
    {
    case HEAD_TAIL:
        {
            return 0xF08C8C;
        }
        break;
    
    case MIDDLE:
        {
            return 0xFFD452;
        }
        break;
    
    case ZERO:
        {
            return 0x8FFF8A;
        }
        break;
    
    case FREE:
        {
            return 0xCF9EFF;
        }
        break;

    default:
        break;
    }

    return 0;
}


int link_nodes(int index1, int index2, int color)
{
    fprintf(graphviz_file, "    node%d->node%d [color = \"#%X\"];\n", index1, index2, (unsigned) color);
    return 0;
}


int link_head_n_tail_n_free(int head_ind, int tail_ind, int free_ind)
{
    ASSERT(graphviz_file);

    fprintf(graphviz_file, "    list_info:<f0>->node%d [color = \"black\", style=\"dashed\"];\n", head_ind);
    fprintf(graphviz_file, "    list_info:<f1>->node%d [color = \"black\", style=\"dashed\"];\n", tail_ind);
    fprintf(graphviz_file, "    list_info:<f2>->node%d [color = \"black\", style=\"dashed\"];\n", free_ind);

    return 0;
}

unsigned int list_dump_(struct my_list * list, unsigned err_code, location_info loc_inf)
{
    ASSERT(list);

    if (err_code)
    {
        error_translate(err_code, loc_inf);
        return err_code;
    }
    
    fprintf(log_file, "\n<pre>");
    fprintf(log_file, "\ndump from: \nfunc - %s, \nfile - %s, \nline - %lu\n\n", loc_inf.file, loc_inf.func, loc_inf.line);
    fprintf(log_file, "data-ptr - %p,\ncapacity - %u,\nfree   - %d,\nhead   - %d,\ntail   - %d,\nstatus - %d\n", list->data, list->capacity, list->free, list->head, list->tail,list->status);
    fprintf(log_file, "</pre>\n");

    open_grapgviz_file();
    init_graphviz_file(list);

    graphviz_add_node(&list->data[0], 0, ZERO);

    for (int i = 1; i < (int)list->capacity; i++)
    {
        if (i == list->head || i == list->tail)
        {
            graphviz_add_node(&list->data[i], i, HEAD_TAIL);
        }

        else if (list->data[i].prev == -1)
        {
            graphviz_add_node(&list->data[i], i, FREE);
        }

        else 
        {
            graphviz_add_node(&list->data[i], i, MIDDLE);
        }
    }

    fprintf(graphviz_file, "\n");

    for (int i = 1; i < (int)list->capacity; i++)
    {
        if (list->data[i].next == 0)
        {
            if (list->data[i].prev != -1 && list->data[i].prev != 0)
            {
                link_nodes(i, list->data[i].prev, BLUE);
            }
        }

        else
        {
            if (list->data[i].prev == -1)
            {
                link_nodes(i, list->data[i].next, GREEN);
            }
            else
            {
                link_nodes(i, list->data[i].next, RED);
                if (list->data[i].prev != 0)
                {
                    link_nodes(i, list->data[i].prev, BLUE);
                }
            }
        }
    }

    fprintf(graphviz_file, "\n");

    link_head_n_tail_n_free(list->head, list->tail, list->free);
    close_grapgviz_file();

    char sys_cmd[200] = "dot ../logs/log_graphviz.dot -Tpng -o ../logs/list_dump";
    snprintf(sys_cmd + strlen(sys_cmd), 30, "%d.png", graphviz_png_count);

    system(sys_cmd);

    fprintf(log_file, "\n<img src=\"../logs/list_dump%d.png\" width=\"100%%\">\n", graphviz_png_count);
    
    graphviz_png_count++;
    return 0;
}


int error_translate(unsigned err_code, location_info loc_inf)
{
    ASSERT(log_file);

    fprintf(log_file, "<pre>\n");
    fprintf(log_file, "verify failed at: \nfunc - %s, \nfile - %s, \nline - %lu\n\nERRORS:\n", loc_inf.file, loc_inf.func, loc_inf.line);

    for (int i = 0; i < error_count; i++)
    {
        switch(err_code & (1 << i))
        {
            case BAD_POS_INS_AFTER:
                fprintf(log_file, "You have given wrong position to add node after\n"); 
                break;  

            case CURR_ZERO_POS:
                fprintf(log_file, "You have given 0 position in list pop. You can't pop 0 element\n");
                break;
            
            case BAD_POS_POP:
                fprintf(log_file, "You have given wrong position in list pop\n");
                break;

            case BAD_DATA_PTR:
                fprintf(log_file, "You have NULL ptr to data array\n");
                break;

            default:
                fprintf(log_file, "I have not got enough time, so if you see this (if you're a mentor pls forgive me) check error codes or simply write error translate to the end\n");
                break;
        }
    }

    fprintf(log_file, "</pre>\n");

    return 0;
}


unsigned list_verify(struct my_list * list)
{
    ASSERT(list);

    int stat = 0;
    
    if (list->free > (int)list->capacity || list->free < 0)
        stat |= BAD_FREE;
    
    if (list->head > (int)list->capacity || list->head < 0)
        stat |= BAD_HEAD;

    if (list->tail > (int)list->capacity || list->tail < 0)
        stat |= BAD_TAIL;

    if (!list->data)
        stat |= BAD_DATA_PTR;
    
    if (!(list->info.file) || !(list->info.func) || !(list->info.name))
        stat |= BAD_LIST_INFO;

    if (list->status < 0)
    {
        list->status = 0;
        stat |= BAD_LIST_STATUS;
    }

    list->status = stat;
    return (unsigned)stat;
}
