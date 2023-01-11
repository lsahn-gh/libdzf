/* dzf-stack.h
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

/*! @file dzf-stack.h
 *
 * @brief Stack Type Structure.
 * 
 * Stack is an abstract data type that has a special characteristic.
 * LIFO, Last In First Out. Default capacity is '16' unless clarify
 * the size via initializer.
 * 
 * dzf_stack_t(T) provides two types,
 * - \b Static: never success on push once it is full.
 * - \b Dynamic: grow up to the 'current capacity * 2'[1] if full.
 * 
 * Default type is 'Dynamic' and use 'DZF_STACK_STATIC_SIZE' define to
 * build with static stack type. Please see '__dzf_stack_try_growing'.
 * 
 * [1]: grow multiplied by 2
 */

#ifndef DZF_STACK_H
#define DZF_STACK_H

#define DZF_STACK_USE_AS_PRIVATE
#include "dzf-stack-priv.h"


/*!
 * Initialize a dzf_stack_t(T) instance.
 * 
 * @param self: a stack instance of dzf_stack_t(T).
 * @param elem_size: each element size in byte unit.
 * @param capacity: number of elements in the stack.
 * @return 0 on success.
 */
DZF_PUBLIC
static inline int
dzf_stack_init(void *self,
               size_t elem_size, size_t capacity)
{
    __die(self);

    return __dzf_stack_init(self, elem_size, capacity);
}

/*!
 * Initialize a dzf_stack_t(T) instance with capacity, '16'.
 * 
 * @param self: an instance of dzf_stack_t(T).
 * @param elem_size: each element size in byte unit.
 * @return 0 on success.
 */
DZF_PUBLIC
static inline int
dzf_stack_new(void *self,
              size_t elem_size)
{
    __die(self);

    return __dzf_stack_init(self, elem_size, DZF_STACK_ALLOC_SIZE);
}

/*!
 * Free the data of dzf_stack_t(T).
 * Note that it doesn't free stack itself if from malloc.
 *
 * @param self: an instance of dzf_stack_t(T).
 * @return none
 */
DZF_PRIVATE
static inline void
dzf_stack_data_free(void *self)
{
    __die(self);

    __dzf_vec_data_free(self);
}

/*!
 * Free the data and dzf_stack_t(T) itself.
 * Note that it must be called the stack from malloc.
 *
 * @param self: an instance of dzf_stack_t(T).
 * @return none
 */
DZF_PUBLIC
static inline void
dzf_stack_free(void *self)
{
    __die(self);

    __dzf_vec_data_free(self);
    __dzf_stack_set_top(self, -1);
    free(self);
}

/*!
 * Get the size of current used buckets.
 *
 * @param self: an instance of dzf_stack_t(T).
 * @return the size of current used buckets.
 */
DZF_PUBLIC
static inline int
dzf_stack_size(void *self)
{
    __die(self);

    return __dzf_stack_size(self);
}

DZF_PUBLIC
static inline size_t
dzf_stack_alloc_size(void *self)
{
    __die(self);

    return __dzf_stack_alloc_size(self);
}

/*!
 * Get the capacity of dzf_stack_t(T).
 *
 * @param self: an instance of dzf_stack_t(T).
 * @return the current capacity.
 */
DZF_PUBLIC
static inline size_t
dzf_stack_capacity(void *self)
{
    __die(self);

    return __dzf_stack_alloc_size(self);
}

/*!
 * Is dzf_stack_t(T) full?
 *
 * @param self: an instance of dzf_stack_t(T).
 * @return TRUE if full, otherwise FALSE.
 */
DZF_PUBLIC
static inline Bool
dzf_stack_is_full(void *self)
{
    __die(self);

    return __dzf_stack_is_full(self);
}

/*!
 * Is dzf_stack_t(T) empty?
 *
 * @param self: an instance of dzf_stack_t(T).
 * @return TRUE if empty, otherwise FALSE.
 */
DZF_PUBLIC
static inline Bool
dzf_stack_is_empty(void *self)
{
    __die(self);

    return __dzf_stack_is_empty(self);
}

/*!
 * Push a new value to the top of dzf_stack_t(T).
 * 
 * @param self: an instance of dzf_stack_t(T).
 * @param val: a new value.
 * @return none
 */
DZF_PUBLIC
#define dzf_stack_push(self, val) \
    ( \
      __die(self), \
      __dzf_stack_push(self, val) \
    )

/*!
 * Pop a value from the top of dzf_stack_t(T).
 * 
 * @param self: an instance of dzf_stack_t(T).
 * @return a value popped from the stack.
 */
DZF_PUBLIC
#define dzf_stack_pop(self) \
    ( \
      __die(self), \
      __dzf_stack_pop(self) \
    )

/*!
 * Pop a value from the top of dzf_stack_t(T).
 *
 * Used in 'expression' of C language syntax.
 *
 * @param self: an instance of dzf_stack_t(T).
 * @return a value popped from the stack.
 */
DZF_PUBLIC
#define dzf_stack_pop_as_expr(self) \
    dzf_stack_pop(self)

/*!
 * Pop a value from the top of dzf_stack_t(T).
 *
 * Used in 'statement' of C language syntax.
 * 
 * @param self: an instance of dzf_stack_t(T).
 * @return a value popped from the stack.
 */
DZF_PUBLIC
#define dzf_stack_pop_as_stmt(self) \
    dzf_stack_pop(self);

/*!
 * Get a value from the top of dzf_stack_t(T).
 *
 * @param self: an instance of dzf_stack_t(T).
 * @return a value from the stack.
 */
DZF_PUBLIC
#define dzf_stack_peek(self) \
    ( \
      __die(self), \
      __dzf_stack_peek(self) \
    )

DZF_PUBLIC
#define dzf_stack_foreach(self, _fptr, ...) \
    for ( int i = 0; \
          i < __dzf_stack_size(self); \
          (_fptr)(&((self)->data[i]), __VA_ARGS__), ++i )
        
#endif /* DZF_STACK_H */
