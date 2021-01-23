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
#define DZF_VEC_VOID(_vecptr)   ((__dzf_vec_priv_void_t*)_vecptr)


/* -- Define something else -- */
#define DZF_VEC_DFLT_CAP        8   /* default capacity */
#define dzf_vec_log(prefix, fmt, ...) \
    __dzf_log_with_domain("VECTOR", prefix, fmt, __VA_ARGS__)


/* -- Private APIs -- */
__DZF_PRIVATE
static inline int
__dzf_vec_set_length(__dzf_vec_priv_void_t *vec,
                     int length)
{
    /* We don't care whether size is less than and equal to 0 */
    if (vec->_length != length)
        vec->_length = length;

    return length;
}


__DZF_PRIVATE
static inline int
__dzf_vec_get_length(__dzf_vec_priv_void_t *vec)
{
    return vec->_length;
}


__DZF_PRIVATE
static inline size_t
__dzf_vec_set_allocated_size(__dzf_vec_priv_void_t *vec,
                             size_t new_size)
{
    if (vec->_allocated_size != new_size)
        vec->_allocated_size = new_size;

    return new_size;
}


__DZF_PRIVATE
static inline size_t
__dzf_vec_get_allocated_size(__dzf_vec_priv_void_t *vec)
{
    return vec->_allocated_size;
}


__DZF_PRIVATE
static inline size_t
__dzf_vec_set_element_size(__dzf_vec_priv_void_t *vec,
                           size_t new_size)
{
    if (vec->_element_size != new_size)
        vec->_element_size = new_size;

    return new_size;
}


__DZF_PRIVATE
static inline size_t
__dzf_vec_get_element_size(__dzf_vec_priv_void_t *vec)
{
    return vec->_element_size;
}


__DZF_PRIVATE
static inline Bool
__dzf_vec_index_validator(__dzf_vec_priv_void_t *vec,
                          int index)
{
    return (index >= 0 && index < __dzf_vec_get_length(vec));
}


__DZF_PRIVATE
static inline int
__dzf_vec_get_capacity(__dzf_vec_priv_void_t *vec)
{
    return __dzf_vec_get_allocated_size(vec) - __dzf_vec_get_length(vec);
}


__DZF_PRIVATE
static inline Bool
__dzf_vec_is_full(__dzf_vec_priv_void_t *vec)
{
    return (__dzf_vec_get_allocated_size(vec) == __dzf_vec_get_length(vec));
}


__DZF_PRIVATE
static inline Bool
__dzf_vec_is_empty(__dzf_vec_priv_void_t *vec)
{
    return (__dzf_vec_get_length(vec) == 0);
}


__DZF_PRIVATE
static inline int
__dzf_vec_expand(__dzf_vec_priv_void_t *vec)
{
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


__DZF_PRIVATE
static inline int
__dzf_vec_init(__dzf_vec_priv_void_t *vec,
               size_t elem_size,
               size_t capacity)
{
    if (capacity <= 0)
        capacity = DZF_VEC_DFLT_CAP;

    vec->_length = 0;
    vec->_element_size = elem_size;
    vec->_allocated_size = capacity;
    vec->data = dzf_malloc(elem_size * capacity);

    dzf_vec_log("MALLOC ", "Vector can have %zd items now\n", capacity);

    return 0;
}


__DZF_PRIVATE
static inline int
__dzf_vec_free(__dzf_vec_priv_void_t *vec)
{ 
    if (vec->data == NULL)
        return 0;

    free(vec->data);
    vec->data = NULL;
    vec->_length = 0;
    vec->_element_size = 0;
    vec->_allocated_size = 0;

    return 0;
}


__DZF_PRIVATE
static inline void *
__dzf_vec_get_pointer_at(__dzf_vec_priv_void_t *vec,
                         size_t index)
{
    index = index * __dzf_vec_get_element_size(vec);

    return &(vec->data[index]);
}


__DZF_PRIVATE
#define __dzf_vec_get_value_at(_vecptr, _idx) \
    ((_vecptr)->data[_idx])


__DZF_PRIVATE
#define __dzf_vec_set_value_at(_vecptr, _idx, _val) \
    ((_vecptr)->data[_idx] = _val)


__DZF_PRIVATE
#define __dzf_vec_insert_at(_vecptr, _idx, _val) \
    { \
        assert(_idx <= __dzf_vec_get_allocated_size(DZF_VEC_VOID(_vecptr))); \
        __dzf_vec_expand(DZF_VEC_VOID(_vecptr)); \
        int n = __dzf_vec_get_length(DZF_VEC_VOID(_vecptr)); \
        for (int i = n; i > _idx; i--) { /* shifting */ \
            __dzf_vec_set_value_at(_vecptr, i, __dzf_vec_get_value_at(_vecptr, i-1)); \
        } \
        __dzf_vec_set_value_at(_vecptr, _idx, _val); \
        __dzf_vec_set_length(DZF_VEC_VOID(_vecptr), n+1); \
    }


__DZF_PRIVATE
#define __dzf_vec_remove_at(_vecptr, _idx) \
    { \
        assert(__dzf_vec_index_validator(DZF_VEC_VOID(_vecptr), _idx)); \
        int n = __dzf_vec_get_length(DZF_VEC_VOID(_vecptr)); \
        for (int i = _idx; i < n-1; i++) { /* shifting */ \
            __dzf_vec_set_value_at(_vecptr, i, __dzf_vec_get_value_at(_vecptr, i+1)); \
        } \
        __dzf_vec_set_length(DZF_VEC_VOID(_vecptr), __dzf_vec_get_length(DZF_VEC_VOID(_vecptr))-1); \
    }


#endif
