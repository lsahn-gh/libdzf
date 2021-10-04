/* dzf-vector-priv.h
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

#ifndef DZF_VEC_PRIV_H
#define DZF_VEC_PRIV_H

#if !defined(DZF_VEC_USE_AS_PRIVATE)
#   error "Only <dzf/dzf-vector.h> can be included directly!"
#endif

#define DZF_BASE_USE_AS_PRIVATE
#include "dzf-base.h"
#undef  DZF_BASE_USE_AS_PRIVATE

/* -- Type Definition -- */
/*!
 * @def dzf_vec_t(T)
 * @brief Vector type
 *
 * @param T: type that represents an elem of 'data' array.
 *
 * \b Examples
 * @code{.c}
 *   typedef dzf_vec_t(int) vec_int_t;
 *   typedef dzf_vec_t(double) vec_double_t;
 *   typedef dzf_vec_t(char *) vec_str_t;
 * @endcode
 */
#define dzf_vec_t(T) \
    struct { \
        __dzf_base_t _unused1; \
        T *data; \
    }

typedef dzf_vec_t(char) __dzf_vec_priv_void_t;
#define DZF_VEC_VOID(self)   ((__dzf_vec_priv_void_t*)self)

#define DZF_VEC_ALLOC_SIZE 8 /* default capacity */


/* -- Private APIs -- */
DZF_PRIVATE
static inline int
__dzf_vec_set_length(void *self,
                     int length)
{
    return __dzf_base_set_length(self, length);
}


DZF_PRIVATE
static inline int
__dzf_vec_get_length(void *self)
{
    return __dzf_base_get_length(self);
}


DZF_PRIVATE
static inline size_t
__dzf_vec_set_alloc_size(void *self,
                         size_t new_size)
{
    return __dzf_base_set_capacity(self, new_size);
}


DZF_PRIVATE
static inline size_t
__dzf_vec_get_alloc_size(void *self)
{
    return __dzf_base_get_capacity(self);
}


DZF_PRIVATE
static inline size_t
__dzf_vec_set_elem_size(void *self,
                        size_t new_size)
{
    return __dzf_base_set_elem_size(self, new_size);
}


DZF_PRIVATE
static inline size_t
__dzf_vec_get_elem_size(void *self)
{
    return __dzf_base_get_elem_size(self);
}


DZF_PRIVATE
static inline Bool
__dzf_vec_index_validator(void *self,
                          int index)
{
    return (index >= 0 && index < __dzf_vec_get_length(self));
}


DZF_PRIVATE
static inline int
__dzf_vec_get_capacity(void *self)
{
    return __dzf_vec_get_alloc_size(self) - __dzf_vec_get_length(self);
}


DZF_PRIVATE
static inline Bool
__dzf_vec_is_full(void *self)
{
    return (__dzf_vec_get_alloc_size(self) == __dzf_vec_get_length(self));
}


DZF_PRIVATE
static inline Bool
__dzf_vec_is_empty(void *self)
{
    return (__dzf_vec_get_length(self) == 0);
}


DZF_PRIVATE
static inline int
__dzf_vec_try_growing(void *self)
{
    __dzf_vec_priv_void_t *vec = self;
    size_t new_alloc_size = 0;

    new_alloc_size = __dzf_vec_get_alloc_size(vec) * 2;
    vec->data = dzf_realloc(vec->data,
                            __dzf_vec_get_elem_size(vec) * new_alloc_size);
    __dzf_vec_set_alloc_size(vec, new_alloc_size);

    return new_alloc_size;
}


DZF_PRIVATE
static inline int
__dzf_vec_init(void *self,
               size_t elem_size, size_t capacity)
{
    __dzf_vec_priv_void_t *vec = self;

    if (capacity <= DZF_VEC_ALLOC_SIZE)
        capacity = DZF_VEC_ALLOC_SIZE;

    memset(vec, 0, sizeof(*vec));

    __dzf_base_init(vec, 0, capacity, elem_size);
    vec->data = dzf_malloc(elem_size * capacity);

    return 0;
}


DZF_PRIVATE
static inline void
__dzf_vec_data_free(void *self)
{
    __dzf_vec_priv_void_t *vec = self;

    if (vec->data != NULL) {
        free(vec->data);
        vec->data = NULL;
    }
    __dzf_base_init(vec, 0, 0, 0);
}


DZF_PRIVATE
static inline void *
__dzf_vec_get_pointer_at(void *self,
                         size_t index)
{
    __dzf_vec_priv_void_t *vec = self;

    return &(vec->data[index * __dzf_vec_get_elem_size(vec)]);
}


DZF_PRIVATE
#define __dzf_vec_get_value_at(self, _idx) \
    ((self)->data[_idx])


DZF_PRIVATE
#define __dzf_vec_set_value_at(self, _idx, _val) \
    ((self)->data[_idx] = _val)


DZF_PRIVATE
#define __dzf_vec_self_memmove(self, _idx, _direction) \
   memmove(__dzf_vec_get_pointer_at(self, _idx _direction), \
           __dzf_vec_get_pointer_at(self, _idx), \
           __dzf_vec_get_length(self) - _idx)


DZF_PRIVATE
#define __dzf_vec_insert_at(self, _idx, _val) \
    ( \
        __dzf_vec_is_full(self) ? __dzf_vec_try_growing(self) : 0, \
        ((_idx == __dzf_vec_get_length(self)) \
            ? NULL : __dzf_vec_self_memmove(self, _idx, __right_x(1))), \
        __dzf_vec_set_value_at(self, _idx, _val), \
        __dzf_vec_set_length(self, __dzf_vec_get_length(self)+1) \
    )


DZF_PRIVATE
#define __dzf_vec_remove_at(self, _idx) \
    ( \
        (_idx == __dzf_vec_get_length(self)) \
            ? NULL : __dzf_vec_self_memmove(self, _idx+1, __left_x(1)), \
        __dzf_vec_set_length(self, __dzf_vec_get_length(self)-1) \
    )

#endif /* DZF_VEC_PRIV_H */
