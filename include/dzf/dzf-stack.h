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

/*! @file dzf-stack.h
 *
 * @brief Stack data structure.
 * 
 * Stack is a data structure based on LIFO, also known as Last In First Out.
 * 
 * dzf-stack provides two stack types,
 * - \b Static stack. Once it is built, the length of it never changed.
 * - \b Dynamic stack. It grows up and down anytime if it needs to be resized.
 * 
 * Default: Static stack.  
 * Add \b -DDZF_DYNAMIC_STACK compile flag to switch.
 * 
 * When no space condition is met with \b -DDZF_DYNAMIC_STACK , the capacity 
 * would be multiplied by 2 for every extension as vector.
 * @code
 *   8 (with DFLT_STACK_CAP)
 *   16
 *   32
 *   64
 *   128
 *   256
 * @endcode
 */

#ifndef __DZF_STACK_H__
#define __DZF_STACK_H__

#if !defined (__LIBDZF_H_INCLUDE__)
#error "Only <dzf.h> can be included directly!"
#endif


#include "dzf-util.h"

#define _dzf_stk_log(prefix, fmt, ...) \
    _dzf_dbugf("** DZF::STACK::" prefix " -- ", fmt, __VA_ARGS__)

#define DFLT_STACK_CAP      8



/*
 * Attempt to allocate memory as much as size of T multiplies by capacity.
 * 
 * @param _stkptr: A pointer to the dzf_stack_t(T).
 * @param _stk_cap: Capacity.
 * @return None
 */
#define _dzf_stack_priv_init(_stkptr, _stk_cap) \
    do { \
        dzf_malloc((_stkptr)->data, dzf_sizeof(_stkptr) * _stk_cap); \
        _dzf_stk_log("MALLOC", "Required size: %zd bytes.\n", \
                dzf_sizeof(_stkptr) * _stk_cap); \
        _dzf_stack_top(_stkptr) = -1; \
        dzf_stack_cap(_stkptr) = _stk_cap; \
    } while(FALSE)


#ifdef DZF_DYNAMIC_STACK
/*
 * Attempt to resize alloc'd memory as much as capacity multiplies by 2.
 * 
 * @param _stkptr: A pointer to the dzf_stack_t(T).
 * @return None
 */
# define    _dzf_stack_priv_extend(_stkptr) \
    ( (dzf_stack_is_full(_stkptr) == TRUE) ? \
      ( dzf_realloc( \
            (_stkptr)->data, (_stkptr)->data, \
            dzf_sizeof(_stkptr) * (dzf_stack_cap(_stkptr) * 2) ), \
        _dzf_stk_log( /* Print how many it is alloc'd to stderr. */ \
            "REALLOC", "Required size: %zd bytes.\n", \
            dzf_sizeof(_stkptr) * (dzf_stack_cap(_stkptr) * 2) ), \
        dzf_stack_cap(_stkptr) = dzf_stack_cap(_stkptr) * 2 \
      ) : 0 )


/*!
 * Initialize a stack with default capacity, 8 (DFLT_STACK_CAP).
 * 
 * This is available with \b DZF_DYNAMIC_STACK flag.
 * 
 * @param _stkptr: A pointer to the dzf_stack_t(T).
 * @return None
 */
#define dzf_stack_new(_stkptr) \
    _dzf_stack_priv_init(_stkptr, DFLT_STACK_CAP)
#else
/*
 * If \b DZF_DYNAMIC_STACK is off, _dzf_stack_priv_extend will be as
 * static stack and check the stack is full, or not.
 */
# define    _dzf_stack_priv_extend(_stkptr) \
    assert(dzf_stack_is_full(_stkptr) == FALSE)
#endif


/*
 * Get where the top points to.
 * 
 * @param _stkptr: A pointer to the dzf_stack_t(T).
 * @retur \c int
 */
#define _dzf_stack_top(_stkptr) \
    ((_stkptr)->top)


/*!
 * Initialize a stack with required capacity size.
 * 
 * @param _stkptr: A pointer to the dzf_stack_t(T).
 * @param _cap_sze: Capacity.
 * @return None
 */
#define dzf_stack_new_with(_stkptr, _cap_sze) \
    _dzf_stack_priv_init(_stkptr, _cap_sze)


/*!
 * Free allocated memory to the data member.
 * 
 * @param _stkptr: A pointer to the dzf_stack_t(T).
 * @return None
 */
#define dzf_stack_free(_stkptr) \
    for ( free((_stkptr)->data), \
          (_stkptr)->data = NULL; \
          FALSE; )


/*!
 * Get how many elements it has.
 * 
 * @param _stkptr: A pointer to the dzf_stack_t(T).
 * @return \c int
 */
#define dzf_stack_size(_stkptr) \
    _dzf_stack_top(_stkptr)+1


/*!
 * Get capacity of the stack.
 * 
 * @param _stkptr: A pointer to the dzf_stack_t(T).
 * @return \c int
 */
#define dzf_stack_cap(_stkptr) \
    ((_stkptr)->cap)


/*!
 * Check it is empty or not.
 * 
 * @param _stkptr: A pointer to the dzf_stack_t(T).
 * @return TRUE if it is empty, or FALSE.
 */
#define dzf_stack_is_empty(_stkptr) \
    ( _dzf_stack_top(_stkptr) == -1 ? TRUE : FALSE )


/*!
 * Check it is full or not.
 * 
 * @param _stkptr: A pointer to the dzf_stack_t(T).
 * @return TRUE if it is full, or FALSE.
 */
#define dzf_stack_is_full(_stkptr) \
    ( dzf_stack_size(_stkptr) == dzf_stack_cap(_stkptr) ? TRUE : FALSE )


/*!
 * Push a data at the top of the stack.
 * 
 * @param _stkptr: A pointer to the dzf_stack_t(T).
 * @param value: \c T typed value.
 * @return None
 */
#define dzf_stack_push(_stkptr, value) \
    for ( \
         _dzf_stack_priv_extend(_stkptr), \
         ++_dzf_stack_top(_stkptr), \
         (_stkptr)->data[_dzf_stack_top(_stkptr)] = value; \
         FALSE; /* must be false not to loop. */ )


/*!
 * Pop a data at the top of the stack.
 * 
 * @param _stkptr: A pointer to the dzf_stack_t(T).
 * @return \c T typed value.
 */
#define dzf_stack_pop(_stkptr) \
    ( assert(dzf_stack_is_empty(_stkptr) == FALSE), \
      --_dzf_stack_top(_stkptr), \
      (_stkptr)->data[dzf_stack_size(_stkptr)] )


/*!
 * Get a data at the top of the stack.
 * 
 * <i>Note that this does not remove the data as dzf_stack_pop.</i>
 * 
 * @param _stkptr: A pointer to the dzf_stack_t(T).
 * @return \c T typed value.
 */
#define dzf_stack_at_top(_stkptr) \
    ( assert(dzf_stack_is_empty(_stkptr) == FALSE), \
      (_stkptr)->data[_dzf_stack_top(_stkptr)] )


/*!
 * Do something with the function through all elements.
 * 
 * @param _stkptr: A pointer to the dzf_stack_t(T).
 * @param _fptr: A pointer to a function that will be called.
 * @param ...: Various arguments to be passed into the function.
 * @return None
 */
#define dzf_stack_foreach(_stkptr, _fptr, ...) \
    for ( int i = 0; \
          i < dzf_stack_size(_stkptr); \
          (_fptr)(&((_stkptr)->data[i]), __VA_ARGS__), ++i )
        

#endif
