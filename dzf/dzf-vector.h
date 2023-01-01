/* dzf-vector.h
 *
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

/*! @file dzf-vector.h
 *
 * @brief Vector Type Structure.
 *
 * Vector is an abstract data type that automatically grow its buckets size.
 * Default capacity is '8' unless clarify the size via initializer.
 *
 * dzf_vec_t(T) has the following characteristics,
 * - automatically grow its size up to the 'current size * 2'.
 *
 * Note that it doesn't shrink its size although it is empty.
 */

#ifndef DZF_VEC_H
#define DZF_VEC_H

#define DZF_VEC_USE_AS_PRIVATE
#include "dzf-vector-priv.h"


/*!
 * Initialize a vector.
 *
 * @param self: a vector instance of dzf_vec_t(T).
 * @param elem_size: each element size in byte unit.
 * @param capacity: number of elements in the vector.
 */
DZF_PUBLIC
static inline int
dzf_vec_new_with(void *self,
                 size_t elem_size, size_t capacity)
{
    __die(self);

    return __dzf_vec_init(self, elem_size, capacity);
}

/*!
 * Initialize a vector with default capacity, '8'.
 *
 * @param self: a vector instance of dzf_vec_t(T).
 * @param elem_size: each element size in byte unit.
 */
DZF_PUBLIC
static inline int
dzf_vec_new(void *self,
            size_t elem_size)
{
    __die(self);

    return __dzf_vec_init(self, elem_size, DZF_VEC_ALLOC_SIZE);
}

/*!
 * Free the data of dzf_vec_t(T).
 * Note that it doesn't free vector itself if from malloc.
 *
 * @param self: a vector instance of dzf_vec_t(T).
 */
DZF_PUBLIC
static inline void
dzf_vec_data_free(void *self)
{
    __die(self);

    __dzf_vec_data_free(self);
}

/*!
 * Free the data and dzf_vec_t(T) itself.
 * Note that it must be called the vector from malloc.
 *
 * @param self: a vector instance of dzf_vec_t(T).
 * @return none
 */
DZF_PUBLIC
static inline void
dzf_vec_free(void *self)
{
    __die(self);

    __dzf_vec_data_free(self);
    free(self);
}

/*!
 * Get the size of current used buckets.
 *
 * @param self: a vector instance of dzf_vec_t(T).
 * @return the size of current used buckets.
 */
DZF_PUBLIC
static inline int
dzf_vec_get_length(void *self)
{
    __die(self);

    return __dzf_vec_get_length(self);
}

/*!
 * Get the capacity of dzf_vec_t(T).
 *
 * @param self: a vector instance of dzf_vec_t(T).
 * @return the current capacity.
 */
DZF_PUBLIC
static inline int
dzf_vec_get_capacity(void *self)
{
    __die(self);

    return __dzf_vec_get_capacity(self);
}

/*!
 * Is dzf_vec_t(T) full?
 *
 * @param self: a vector instance of dzf_vec_t(T).
 * @return TRUE if full, otherwise FALSE.
 */
DZF_PUBLIC
static inline Bool
dzf_vec_is_full(void *self)
{
    __die(self);

    return __dzf_vec_is_full(self);
}

/*!
 * Is dzf_vec_t(T) empty?
 *
 * @param self: a vector instance of dzf_vec_t(T).
 * @return TRUE if empty, otherwise FALSE.
 */
DZF_PUBLIC
static inline Bool
dzf_vec_is_empty(void *self)
{
    __die(self);

    return __dzf_vec_is_empty(self);
}

/*!
 * Get a pointer at the elem of the index.
 *
 * @param self: a vector instance of dzf_vec_t(T).
 * @param index: an index to the elem.
 * @return a pointer to the elem of the index.
 */
DZF_PUBLIC
static inline void *
dzf_vec_get_ptr_at(void *self,
                   size_t index)
{
    __die(self);

    if (!__dzf_vec_index_validator(self, index))
        return NULL;

    return __dzf_vec_get_ptr_at(self, index);
}

/*!
 * Get a pointer at the elem of the index.
 *
 * @param self: a vector instance of dzf_vec_t(T).
 * @param index: an index to the elem.
 * @return a pointer to the elem of the index.
 */
DZF_PUBLIC
#define dzf_vec_get_ptr(self, _idx) \
    dzf_vec_get_ptr_at(self, _idx)

/*!
 * Set a new value to the elem of the index.
 *
 * @param self: a vector instance of dzf_vec_t(T).
 * @param _idx: an index to the elem.
 * @param _val: a new value.
 * @return none
 */
DZF_PUBLIC
#define dzf_vec_set_value(self, _idx, _val) \
    dzf_vec_set_value_at(self, _idx, _val)

/*!
 * Set a new value to the elem of the index.
 *
 * @param self: a vector instance of dzf_vec_t(T).
 * @param _idx: an index to the elem.
 * @param _val: a new value.
 * @return none
 */
DZF_PUBLIC
#define dzf_vec_set_value_at(self, _idx, _val) \
    ( __die(__dzf_vec_index_validator(self, _idx)), \
      __dzf_vec_set_value_at(self, _idx, _val) )

/*!
 * Get a value at the elem of the index.
 *
 * @param self: a vector instance of dzf_vec_t(T).
 * @param _idx: an index to the elem.
 * @return a value at the elem of the index.
 */
DZF_PUBLIC
#define dzf_vec_get_value(self, _idx) \
    dzf_vec_get_value_at(self, _idx)

/*!
 * Get a value at the elem of the index.
 *
 * @param self: a vector instance of dzf_vec_t(T).
 * @param _idx: an index to the elem.
 * @return a value at the elem of the index.
 */
DZF_PUBLIC
#define dzf_vec_get_value_at(self, _idx) \
    ( __die(__dzf_vec_index_validator(self, _idx)), \
      __dzf_vec_get_value_at(self, _idx) )

/*!
 * Add a new value at the index.
 *
 * Note that this is slow.
 *
 * @param self: a vector instance of dzf_vec_t(T).
 * @param _idx: an index to store the value.
 * @param _val: a new value.
 * @return none.
 */
DZF_PUBLIC
#define dzf_vec_add_at(self, _idx, _val) \
    ( assert(0 <= _idx && _idx <= __dzf_vec_get_alloc_size(self)), \
      __dzf_vec_insert_at(self, _idx, _val) )

/*!
 * Add a new value at the head of dzf_vec_t(T).
 *
 * Note that this is slow.
 *
 * @param self: a vector instance of dzf_vec_t(T).
 * @param _val: a new value.
 * @return none.
 */
DZF_PUBLIC
#define dzf_ved_add_head(self, val) \
    dzf_vec_add_at(self, 0, val)

/*!
 * Add a new value at the tail of dzf_vec_t(T).
 *
 * Note that this is faster than adding at the head.
 *
 * @param self: a vector instance of dzf_vec_t(T).
 * @param _val: a new value.
 * @return none.
 */
DZF_PUBLIC
#define dzf_vec_add_tail(self, val) \
    dzf_vec_add_at(self, __dzf_vec_get_length(self), val)

/*!
 * Remove a value at the index of dzf_vec_t(T).
 *
 * Note that this is slow.
 *
 * @param self: a vector instance of dzf_vec_t(T).
 * @param _val: a new value.
 * @return none.
 */
DZF_PUBLIC
#define dzf_vec_rmv_at(self, _idx) \
    ( __die(__dzf_vec_index_validator(self, _idx)), \
      __dzf_vec_remove_at(self, _idx) )

/*!
 * Remove a value at the head of dzf_vec_t(T).
 *
 * Note that this is slow.
 *
 * @param self: a vector instance of dzf_vec_t(T).
 * @return none.
 */
DZF_PUBLIC
#define dzf_vec_rmv_head(self) \
    dzf_vec_rmv_at(self, 0)

/*!
 * Remove a value at the tail of dzf_vec_t(T).
 *
 * Note that this is faster than removing at the head.
 *
 * @param self: a vector instance of dzf_vec_t(T).
 * @return none.
 */
DZF_PUBLIC
#define dzf_vec_rmv_tail(self) \
    dzf_vec_rmv_at(self, __dzf_vec_get_length(self)-1)

/*!
 * Walk through all elements in dzf_vec_t(T).
 *
 * @param elem: a pointer to the type of element of dzf_vec_t(T).
 * @param self: a vector instance of dzf_vec_t(T).
 * @param idx_var: an integer type variable.
 */
DZF_PUBLIC
#define dzf_vec_for_each(elem, self, idx_var) \
    for (idx_var = 0; \
         idx_var < __dzf_vec_get_length(self) && \
         ( elem = __dzf_vec_get_ptr_at(self, idx_var), 1 ); \
         idx_var++)

#endif /* DZF_VEC_H */
