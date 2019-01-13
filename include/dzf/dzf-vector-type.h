/*
 * MIT License
 *
 * Copyright (c) 2018-2019 Yi-Soo An <yisooan@gmail.com>
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

#ifndef __DZF_VEC_TYPE_H__
#define __DZF_VEC_TYPE_H__

#if !defined (__LIBDZF_H_INCLUDE__)
#   error "Only <dzf.h> can be included directly!"
#endif

#include "dzf-object.h"

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
        dzf_object_t _obj; \
        int _length; \
        size_t _allocated_size; \
        size_t _element_size; \
        T *data; \
    }

typedef dzf_vec_t(char)         __dzf_vec_priv_void_t;
#define DZF_VEC_VOID(_vecptr)   ((__dzf_vec_priv_void_t*)_vecptr)

#endif
