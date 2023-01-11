/* dzf-stack-priv.h
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

#ifndef DZF_STACK_PRIV_H
#define DZF_STACK_PRIV_H

#if !defined(DZF_STACK_USE_AS_PRIVATE)
#   error "Only <dzf/dzf-stack.h> can be included directly!"
#endif

#define DZF_VEC_USE_AS_PRIVATE
#include "dzf-vector-priv.h"
#undef  DZF_VEC_USE_AS_PRIVATE

/* -- Type Definition -- */
/*!
 * @def dzf_stack_t(T)
 * @brief Stack type
 *
 * @param T: type that represents an elem of 'data' array.
 *
 * \b Examples
 * @code{.c}
 *   typedef dzf_stack_t(int) stack_int_t;
 *   typedef dzf_stack_t(struct _node) stack_node_t;
 *   typedef dzf_stack_t(char *) stack_str_t;
 * @endcode
 */
#define dzf_stack_t(T) \
    struct { \
        __dzf_base_t _unused1; \
        T *data; \
    }

typedef dzf_stack_t(char) __dzf_stack_priv_void_t;
#define DZF_STACK_VOID(self) ((__dzf_stack_priv_void_t*)self)

#define DZF_STACK_ALLOC_SIZE 16 /* default capacity */


/* -- Private APIs -- */
DZF_PRIVATE
static inline size_t
__dzf_stack_set_alloc_size(void *self,
                           size_t new_size)
{
    return __dzf_base_set_alloc_size(self, new_size);
}


DZF_PRIVATE
static inline size_t
__dzf_stack_alloc_size(void *self)
{
    return __dzf_base_get_alloc_size(self);
}


DZF_PRIVATE
static inline size_t
__dzf_stack_set_elem_size(void *self,
                          size_t new_size)
{
    return __dzf_base_set_elem_size(self, new_size);
}


DZF_PRIVATE
static inline size_t
__dzf_stack_elem_size(void *self)
{
    return __dzf_base_get_elem_size(self);
}


DZF_PRIVATE
static inline int
__dzf_stack_set_top(void *self,
                    int new_top)
{
    return __dzf_base_set_length(self, new_top);
}


DZF_PRIVATE
static inline int
__dzf_stack_top(void *self)
{
    return __dzf_base_get_length(self);
}


DZF_PRIVATE
static inline int
__dzf_stack_size(void *self)
{
    return __dzf_stack_top(self) + 1;
}


DZF_PRIVATE
static inline Bool
__dzf_stack_is_empty(void *self)
{
    return (__dzf_stack_top(self) == -1 ? TRUE : FALSE);
}


DZF_PRIVATE
static inline Bool
__dzf_stack_is_full(void *self)
{
    if (__dzf_stack_size(self) == 0)
        return FALSE;
    /* assume always 'alloc_size >= stack_size' */
    return (__dzf_stack_alloc_size(self) - __dzf_stack_size(self)
            ? FALSE : TRUE);
}


DZF_PRIVATE
static inline int
__dzf_stack_init(void *self,
                 size_t elem_size, size_t capacity)
{
    __dzf_vec_init(self, elem_size, capacity /* as alloc size */);
    __dzf_stack_set_top(self, -1);

    return 0;
}


DZF_PRIVATE
static inline void
__dzf_stack_data_free(void *self)
{
    __dzf_vec_data_free(self);
}


DZF_PRIVATE
static inline int
__dzf_stack_try_growing(void *self)
{
    /*
     * if 'DZF_STACK_STATIC_SIZE' is defined, then
     *    die not to corrupt current buckets.
     * otherwise
     *    try to grow the stack up to the current 'alloc_size * 2'.
     */
#if defined(DZF_STACK_STATIC_SIZE)
    /* abort at runtime if try growing */
    __die(FALSE);
#else
    return __dzf_vec_try_growing(self);
#endif
}


DZF_PRIVATE
#define __dzf_stack_push(self, val) \
    ( \
      __dzf_stack_is_full(self) ? __dzf_stack_try_growing(self) : 0, \
      __dzf_stack_set_top(self, __dzf_stack_size(self)), \
      (self)->data[__dzf_stack_top(self)] = val, \
      (void)0 /* represents success */ \
    )


DZF_PRIVATE
#define __dzf_stack_pop(self) \
    ( \
      (self)->data[DZF_GET_BASE(self)->length--] \
    )


DZF_PRIVATE
#define __dzf_stack_peek(self) \
    ( \
      (self)->data[__dzf_stack_top(self)] \
    )

#endif /* DZF_STACK_PRIV_H */
