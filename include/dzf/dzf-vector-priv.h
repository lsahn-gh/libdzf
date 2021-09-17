/*
 * MIT License
 *
 * Copyright (c) 2018-2021 Leesoo Ahn <lsahn@ooseel.net>
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

#ifndef __DZF_VEC_PRIV_H__
#define __DZF_VEC_PRIV_H__

#if !defined (__LIBDZF_H_INCLUDE__)
#   error "Only <dzf.h> can be included directly!"
#endif

#include "dzf-util.h"

/* -- Type Definition -- */
/*!
 * @def dzf_vec_t(T)
 * @brief Vector type.
 *
 * @param T: A type to represent the elements.
 *
 * \b Examples
 * @code{.c}
 *   // Build three types.
 *   typedef dzf_vec_t(int) vec_int_t;
 *   typedef dzf_vec_t(double) vec_double_t;
 *   typedef dzf_vec_t(char *) vec_str_t;
 * @endcode
 */
#define dzf_vec_t(T) \
    struct { \
        int _length; \
        size_t _allocated_size; \
        size_t _element_size; \
        T *data; \
    }

typedef dzf_vec_t(char)         __dzf_vec_priv_void_t;
#define DZF_VEC_VOID(self)   ((__dzf_vec_priv_void_t*)self)


/* -- Define something else -- */
#define DZF_VEC_DFLT_CAP        8   /* default capacity */
#define dzf_vec_log(prefix, fmt, ...) \
    __dzf_log_with_domain("VECTOR", prefix, fmt, __VA_ARGS__)


/* -- Private APIs -- */
DZF_PRIVATE
static inline int
__dzf_vec_set_length(void *self,
                     int length)
{
    __dzf_vec_priv_void_t *vec = self;

    /* We don't care whether size is less than and equal to 0 */
    if (vec->_length != length)
        vec->_length = length;

    return length;
}


DZF_PRIVATE
static inline int
__dzf_vec_get_length(void *self)
{
    __dzf_vec_priv_void_t *vec = self;

    return vec->_length;
}


DZF_PRIVATE
static inline size_t
__dzf_vec_set_allocated_size(void *self,
                             size_t new_size)
{
    __dzf_vec_priv_void_t *vec = self;

    if (vec->_allocated_size != new_size)
        vec->_allocated_size = new_size;

    return new_size;
}


DZF_PRIVATE
static inline size_t
__dzf_vec_get_allocated_size(void *self)
{
    __dzf_vec_priv_void_t *vec = self;

    return vec->_allocated_size;
}


DZF_PRIVATE
static inline size_t
__dzf_vec_set_element_size(void *self,
                           size_t new_size)
{
    __dzf_vec_priv_void_t *vec = self;

    if (vec->_element_size != new_size)
        vec->_element_size = new_size;

    return new_size;
}


DZF_PRIVATE
static inline size_t
__dzf_vec_get_element_size(void *self)
{
    __dzf_vec_priv_void_t *vec = self;

    return vec->_element_size;
}


DZF_PRIVATE
static inline Bool
__dzf_vec_index_validator(void *self,
                          int index)
{
    __dzf_vec_priv_void_t *vec = self;

    return (index >= 0 && index < __dzf_vec_get_length(vec));
}


DZF_PRIVATE
static inline int
__dzf_vec_get_capacity(void *self)
{
    __dzf_vec_priv_void_t *vec = self;

    return __dzf_vec_get_allocated_size(vec) - __dzf_vec_get_length(vec);
}


DZF_PRIVATE
static inline Bool
__dzf_vec_is_full(void *self)
{
    __dzf_vec_priv_void_t *vec = self;

    return (__dzf_vec_get_allocated_size(vec) == __dzf_vec_get_length(vec));
}


DZF_PRIVATE
static inline Bool
__dzf_vec_is_empty(void *self)
{
    __dzf_vec_priv_void_t *vec = self;

    return (__dzf_vec_get_length(vec) == 0);
}


DZF_PRIVATE
static inline int
__dzf_vec_expand(void *self)
{
    __dzf_vec_priv_void_t *vec = self;
    size_t new_allocated_size = 0;

    if (__dzf_vec_is_full(vec)) {
        new_allocated_size = __dzf_vec_get_allocated_size(vec) * 2;
        vec->data = dzf_realloc(vec->data,
                                __dzf_vec_get_element_size(vec) * new_allocated_size);
        __dzf_vec_set_allocated_size(vec, new_allocated_size);
        dzf_vec_log("REALLOC", "Vector can have %zd items now\n", new_allocated_size);
    }

    return new_allocated_size;
}


DZF_PRIVATE
static inline int
__dzf_vec_init(void *self,
               size_t elem_size, size_t capacity)
{
    __dzf_vec_priv_void_t *vec = self;

    if (capacity <= 0)
        capacity = DZF_VEC_DFLT_CAP;

    vec->_length = 0;
    vec->_element_size = elem_size;
    vec->_allocated_size = capacity;
    vec->data = dzf_malloc(elem_size * capacity);

    dzf_vec_log("MALLOC ", "Vector can have %zd items now\n", capacity);

    return 0;
}


DZF_PRIVATE
static inline void
__dzf_vec_data_free(void *self)
{
    __dzf_vec_priv_void_t *vec = self;

    if (vec->data != NULL) {
        free(vec->data);
        vec->data = NULL;
    }
    vec->_length = 0;
    vec->_element_size = 0;
    vec->_allocated_size = 0;
}


DZF_PRIVATE
static inline void *
__dzf_vec_get_pointer_at(void *self,
                         size_t index)
{
    __dzf_vec_priv_void_t *vec = self;

    index = index * __dzf_vec_get_element_size(vec);
    return &(vec->data[index]);
}


DZF_PRIVATE
#define __dzf_vec_get_value_at(self, _idx) \
    ((self)->data[_idx])


DZF_PRIVATE
#define __dzf_vec_set_value_at(self, _idx, _val) \
    ((self)->data[_idx] = _val)


DZF_PRIVATE
#define __dzf_vec_self_memmove(self, _idx, _direction) \
   memmove(__dzf_vec_get_pointer_at(self, _idx _direction), \
           __dzf_vec_get_pointer_at(self, _idx), \
           __dzf_vec_get_length(self) - _idx)


DZF_PRIVATE
#define __dzf_vec_insert_at(self, _idx, _val) \
    ( \
        __dzf_vec_expand(self), \
        ((_idx == __dzf_vec_get_length(self)) \
            ? NULL : __dzf_vec_self_memmove(self, _idx, __right_x(1))), \
        __dzf_vec_set_value_at(self, _idx, _val), \
        __dzf_vec_set_length(self, __dzf_vec_get_length(self)+1) \
    )


DZF_PRIVATE
#define __dzf_vec_remove_at(self, _idx) \
    ( \
        (_idx == __dzf_vec_get_length(self)) \
            ? NULL : __dzf_vec_self_memmove(self, _idx+1, __left_x(1)), \
        __dzf_vec_set_length(self, __dzf_vec_get_length(self)-1) \
    )

#endif
