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

/*! @file dzf-queue.h
 *
 * @brief Queue data structure.
 * 
 * Queue is a data structure based on FIFO, also known as First In First Out.
 * 
 * dzf-queue is based on Circular Queue.
 */

#ifndef __DZF_QUEUE_H__
#define __DZF_QUEUE_H__

#if !defined (__LIBDZF_H_INCLUDE__)
#error "Only <dzf.h> can be included directly!"
#endif

#include "dzf-queue-priv.h"

#define DFLT_CAP 16


/*!
 * Initialize a queue with required capacity size.
 * 
 * @param _qptr: A pointer to the dzf_queue_t(T).
 * @param _cap_sze: Capacity.
 * @return None
 */
#define dzf_queue_new_with(_qptr, _cap_sze) \
    _dzf_queue_priv_init(_qptr, _cap_sze)


/*
 * Is dynamic circular queue necessary?
 * 
 * If so ...
 * It should be as follow, and need to
 * implement something more as Vector, or
 * Try it with Vector.
 * 
#define dzf_queue_new(_qptr) \
    _dzf_queue_priv_init(_qptr, DFLT_CAP)
 */


/*!
 * Free allocated memory to the data member.
 * 
 * @param _qptr: A pointer to the dzf_queue_t(T).
 * @return None
 */
#define dzf_queue_free(_qptr) \
    for ( free((_qptr)->data), \
          (_qptr)->data = NULL; \
          FALSE; )


/*!
 * Get capacity of the queue.
 * 
 * @param _qptr: A pointer to the dzf_queue_t(T).
 * @return \c int
 */
#define dzf_queue_cap(_qptr) \
    ((_qptr)->_cap)


/*!
 * Get current front index of the queue.  
 * It is used for implementing enqueue and dequeue.
 * 
 * @param _qptr: A pointer to the dzf_queue_t(T).
 * @return \c int
 */
#define dzf_queue_front(_qptr) \
    ((_qptr)->front)


/*!
 * Get current rear index of the queue.  
 * It is used for implementing enqueue and dequeue.
 * 
 * @param _qptr: A pointer to the dzf_queue_t(T).
 * @return \c int
 */
#define dzf_queue_rear(_qptr) \
    ((_qptr)->rear)


/*!
 * Check whether it is empty or not.
 * 
 * @param _qptr: A pointer to the dzf_queue_t(T).
 * @return TRUE if it is empty, or FALSE.
 */
#define dzf_queue_is_empty(_qptr) \
    ( dzf_queue_front(_qptr) == -1 ? TRUE : FALSE )


/*!
 * Check whether it is full or not.
 * 
 * @param _qptr: A pointer to the dzf_queue_t(T).
 * @return TRUE if it is full, or FALSE.
 */
#define dzf_queue_is_full(_qptr) \
    ( ((dzf_queue_rear(_qptr)+1) % dzf_queue_cap(_qptr)) == dzf_queue_front(_qptr) \
                                 ? TRUE : FALSE )


/*!
 * Enqueue a data at the current rear index of the queue.
 * 
 * @param _qptr: A pointer to the dzf_queue_t(T).
 * @param value: \c T typed value.
 * @return None
 */
#define dzf_queue_enq(_qptr, value) \
    for ( assert(dzf_queue_is_full(_qptr) == FALSE), \
          dzf_queue_rear(_qptr) = (dzf_queue_rear(_qptr)+1) % dzf_queue_cap(_qptr), \
          (_qptr)->data[dzf_queue_rear(_qptr)] = value, \
          (dzf_queue_front(_qptr) == -1 ? dzf_queue_front(_qptr) = 0 : 0); \
          FALSE; /* must be false not to loop. */ )
    

/*!
 * Dequeue a data at the current front of the queue.
 * 
 * @param _qptr: A pointer to the dzf_queue_t(T).
 * @param _var: A variable to hold the data.
 * @return None
 */
#define dzf_queue_deq(_qptr, _var) \
    for ( assert(dzf_queue_is_empty(_qptr) == FALSE), \
          _var = (_qptr)->data[dzf_queue_front(_qptr)], \
          ( dzf_queue_front(_qptr) == dzf_queue_rear(_qptr) \
            ? (dzf_queue_front(_qptr) = dzf_queue_rear(_qptr) = -1) \
            : (dzf_queue_front(_qptr) = (dzf_queue_front(_qptr)+1) % dzf_queue_cap(_qptr)) \
          ); \
          FALSE; )


/*!
 * Do something with the function through all elements.
 * 
 * @param _qptr: A pointer to the dzf_queue_t(T).
 * @param _fptr: A pointer to a function that will be called.
 * @param ...: Various arguments to be passed into the function.
 * @return None
 */
#define dzf_queue_foreach(_qptr, _fptr, ...) \
    for ( int i = dzf_queue_front(_qptr); \
          i == dzf_queue_rear(_qptr)+1 \
          ? FALSE : ( (_fptr)(&((_qptr)->data[i]), __VA_ARGS__), \
                      (i = (i+1) % dzf_queue_cap(_qptr)) ); \
        )


#endif
