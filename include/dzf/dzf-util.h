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

/*! @file dzf-util.h
 *
 * @brief Helpful stuffs are here.
 */

#ifndef __DZF_UTIL_H__
#define __DZF_UTIL_H__

#if !defined (__DZF_VEC_H__) && !defined (__DZF_STACK_H__) && \
    !defined (__DZF_QUEUE_H__) && !defined (__DZF_STRING_H__)
#error "<dzf-util.h> cannot be included directly!"
#endif


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>


/*! libdzf does not use bool type from C99.
 *
 * @enum _dzf_bool
 */
enum _dzf_bool { 
    FALSE = 0,  /*!< is as 0 */
    TRUE = 1    /*!< is as 1 */
};


#ifdef DZF_DEBUG
# define    _dzf_dbugf(prefix, fmt, ...) \
                (void)fprintf(stderr, prefix fmt, __VA_ARGS__)
#else
# define    _dzf_dbugf(prefix, fmt, ...) \
                ((void) 0)
#endif /* end of DZF_DEBUG */



#define dzf_log(prefix, fmt, ...) \
    _dzf_dbugf("** DZF::" prefix " -- ", fmt, __VA_ARGS__)


#define dzf_strerr(_msg) \
    fprintf(stderr, _msg "\n")


#define dzf_exit_with_err(_msg, _exitc) \
    ( dzf_strerr("** DZF -- " _msg), exit(_exitc) )


/*! Re-allocate already allocated memory.
 *
 * If _OLDPTR is NULL, it will be as \c malloc.
 *
 * @param _NPTR: A pointer to be saved allocated memory.
 * @param _OLDPTR: A pointer that already allocated memory.
 * @param _SIZE: Size of requirement.
 * @return None
 */
#define dzf_realloc(_NPTR, _OLDPTR, _SIZE) \
    ( (_NPTR = realloc(_OLDPTR, _SIZE)) == NULL ? \
      dzf_exit_with_err("Failed to allocate memory.", -1) : \
      ((void) 0) )


/*! Attempt to allocate memory.
 *
 * @param _PTR: A pointer to be saved allocated memory.
 * @param _SIZE: Size of requirement.
 * @return None
 */
#define dzf_malloc(_PTR, _SIZE) \
    dzf_realloc(_PTR, NULL, _SIZE)


/*! Compare any types.
 *
 * @param _x: Any object.
 * @param _y: Any object.
 * @return TRUE if both are same, or FALSE.
 */
#define dzf_cmp(_x, _y) \
    ( (_x == _y) ? TRUE : FALSE )


/*! Get a size of T type.
 *
 * @param _ptr: Any pointer to an object that has T *data member.
 * @return int
 */
#define dzf_sizeof(_ptr) \
    sizeof((_ptr)->data[0])


#endif
