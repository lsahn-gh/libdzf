/* dzf-queue-priv.h
 *
 * MIT License
 *
 * Copyright (c) 2018-2023 Leesoo Ahn <lsahn@ooseel.net>
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

#ifndef DZF_QUEUE_PRIV_H
#define DZF_QUEUE_PRIV_H

#if !defined (DZF_QUEUE_USE_AS_PRIVATE)
#   error "Only <dzf/dzf-queue.h> can be included directly!"
#endif

#include "dzf-util.h"
#include "dzf-barrier.h"

#define DZF_BASE_USE_AS_PRIVATE
#include "dzf-base.h"
#undef  DZF_BASE_USE_AS_PRIVATE

/* -- Type Definition -- */
/*!
 * @def dzf_queue_t(T)
 * @brief Queue type
 *
 * @param T: type that represents an elem of 'data' array.
 *
 * \b Examples
 * @code{.c}
 *   typedef dzf_queue_t(long) q_long_t;
 *   typedef dzf_queue_t(int *) q_iptr_t;
 *   typedef dzf_queue_t(char *) q_str_t;
 * @endcode
 */
#define dzf_queue_t(T) \
    struct { \
        __dzf_base_t _unused1; \
        int front; \
        int rear; \
        T hold_elem; \
        T *data; \
    }

typedef dzf_queue_t(void*)       __dzf_queue_priv_void_t;
#define DZF_QUEUE_VOID(self)   ((__dzf_queue_priv_void_t*)self)

#define DZF_QUEUE_ALLOC_SIZE 16 /* default capacity */


/* -- Private APIs -- */
DZF_PRIVATE
static inline size_t
__dzf_queue_set_alloc_size(void *self,
                           size_t new_size)
{
    return __dzf_base_set_alloc_size(self, new_size);
}
#define __dzf_queue_set_capacity __dzf_queue_set_alloc_size


DZF_PRIVATE
static inline size_t
__dzf_queue_alloc_size(void *self)
{
    return __dzf_base_get_alloc_size(self);
}
#define __dzf_queue_capacity __dzf_queue_alloc_size


DZF_PRIVATE
static inline size_t
__dzf_queue_set_elem_size(void *self,
                          size_t new_size)
{
    return __dzf_base_set_elem_size(self, new_size);
}


DZF_PRIVATE
static inline size_t
__dzf_queue_elem_size(void *self)
{
    return __dzf_base_get_elem_size(self);
}


DZF_PRIVATE
static inline void
__dzf_queue_set_front(void *self,
                      int new_front)
{
    __dzf_queue_priv_void_t *q = self;

    q->front = new_front;
}


DZF_PRIVATE
static inline int
__dzf_queue_front(void *self)
{
    __dzf_queue_priv_void_t *q = self;

    return q->front;
}


DZF_PRIVATE
static inline void
__dzf_queue_set_rear(void *self,
                     int new_rear)
{
    __dzf_queue_priv_void_t *q = self;

    q->rear = new_rear;
}


DZF_PRIVATE
static inline int
__dzf_queue_rear(void *self)
{
    __dzf_queue_priv_void_t *q = self;

    return q->rear;
}


DZF_PRIVATE
static inline Bool
__dzf_queue_is_empty(void *self)
{
    return (__dzf_queue_front(self) == -1) ? TRUE : FALSE;
}


DZF_PRIVATE
static inline Bool
__dzf_queue_is_full(void *self)
{
    if (__dzf_queue_is_empty(self))
        return FALSE;

    /* '(rear + 1) % capacity == front' represents full */
    return ( ((__dzf_queue_rear(self) + 1) % __dzf_queue_capacity(self)) \
             == __dzf_queue_front(self) ) ? TRUE : FALSE;
}


/* called under early 'queue_is_full' */
DZF_PRIVATE
static inline void
__dzf_queue_adjust_rear(void *self)
{
    int next_value = (__dzf_queue_rear(self) + 1) % \
                     __dzf_queue_capacity(self);

    __dzf_queue_set_rear(self, next_value);

    if (__dzf_queue_front(self) == -1)
        __dzf_queue_set_front(self, 0);
}


/* called under early 'queue_is_empty' */
DZF_PRIVATE
static inline void
__dzf_queue_adjust_front(void *self)
{
    int next_value = (__dzf_queue_front(self) + 1) % \
                     __dzf_queue_capacity(self);

    if (__dzf_queue_front(self) == __dzf_queue_rear(self)) {
        next_value = -1;
        __dzf_queue_set_rear(self, next_value);
    }

    __dzf_queue_set_front(self, next_value);
}


DZF_PRIVATE
#define __dzf_queue_push_tail(self, value) \
    ( \
      __dzf_queue_adjust_rear(self), \
      (self)->data[__dzf_queue_rear(self)] = (value), \
      (void)0 /* represents success */ \
    )


DZF_PRIVATE
#define __dzf_queue_pop_head(self) \
    ( \
      (self)->hold_elem = (self)->data[__dzf_queue_front(self)], \
      __dzf_queue_adjust_front(self), \
      (self)->hold_elem \
    )


DZF_PRIVATE
static inline int
__dzf_queue_init(void *self,
                 size_t elem_size, size_t capacity)
{
    __dzf_queue_priv_void_t *q = self;

    if (capacity <= DZF_QUEUE_ALLOC_SIZE)
        capacity = DZF_QUEUE_ALLOC_SIZE;

    __dzf_base_init(q, 0, capacity, elem_size);
    __dzf_queue_set_front(q, -1);
    __dzf_queue_set_rear(q, -1);
    q->data = (void **)dzf_malloc(elem_size * capacity);

    return 0;
}


DZF_PRIVATE
static inline void
__dzf_queue_data_free(void *self)
{
    __dzf_queue_priv_void_t *q = self;

    if (q->data != NULL) {
        free(q->data);
        q->data = NULL;
    }
    __dzf_base_init(q, 0, 0, 0);
    __dzf_queue_set_front(q, -1);
    __dzf_queue_set_rear(q, -1);
}

#endif /* DZF_QUEUE_PRIV_H */
