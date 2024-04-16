//  adt_list.c
//  Abstract data types list
//
//    This is a simple implementation of a doubly linked list using an
//    Object Oriented style with C.
//
//    It would have been simpler to make a custom implementation for each
//    list type, however having the same code being used for any type is
//    less time consuming for new types as it can just be used and enable
//    it to be combined with other abstract data types.
//
//    Not the most efficient code as it allocates many small chunks of
//    memory.  A way to make it more effienct is to allocate the structures
//    being used as large block, and having a "free list" as well as a
//    "used list".
//
//  Created by Robert Baron on 5/11/18.
//  Copyright © 2018 Robert Baron. All rights reserved.
//  draftkings???

// P1 is finding the last element of a linked list
#include "adt_list.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// C solution
c_double_list_head *dl_create(void *(*dup_element)(void *e), int (*del_element)(void *e), char *(*to_string)(void *e))
{
    c_double_list_head *lh = calloc(1, sizeof(c_double_list_head));
    if (lh)
    {
        lh->dup_element = dup_element;
        lh->del_element = del_element;
        lh->to_string = to_string;
        lh->lh = NULL;
    }
    return lh;
}

c_double_list_head *dl_last(c_double_list_head **list)
{
    c_double_list_head *ret_list = NULL;
    if (list && *list && (*list)->lh && (*list)->lh->prev)
    {
        ret_list = (c_double_list_head *)calloc(1, sizeof(c_double_list_head));
        ret_list->lh = (c_double_list *)calloc(1, sizeof(c_double_list));
        if (ret_list && ret_list->lh)
        {
            ret_list->dup_element = (*list)->dup_element;
            ret_list->del_element = (*list)->del_element;
            ret_list->to_string = (*list)->to_string;
            ret_list->lh->element = (*list)->dup_element((*list)->lh->prev->element);
            ret_list->lh->next = ret_list->lh;
            ret_list->lh->prev = ret_list->lh;
        }
        else
        {
            if (ret_list->lh)
            {
                free(ret_list->lh);
                ret_list->lh = NULL;
            }
            if (ret_list)
            {
                free(ret_list);
                ret_list = NULL;
            }
        }
    }
    return ret_list;
}

int dl_add_element(c_double_list_head **list, void *e)
{
    if (!list)
    {
        return RC_ERROR_LIST_DNE;
    }
    if (!(*list)->lh)
    {
        (*list)->lh = (c_double_list *)calloc(1, sizeof(c_double_list));
        if ((*list)->lh)
        {
            (*list)->lh->element = (*list)->dup_element(e);
            (*list)->lh->next = (*list)->lh->prev = (*list)->lh;
        }
    }
    else
    {
        c_double_list *l = (c_double_list *)calloc(1, sizeof(c_double_list));
        if (!l)
        {
            return RC_ERROR_MEMORY;
        }
        c_double_list *head = (*list)->lh;
        l->next = head;
        head->prev->next = l;
        l->prev = head->prev;
        head->prev = l;
        l->element = (*list)->dup_element(e);
    }
    return 0;
}

int dl_delete_member(c_double_list_head **list, int n)
{
    if (!list || !(*list) || !(*list)->lh)
        return RC_ERROR_LIST_DNE;

    c_double_list *le = (*list)->lh;
    int x = 0;
    while (x < n && le->next != (*list)->lh)
    {
        le = le->next;
        x++;
    }
    /* did we move to the correct position to delete */
    if (x == n)
    {
        if (le->next == le && le->prev == le)
        {
            if (le->element)
            {
                (*list)->del_element(le->element);
                le->element = NULL;
            }
            (*list)->lh = NULL;
            free(le);
        }
        else
        {
            if ((*list)->lh == le)
            {
                (*list)->lh = le->next;
            }
            if (le->element)
            {
                (*list)->del_element(le->element);
                le->element = NULL;
            }
            le->next->prev = le->prev;
            le->prev->next = le->next;
            free(le);
        }
        return RC_OK;
    }
    return RC_ERROR_MEMBER_DNE;
}

int dl_delete_list(c_double_list_head **list)
{
    if (!list && !(*list))
    {
        return RC_ERROR_LIST_DNE;
    }
    while (dl_delete_member(list, 0) == RC_OK)
        /* do nothing */;
    return RC_OK;
}

int dl_delete(c_double_list_head **list)
{
    if (!list && !(*list))
    {
        return RC_ERROR_LIST_DNE;
    }
    int rc = dl_delete_list(list);
    if (rc == RC_OK)
        free(*list);
    return rc;
}

int dl_push(c_double_list_head **list, void *e)
{
    if (!list)
    {
        return RC_ERROR_LIST_DNE;
    }
    return 1;
}

int dl_pop(c_double_list_head **list, void *e)
{
    if (!list)
    {
        return RC_ERROR_LIST_DNE;
    }
    return 1;
}

// This is more for debugging than actual use.
int dl_list2str(c_double_list_head **list, char *buf, long buf_size)
{
    if (!list)
    {
        return RC_ERROR_LIST_DNE;
    }
    strncpy(buf, "{ ", buf_size);
    if (*list && (*list)->lh)
    {
        c_double_list *le = (*list)->lh->next;
        char *element_str;
        element_str = (*list)->to_string((*list)->lh->element);
        strncat(buf, element_str, buf_size);
        strncat(buf, ", ", buf_size);
        free(element_str);
        while (le != (*list)->lh)
        {
            element_str = (*list)->to_string(le->element);
            strncat(buf, element_str, buf_size);
            strncat(buf, ", ", buf_size);
            free(element_str);
            le = le->next;
        }
    }
    strncat(buf, "}", buf_size);
    return 0;
}