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

/*! @file dzf-vector.h
 * 
 * @brief Vector data structure.
 * 
 * Vector is a data structure that the space of it is automatically able 
 * to extend the size of it when there is no space for a value to be added.
 * 
 * However, this is \b type-unsafe vector. functions are implemented based on 
 * \c #define directive. You must always take care of the type, \c T of dzf_vec_t(T).
 * 
 * When no space condition is met, the capacity would be multiplied by 2 for
 * every extension as below,
 * @code
 *   8 (with DFLT_VEC_CAP)
 *   16
 *   32
 *   64
 *   128
 *   256
 * @endcode
 * 
 * Please, take a look at dzf-vector.h and main.c in examples for how-to.
 */

#ifndef __DZF_VEC_H__
#define __DZF_VEC_H__

#if !defined (__LIBDZF_H_INCLUDE__)
#error "Only <dzf.h> can be included directly!"
#endif


#include "dzf-util.h"

#define _dzf_vec_log(prefix, fmt, ...) \
    _dzf_dbugf("** DZF::VECTOR::" prefix " -- ", fmt, __VA_ARGS__)

#define DFLT_VEC_CAP    8   /* default capacity */



/*
 * Attempt to allocate memory as much as size of T multiplies by capacity.
 * 
 * @param _vecptr: A pointer to the dzf_vec_t(T).
 * @param _vec_cap: Capacity.
 * @return None
 */
#define _dzf_vec_priv_init(_vecptr, _vec_cap) \
    do { \
        dzf_malloc((_vecptr)->data, dzf_sizeof(_vecptr) * _vec_cap); \
        _dzf_vec_log("MALLOC", "Required size: %zd bytes.\n", \
                dzf_sizeof(_vecptr) * _vec_cap); \
        dzf_vec_size(_vecptr) = 0; \
        dzf_vec_cap(_vecptr) = _vec_cap; \
    } while(FALSE)


/*
 * Attempt to resize alloc'd memory as much as capacity multiplies by 2.
 *
 * @param _vecptr: A pointer to the dzf_vec_t(T).
 * @return None
 */
#define _dzf_vec_priv_extend(_vecptr) \
    ( dzf_vec_is_full(_vecptr) ? \
      ( dzf_realloc( \
            (_vecptr)->data, (_vecptr)->data, \
            dzf_sizeof(_vecptr) * (dzf_vec_cap(_vecptr) * 2) ), \
        _dzf_vec_log( /* Print how many it is realloc'd. */ \
            "REALLOC", "Required size: %zd bytes.\n", \
            dzf_sizeof(_vecptr) * (dzf_vec_cap(_vecptr) * 2) ), \
        dzf_vec_cap(_vecptr) = dzf_vec_cap(_vecptr) * 2 \
      ) : 0 )


/*
 * Attempt to shrink alloc'd memory as much as divide by 2.
 *
 * Todo
 *
 * @param _vecptr: A pointer to the dzf_vec_t(T).
 * @return None
 */
#define _dzf_vec_priv_shrink(_vecptr)


/*
 * Check whether the index is out of index or not.
 *
 * If it is out of index, exception of assert raises.
 *
 * @param _vecptr: A pointer to the dzf_vec_t(T).
 * @return None
 */
#define _dzf_vec_priv_idx_chk(_vecptr, _idx) \
    assert(_idx >= 0 && _idx < dzf_vec_size(_vecptr))


/*
 * Get/Set a value at the index without care of type.
 * 
 * This is as Getter and Setter.
 * 
 * @param _vecptr: A pointer to the dzf_vec_t(T).
 * @return \c T typed data.
 */
#define _dzf_vec_priv_at(_vecptr, _idx) \
    ((_vecptr)->data[_idx])


/*!
 * Initialize a vector with required capacity size.
 *
 * @param _vecptr: A pointer to the dzf_vec_t(T).
 * @param _cap_sze: Capacity.
 * @return None
 */
#define dzf_vec_new_with(_vecptr, _cap_sze) \
    _dzf_vec_priv_init(_vecptr, _cap_sze)


/*!
 * Initialize a vector with default capacity, 8 (DFLT_VEC_CAP).
 * 
 * @param _vecptr: A pointer to the dzf_vec_t(T)
 * @return None
 */
#define dzf_vec_new(_vecptr) \
    _dzf_vec_priv_init(_vecptr, DFLT_VEC_CAP)


/*!
 * Free allocated memory to the data member.
 * 
 * @param _vecptr: A pointer to the dzf_vec_t(T).
 * @return None
 */
#define dzf_vec_free(_vecptr) \
    for ( free((_vecptr)->data), \
          (_vecptr)->data = NULL; \
          FALSE; )


/*!
 * Get how many elements it has.
 * 
 * @param _vecptr: A pointer to the dzf_vec_t(T).
 * @return \c int
 */
#define dzf_vec_size(_vecptr) \
    ((_vecptr)->size)


/*!
 * Get capacity of the vector.
 * 
 * @param _vecptr: A pointer to the dzf_vec_t(T).
 * @return \c int
 */
#define dzf_vec_cap(_vecptr) \
    ((_vecptr)->_cap)


/*!
 * Check whether it is full or not.
 * 
 * @param _vecptr: A pointer to the dzf_vec_t(T).
 * @return TRUE if it is full, or FALSE.
 */
#define dzf_vec_is_full(_vecptr) \
    ( dzf_vec_cap(_vecptr) == dzf_vec_size(_vecptr) ? TRUE : FALSE ) 


/*!
 * Return \c T typed data at the index.
 * 
 * @param _vecptr: A pointer to the dzf_vec_t(T).
 * @param _idx: An index of the vector.
 * @return \c T typed data at the index.
 */
#define dzf_vec_get_val_at(_vecptr, _idx) \
    ( _dzf_vec_priv_idx_chk(_vecptr, _idx), _dzf_vec_priv_at(_vecptr, _idx) )


/*!
 * Return a pointer to \c T typed data at the index.
 * 
 * @param _vecptr: A pointer to the dzf_vec_t(T).
 * @param _idx: An index of the vector.
 * @return A pointer to \c T typed data at the index.
 */
#define dzf_vec_get_ptr_at(_vecptr, _idx) \
    ( _dzf_vec_priv_idx_chk(_vecptr, _idx), &_dzf_vec_priv_at(_vecptr, _idx) )


/*!
 * Set a new value at an index.
 * 
 * @param _vecptr: A pointer to the dzf_vec_t(T).
 * @param _idx: An index of the vector.
 * @param value: \c T typed new value.
 * @return None
 */
#define dzf_vec_set(_vecptr, _idx, value) \
    for ( _dzf_vec_priv_idx_chk(_vecptr, _idx), \
          _dzf_vec_priv_at(_vecptr, _idx) = value; \
          FALSE; /* must be false not to loop. */ )


/*!
 * Add a new value at the end of the vec_t(T).
 * 
 * @param _vecptr: A pointer to the dzf_vec_t(T).
 * @param value: \c T typed value.
 * @return None
 */
#define dzf_vec_add(_vecptr, value) \
    for ( _dzf_vec_priv_extend(_vecptr), \
          _dzf_vec_priv_at(_vecptr, dzf_vec_size(_vecptr)) = value, \
          ++dzf_vec_size(_vecptr); \
          FALSE; )


/*!
 * Remove an element at an index.
 * 
 * <i>Note that it takes O(N) time for left-shifting after remove it.</i>
 * 
 * @param _vecptr: A pointer to the dzf_vec_t(T).
 * @param _idx: An index of the vector.
 * @return None
 */
#define dzf_vec_rmv(_vecptr, _idx) \
    for ( int i = (_dzf_vec_priv_idx_chk(_vecptr, _idx), _idx); \
          (i < dzf_vec_size(_vecptr) - 1) \
             ? TRUE : (--dzf_vec_size(_vecptr), FALSE); \
          (_dzf_vec_priv_at(_vecptr, i) = _dzf_vec_priv_at(_vecptr, i+1)), ++i )


/*!
 * Do something with the function through all elements.
 * 
 * @param _vecptr: A pointer to the dzf_vec_t(T).
 * @param _fptr: A pointer to a function that will be called.
 * @param ...: Various arguments to be passed into the function.
 * @return None
 */
#define dzf_vec_foreach(_vecptr, _fptr, ...) \
    for ( int i = 0; \
          i < dzf_vec_size(_vecptr); \
          (_fptr)(&_dzf_vec_priv_at(_vecptr, i), __VA_ARGS__), ++i )


#endif
