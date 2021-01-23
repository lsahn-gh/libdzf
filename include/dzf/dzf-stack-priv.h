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

#ifndef __DZF_STACK_PRIV_H__
#define __DZF_STACK_PRIV_H__

#if !defined (__LIBDZF_H_INCLUDE__)
# error "Only <dzf/dzf.h> can be included directly!"
#endif

#include "dzf-util.h"

/* -- Type Definition -- */
/*!
 * @def dzf_stack_t
 * @brief Stack type.
 *
 * @param T: A type that you want to hold.
 *
 * \b Examples
 * @code{.c}
 *   // Let's build three types.
 *   typedef dzf_stack_t(int) stk_int_t;
 *   typedef dzf_stack_t(struct _node) stk_node_t;
 *   typedef dzf_stack_t(char *) stk_str_t;
 * @endcode
 */
#define dzf_stack_t(T) \
  struct { \
    size_t _allocated_size; \
    size_t _element_size; \
    int top; \
    int capacity; \
    T *data; \
  }

typedef dzf_stack_t(char) __dzf_stack_priv_void_t;
#define DZF_STACK_VOID(_stkptr) ((__dzf_stack_priv_void_t*)_stkptr)


/* -- Define something else -- */
#define _dzf_stk_log(prefix, fmt, ...) \
    __dzf_log_with_domain("STACK", prefix, fmt, __VA_ARGS__)


/* -- Private APIs -- */
/*
 * Attempt to allocate memory as much as size of T multiplies by capacity.
 *
 * @param _stkptr: A pointer to the dzf_stack_t(T).
 * @param _stk_cap: Capacity.
 * @return None
 */
DZF_PRIVATE
#define _dzf_stack_priv_init(_stkptr, _stk_cap) \
    do { \
        __dzf_malloc((_stkptr)->data, __dzf_sizeof(_stkptr) * _stk_cap); \
        _dzf_stk_log("MALLOC", "Required size: %zd bytes.\n", \
                __dzf_sizeof(_stkptr) * _stk_cap); \
        _dzf_stack_top(_stkptr) = -1; \
        dzf_stack_cap(_stkptr) = _stk_cap; \
    } while(FALSE)


#if defined(DZF_DYNAMIC_STACK)
/*
 * Attempt to resize alloc'd memory as much as capacity multiplies by 2.
 *
 * @param _stkptr: A pointer to the dzf_stack_t(T).
 * @return None
 */
DZF_PRIVATE
# define    _dzf_stack_priv_extend(_stkptr) \
    ( (dzf_stack_is_full(_stkptr) == TRUE) ? \
      ( __dzf_realloc( \
            (_stkptr)->data, (_stkptr)->data, \
            __dzf_sizeof(_stkptr) * (dzf_stack_cap(_stkptr) * 2) ), \
        _dzf_stk_log( /* Print how many it is alloc'd to stderr. */ \
            "REALLOC", "Required size: %zd bytes.\n", \
            __dzf_sizeof(_stkptr) * (dzf_stack_cap(_stkptr) * 2) ), \
        dzf_stack_cap(_stkptr) = dzf_stack_cap(_stkptr) * 2 \
      ) : 0 )

#else /* !defined(DZF_DYNAMIC_STACK) */
/*
 * If \b DZF_DYNAMIC_STACK is off, _dzf_stack_priv_extend will be as
 * static stack and check the stack is full, or not.
 */
DZF_PRIVATE
# define    _dzf_stack_priv_extend(_stkptr) \
    assert(dzf_stack_is_full(_stkptr) == FALSE)

#endif /* defined(DZF_DYNAMIC_STACK) */


/*
 * Get where the top points to.
 *
 * @param _stkptr: A pointer to the dzf_stack_t(T).
 * @retur \c int
 */
DZF_PRIVATE
#define _dzf_stack_top(_stkptr) \
    ((_stkptr)->top)


#endif
