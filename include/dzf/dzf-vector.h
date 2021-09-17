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

#ifndef __DZF_VEC_H__
#define __DZF_VEC_H__

#if !defined (__LIBDZF_H_INCLUDE__)
#   error "Only <dzf.h> can be included directly!"
#endif

#include "dzf-vector-priv.h"

DZF_PUBLIC
static inline int
dzf_vec_new_with(void *self,
                 size_t elem_size, size_t capacity)
{
    ret_val_if_fail(self, -1);

    return __dzf_vec_init(self, elem_size, capacity);
}

DZF_PUBLIC
static inline int
dzf_vec_new(void *self,
            size_t elem_size)
{
    ret_val_if_fail(self, -1);

    return __dzf_vec_init(self, elem_size, DZF_VEC_DFLT_CAP);
}

DZF_PUBLIC
static inline void
dzf_vec_data_free(void *self)
{
    ret_if_fail(self);

    __dzf_vec_data_free(self);
}

DZF_PUBLIC
static inline void
dzf_vec_free(void *self)
{
    ret_if_fail(self);

    __dzf_vec_data_free(self);
    free(self);
}

DZF_PUBLIC
static inline int
dzf_vec_get_length(void *self)
{
    ret_val_if_fail(self, -1);

    return __dzf_vec_get_length(self);
}

DZF_PUBLIC
static inline int
dzf_vec_get_capacity(void *self)
{
    ret_val_if_fail(self, -1);

    return __dzf_vec_get_capacity(self);
}

DZF_PUBLIC
static inline Bool
dzf_vec_is_full(void *self)
{
    ret_val_if_fail(self, FALSE);

    return __dzf_vec_is_full(self);
}

DZF_PUBLIC
static inline Bool
dzf_vec_is_empty(void *self)
{
    ret_val_if_fail(self, FALSE);

    return __dzf_vec_is_empty(self);
}

DZF_PUBLIC
static inline void *
dzf_vec_get_pointer_at(void *self,
                       size_t index)
{
    ret_val_if_fail(self, NULL);
    ret_val_if_fail(__dzf_vec_index_validator(self, index), NULL);

    return __dzf_vec_get_pointer_at(self, index);
}

DZF_PUBLIC
#define dzf_vec_get_pointer(self, _idx) \
    dzf_vec_get_pointer_at(self, _idx)

DZF_PUBLIC
#define dzf_vec_set_value(self, _idx, _val) \
    dzf_vec_set_value_at(self, _idx, _val)

DZF_PUBLIC
#define dzf_vec_set_value_at(self, _idx, _val) \
    ( assert(__dzf_vec_index_validator(self, _idx)), \
      __dzf_vec_set_value_at(self, _idx, _val) )

DZF_PUBLIC
#define dzf_vec_get_value(self, _idx) \
    dzf_vec_get_value_at(self, _idx)

DZF_PUBLIC
#define dzf_vec_get_value_at(self, _idx) \
    ( assert(__dzf_vec_index_validator(self, _idx)), \
      __dzf_vec_get_value_at(self, _idx) )

DZF_PUBLIC
#define dzf_vec_add_at(self, _idx, _val) \
    ( assert(0 <= _idx && _idx <= __dzf_vec_get_allocated_size(self)), \
      __dzf_vec_insert_at(self, _idx, _val) )

DZF_PUBLIC
#define dzf_ved_add_head(self, val) \
    dzf_vec_add_at(self, 0, val)

DZF_PUBLIC
#define dzf_vec_add_tail(self, val) \
    dzf_vec_add_at(self, __dzf_vec_get_length(self), val)

DZF_PUBLIC
#define dzf_vec_rmv_at(self, _idx) \
    ( assert(__dzf_vec_index_validator(self, _idx)), \
      __dzf_vec_remove_at(self, _idx) )

DZF_PUBLIC
#define dzf_vec_rmv_head(self) \
    dzf_vec_rmv_at(self, 0)

DZF_PUBLIC
#define dzf_vec_rmv_tail(self) \
    dzf_vec_rmv_at(self, __dzf_vec_get_length(self)-1)

DZF_PUBLIC
#define dzf_vec_foreach(self, _fptr, ...) \
    for ( int i = 0; \
          i < dzf_vec_get_length(self); \
          (_fptr)(dzf_vec_get_pointer(self, i), __VA_ARGS__), ++i )

#endif
