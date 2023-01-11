/* dzf-queue.h
 *
 * MIT License
 *
 * Copyright (c) 2018-2023 Leesoo Ahn <lsahn@ooseel.net>
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
 * @brief Queue Type Structure.
 *
 * Queue is an abstract data type that has a special characteristic.
 * FIFO, First In First Out. Default capacity is '16' unless clarify
 * the size via initializer.
 *
 * dzf_queue_t(T) is based on circular queue type.
 */

#ifndef DZF_QUEUE_H
#define DZF_QUEUE_H

#define DZF_QUEUE_USE_AS_PRIVATE
#include "dzf-queue-priv.h"


/*!
 * Initialize a dzf_queue_t(T) instance.
 * 
 * @param self: an instance of dzf_queue_t(T).
 * @param elem_size: each element size in byte unit.
 * @param capacity: number of elements in the queue.
 * @return 0 on success.
 */
DZF_PUBLIC
static inline int
dzf_queue_init(void *self,
               size_t elem_size, size_t capacity)
{
    __die(self);

    return __dzf_queue_init(self, elem_size, capacity);
}

/*!
 * Initialize a dzf_queue_t(T) instance with capacity '16'.
 * 
 * @param self: an instance of dzf_queue_t(T).
 * @param elem_size: each element size in byte unit.
 * @return 0 on success.
 */
DZF_PUBLIC
static inline int
dzf_queue_new(void *self,
              size_t elem_size)
{
    __die(self);

    return __dzf_queue_init(self, elem_size, DZF_QUEUE_ALLOC_SIZE);
}

/*!
 * Free the data of dzf_queue_t(T).
 * Note that it doesn't free queue itself if from malloc.
 *
 * @param self: an instance of dzf_queue_t(T).
 * @return none
 */
DZF_PUBLIC
static inline void
dzf_queue_data_free(void *self)
{
    __die(self);

    __dzf_queue_data_free(self);
}

/*!
 * Free the data and dzf_queue_t(T) itself.
 * Note that the instance must be alloc'ed from malloc.
 *
 * @param self: an instance of dzf_queue_t(T).
 * @return none
 */
DZF_PUBLIC
static inline void
dzf_queue_free(void *self)
{
    __die(self);

    __dzf_queue_data_free(self);
    free(self);
}

/*!
 * Get the size of each element of dzf_queue_t(T).
 *
 * @param self: an instance of dzf_queue_t(T).
 * @return the size of each element.
 */
DZF_PUBLIC
static inline size_t
dzf_queue_elem_size(void *self)
{
    __die(self);

    return __dzf_queue_elem_size(self);
}

/*!
 * Get the capacity of dzf_queue_t(T).
 *
 * @param self: an instance of dzf_queue_t(T).
 * @return the current capacity.
 */
DZF_PUBLIC
static inline size_t
dzf_queue_capacity(void *self)
{
    __die(self);

    return __dzf_queue_capacity(self);
}

/*!
 * Get the 'front' value of dzf_queue_t(T).
 *
 * @param self: an instance of dzf_queue_t(T).
 * @return the current front value.
 */
DZF_PUBLIC
static inline int
dzf_queue_front(void *self)
{
    __die(self);

    return __dzf_queue_front(self);
}

/*!
 * Get the 'rear' value of dzf_queue_t(T).
 *
 * @param self: an instance of dzf_queue_t(T).
 * @return the current rear value.
 */
DZF_PUBLIC
static inline int
dzf_queue_rear(void *self)
{
    __die(self);

    return __dzf_queue_rear(self);
}

/*!
 * Is dzf_queue_t(T) full?
 *
 * @param self: an instance of dzf_queue_t(T).
 * @return TRUE if full, otherwise FALSE.
 */
DZF_PUBLIC
static inline Bool
dzf_queue_is_full(void *self)
{
    __die(self);

    return __dzf_queue_is_full(self);
}

/*!
 * Is dzf_queue_t(T) empty?
 *
 * @param self: an instance of dzf_queue_t(T).
 * @return TRUE if empty, otherwise FALSE.
 */
DZF_PUBLIC
static inline Bool
dzf_queue_is_empty(void *self)
{
    __die(self);

    return __dzf_queue_is_empty(self);
}

/*!
 * Enqueue a new value to the tail of dzf_queue_t(T).
 * 
 * @param self: an instance of dzf_queue_t(T).
 * @param val: a new value.
 * @return none
 */
DZF_PUBLIC
#define dzf_queue_enq(self, value) \
    ( \
      __die(self), \
      __die(!__dzf_queue_is_full(self)), \
      __dzf_queue_push_tail(self, value) \
    )

/*!
 * Dequeue a value from the head of dzf_queue_t(T).
 *
 * @param self: an instance of dzf_queue_t(T).
 * @return a value dequeued from the queue.
 */
DZF_PUBLIC
#define dzf_queue_deq(self) \
    ( \
      __die(self), \
      __die(!__dzf_queue_is_empty(self)), \
      __dzf_queue_pop_head(self) \
    )

#endif /* DZF_QUEUE_H */
