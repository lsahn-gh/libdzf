/*
 * MIT License
 *
 * Copyright (c) 2021 Leesoo Ahn <lsahn@ooseel.net>
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

#ifndef __DZF_QUEUE_PRIV_H__
#define __DZF_QUEUE_PRIV_H__

#if !defined (__LIBDZF_H_INCLUDE__)
# error "Only <dzf/dzf.h> can be included directly!"
#endif

#include "dzf-util.h"
/* -- Type Definition -- */
/*!
 * @def dzf_queue_t
 * @brief Queue type.
 *
 * @param T: A type that you want to hold.
 *
 * \b Examples
 * @code{.c}
 *   // Let's build three types.
 *   typedef dzf_queue_t(long) q_long_t;
 *   typedef dzf_queue_t(int *) q_iptr_t;
 *   typedef dzf_queue_t(char *) q_str_t;
 * @endcode
 */
#define dzf_queue_t(T) \
    struct { int front; int rear; int _cap; T *data; }

typedef dzf_queue_t(void)       __dzf_queue_priv_void_t;
#define DZF_QUEUE_VOID(_qptr)   ((__dzf_queue_priv_void_t*)_qptr)


/* -- Define something else -- */
#define _dzf_q_log(prefix, fmt, ...) \
    __dzf_log_with_domain("QUEUE", prefix, fmt, __VA_ARGS__)


/* -- Private APIs -- */
/*
 * Attempt to allocate memory as much as size of T multiplies by capacity.
 *
 * @param _qptr: A pointer to the dzf_queue_t(T).
 * @param _qcap: Capacity.
 * @return None
 */
DZF_PRIVATE
#define _dzf_queue_priv_init(_qptr, _qcap) \
    do { \
        __dzf_malloc((_qptr)->data, __dzf_sizeof(_qptr) * _qcap); \
        _dzf_q_log("MALLOC", "Required size: %zd bytes.\n", \
                   __dzf_sizeof(_qptr) * _qcap); \
        dzf_queue_front(_qptr) = -1; \
        dzf_queue_rear(_qptr) = -1; \
        dzf_queue_cap(_qptr) = _qcap; \
    } while(FALSE)


#endif
