/*
 * MIT License
 *
 * Copyright (c) 2018 Yi-Soo An <yisooan@gmail.com>
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

/*! @file dzf-types.h
 *
 * @brief Data structure types.
 * 
 * @details
 * Please take a look at examples/main.c to figure out how-to.
 */

#ifndef __DZF_TYPES_H__
#define __DZF_TYPES_H__

#if !defined (__LIBDZF_H_INCLUDE__)
#error "Only <dzf.h> can be included directly!"
#endif


/*! 
 * @def dzf_vec_t(T)
 * @brief Vector type.
 * 
 * @param T: A type that you want to hold.
 * 
 * \b Examples
 * @code{.c}
 *   // Let's build a few types.
 *   typedef dzf_vec_t(int) vec_int_t;
 *   typedef dzf_vec_t(double) vec_double_t;
 *   typedef dzf_vec_t(char) vec_str_t;
 * @endcode
 */
#define dzf_vec_t(T) \
    struct { int size; int _cap; T *data; }


/*!
 * @def dzf_stack_t
 * @brief Stack type.
 * 
 * @param T: A type that you want to hold.
 * 
 * \b Examples
 * @code{.c}
 *   // Let's build a few types.
 *   typedef dzf_stack_t(int) stk_int_t;
 *   typedef dzf_stack_t(struct _node) stk_node_t;
 *   typedef dzf_stack_t(char *) stk_node_t;
 * @endcode
 */
#define dzf_stack_t(T) \
    struct { int top; int cap; T *data; }


/*!
 * @def dzf_queue_t
 * @brief Queue type.
 * 
 * @param T: A type that you want to hold.
 * 
 * \b Examples
 * @code{.c}
 *   // Let's build a few types.
 *   typedef dzf_queue_t(long) q_long_t;
 *   typedef dzf_queue_t(int *) q_iptr_t;
 *   typedef dzf_queue_t(char *) q_str_t;
 * @endcode
 */
#define dzf_queue_t(T) \
    struct { int front; int rear; int _cap; T *data; }


#endif
