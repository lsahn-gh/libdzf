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

#ifndef __DZF_UTIL_H__
#define __DZF_UTIL_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>


/* -- Bool type -- */
#if __STDC_VERSION__ >= 199901L
/* if it supports c99 */
# define Bool     bool
# define TRUE     true
# define FALSE    false
#else
# define Bool     int
# define TRUE     1
# define FALSE    0
#endif


/* -- Public unit annotation -- */
#define __DZF_Public_Unit_Annotation__      /* Do nothing! */
#define __DZF_PUBLIC        __DZF_Public_Unit_Annotation__

/* -- Private unit annotation -- */
#define __DZF_Private_Unit_Annotation__     /* Do nothing! */
#define __DZF_PRIVATE       __DZF_Private_Unit_Annotation__

/* -- Deprecate unit annotation -- */
#define __DZF_Deprecate_Unit_Annotation__   /* Do nothing */
#define __DZF_DEPRECATE     __DZF_Deprecate_Unit_Annotation__


/* -- Debug message -- */
#ifdef DZF_DEBUG
# define    __dzf_dbugf(prefix, fmt, ...) \
                (void)fprintf(stderr, prefix " -- " fmt, __VA_ARGS__)
#else
# define    __dzf_dbugf(prefix, fmt, ...) ((void) 0)
#endif

#define __dzf_log_with_domain(domain, prefix, fmt, ...) \
    __dzf_dbugf("** DZF::" domain "::" prefix, fmt, __VA_ARGS__)
    
#define __dzf_strerr(_msg) \
    fprintf(stderr, _msg "\n")

#define __dzf_exit_with_err(_msg, _exitc) \
    ( __dzf_strerr("** DZF -- " _msg), exit(_exitc) )
/* -- End of debugging log -- */


/* Block-scope guard */
#define DZF_GUARD(_CODE) ;_CODE;


#define __dzf_realloc(_NPTR, _OLDPTR, _SIZE) \
    ( (_NPTR = realloc(_OLDPTR, _SIZE)) == NULL ? \
      __dzf_exit_with_err("Failed to allocate memory.", -1) : \
      ((void) 0) )


#define __dzf_malloc(_PTR, _SIZE) \
    __dzf_realloc(_PTR, NULL, _SIZE)


#define __dzf_cmp(_x, _y) \
    ( (_x == _y) ? TRUE : FALSE )


#define __dzf_sizeof(_ptr) \
    sizeof((_ptr)->data[0])


#endif
