//
//  p1.hpp
//  99-Problems
//
//  Created by Robert Baron on 5/11/18.
//  Copyright © 2018 Robert Baron. All rights reserved.
//

#ifndef list_h
#define list_h

#include <stdio.h>

#define RC_OK 0
#define RC_ERROR_MEMORY 2
#define RC_ERROR_LIST_DNE 1
#define RC_ERROR_MEMBER_DNE 3

#ifdef __cplusplus
extern "C"
{
#endif
    /* double linked list */
    struct c_double_list_tag;
    typedef struct c_double_list_tag
    {
        void *element;
        struct c_double_list_tag *next;
        struct c_double_list_tag *prev;
    } c_double_list;

    /* double linked list head */
    typedef struct
    {
        int (*del_element)(void *e);
        void *(*dup_element)(void *e);
        int (*cmp_element)(void *e1, void *e2);
        char *(*to_string)(void *e);
        c_double_list *lh;
    } c_double_list_head;

    c_double_list_head *dl_create(void *(*dup_element)(void *e), int (*del_element)(void *e), char *(*to_string)(void *e));
    int dl_delete(c_double_list_head **lh);
    int dl_delete_member(c_double_list_head **list, int n);
    c_double_list_head *dl_last(c_double_list_head **lh);
    int dl_tail_add(c_double_list_head **lh, void *e);
    int dl_add_element(c_double_list_head **lh, void *e);

    int dl_push(c_double_list_head **lh, void *e);
    int dl_pop(c_double_list_head **lh, void *e);

    int dl_list2str(c_double_list_head **list, char *buf, long buf_size);
#ifdef __cplusplus
}
#endif
#endif /* list_hpp */
