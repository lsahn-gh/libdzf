/* dzf-list.h
 *
 * MIT License
 *
 * Copyright (c) 2023 Leesoo Ahn <lsahn@ooseel.net>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the
 * Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN
 * AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH
 * THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/*! @file dzf-list.h
 *
 * @brief Double Linked-List Abstracted Type Structure.
 */

#ifndef DZF_LIST_H
#define DZF_LIST_H

typedef struct dzf_list_head {
    dzf_list_t *prev, *next;
} dzf_list_t;

#define dzf_list_of(entry) (dzf_list_t *)(entry)

static inline void
DZF_LIST_HEAD_INIT(dzf_list_t *head)
{
    head->next = head;
    head->prev = head;
}

static inline void
__dzf_list_add(dzf_list_t *new,
               dzf_list_t *prev,
               dzf_list_t *next)
{
    new->next = next;
    new->prev = prev;
    next->prev = new;
    prev->next = new;
}

static inline dzf_list_t *
dzf_list_add(dzf_list_t *new,
             dzf_list_t *head)
{
    __dzf_list_add(new, head, head->next);

    return head;
}

static inline dzf_list_t *
dzf_list_add_last(dzf_list_t *new,
                  dzf_list_t *head)
{
    __dzf_list_add(new, head->prev, head);

    return head;
}

static inline void
__dzf_list_del(dzf_list_t *prev,
               dzf_list_t *next)
{
    prev->next = next;
    next->prev = prev;
}

static inline void
dzf_list_del(dzf_list_t *elem)
{
    __dzf_list_del(elem->prev, elem->next);
    elem->prev = elem->next = elem; /* being itself */
}

static inline dzf_list_t *
dzf_list_del_first(dzf_list_t *head)
{
    dzf_list_t *first = head->next;

    dzf_list_del(first);

    return first;
}

static inline dzf_list_t *
dzf_list_del_last(dzf_list_t *head)
{
    dzf_list_t *last = head->prev;

    dzf_list_del(last);

    return last;
}

static inline int
dzf_list_is_empty(dzf_list_t *head)
{
    return (head->next) == head;
}

static inline int
dzf_list_is_head(dzf_list_t *elem, dzf_list_t *head)
{
    return entry == head;
}

#define dzf_list_for_each(pos, head) \
    for (pos = head->next; !list_is_head(pos, head); pos = pos->next)

#define dzf_list_for_each_r(pos, head) \
    for (pos = head->prev; !list_is_head(pos, head); pos = pos->prev)

#define dzf_list_for_each_safe(pos, n, head) \
    for (pos = head->next, n = pos->next; \
        !list_is_head(pos, head); \
        pos = n, n = pos->next)

#define dzf_list_for_each_r_safe(pos, p, head) \
    for (pos = head->prev, p = pos->prev; \
        !list_is_head(pos, head); \
        pos = p, p = pos->prev)

#endif /* DZF_LIST_H */
