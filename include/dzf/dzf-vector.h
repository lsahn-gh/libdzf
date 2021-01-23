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


__DZF_PUBLIC
#define dzf_vec_new_with(_vecptr, _elem_size, _cap_sze) \
    __dzf_vec_init(DZF_VEC_VOID(_vecptr), _elem_size, _cap_sze)


__DZF_PUBLIC
#define dzf_vec_new(_vecptr, _elem_size) \
    dzf_vec_new_with(_vecptr, _elem_size, DZF_VEC_DFLT_CAP)


__DZF_PUBLIC
#define dzf_vec_free(_vecptr) \
    ( assert(__dzf_vec_magic_validator(DZF_VEC_VOID(_vecptr))), \
      __dzf_vec_free(DZF_VEC_VOID(_vecptr)) )


__DZF_PUBLIC
#define dzf_vec_get_length(_vecptr) \
    ( assert(__dzf_vec_magic_validator(DZF_VEC_VOID(_vecptr))), \
      __dzf_vec_get_length(DZF_VEC_VOID(_vecptr)) )


__DZF_PUBLIC
#define dzf_vec_get_capacity(_vecptr) \
    ( assert(__dzf_vec_magic_validator(DZF_VEC_VOID(_vecptr))), \
      __dzf_vec_get_capacity(DZF_VEC_VOID(_vecptr)) )


__DZF_PUBLIC
#define dzf_vec_is_full(_vecptr) \
    ( assert(__dzf_vec_magic_validator(DZF_VEC_VOID(_vecptr))), \
      __dzf_vec_is_full(DZF_VEC_VOID(_vecptr)) )


__DZF_PUBLIC
#define dzf_vec_is_empty(_vecptr) \
    ( assert(__dzf_vec_magic_validator(DZF_VEC_VOID(_vecptr))), \
      __dzf_vec_is_empty(DZF_VEC_VOID(_vecptr)) )


__DZF_PUBLIC
#define dzf_vec_get_pointer(_vecptr, _idx) \
    dzf_vec_get_pointer_at(_vecptr, _idx)


__DZF_PUBLIC
#define dzf_vec_get_pointer_at(_vecptr, _idx) \
    ( assert(__dzf_vec_magic_validator(DZF_VEC_VOID(_vecptr))), \
      assert(__dzf_vec_index_validator(DZF_VEC_VOID(_vecptr), _idx)), \
      __dzf_vec_get_pointer_at(DZF_VEC_VOID(_vecptr), _idx) )


__DZF_PUBLIC
#define dzf_vec_set_value(_vecptr, _idx, _val) \
    dzf_vec_set_value_at(_vecptr, _idx, _val)


__DZF_PUBLIC
#define dzf_vec_set_value_at(_vecptr, _idx, _val) \
    ( assert(__dzf_vec_magic_validator(DZF_VEC_VOID(_vecptr))), \
      assert(__dzf_vec_index_validator(DZF_VEC_VOID(_vecptr), _idx)), \
      __dzf_vec_set_value_at(_vecptr, _idx, _val) )


__DZF_PUBLIC
#define dzf_vec_get_value(_vecptr, _idx) \
    dzf_vec_get_value_at(_vecptr, _idx)


__DZF_PUBLIC
#define dzf_vec_get_value_at(_vecptr, _idx) \
    ( assert(__dzf_vec_magic_validator(DZF_VEC_VOID(_vecptr))), \
      assert(__dzf_vec_index_validator(DZF_VEC_VOID(_vecptr), _idx)), \
      __dzf_vec_get_value_at(_vecptr, _idx) )


__DZF_PUBLIC
#define dzf_vec_add(_vecptr, _idx, _val) \
    dzf_vec_add_at(_vecptr, _idx, _val)


__DZF_PUBLIC
#define dzf_vec_add_at(_vecptr, _idx, _val) \
    DZF_GUARD(__dzf_vec_insert_at(_vecptr, _idx, _val))


__DZF_PUBLIC
#define dzf_vec_add_back(_vecptr, _val) \
    dzf_vec_add_at(_vecptr, __dzf_vec_get_length(DZF_VEC_VOID(_vecptr)), _val)


__DZF_PUBLIC
#define dzf_vec_remove(_vecptr, _idx) \
    dzf_vec_remove_at(_vecptr, _idx)


__DZF_PUBLIC
#define dzf_vec_remove_at(_vecptr, _idx) \
    DZF_GUARD(__dzf_vec_remove_at(_vecptr, _idx))


__DZF_PUBLIC
#define dzf_vec_remove_back(_vecptr) \
    dzf_vec_remove_at(_vecptr, __dzf_vec_get_length(_vecptr)-1)


#define dzf_vec_foreach(_vecptr, _fptr, ...) \
    for ( int i = 0; \
          i < dzf_vec_get_length(_vecptr); \
          (_fptr)(dzf_vec_get_pointer(DZF_VEC_VOID(_vecptr), i), __VA_ARGS__), ++i )


#endif
