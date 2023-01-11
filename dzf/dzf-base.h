/* dzf-base.h
 *
 * MIT License
 *
 * Copyright (c) 2021-2023 Leesoo Ahn <lsahn@ooseel.net>
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

#ifndef DZF_BASE_H
#define DZF_BASE_H

#if !defined(DZF_BASE_USE_AS_PRIVATE)
#   error "Not allowed to include dzf-base.h directly!"
#endif

#include "dzf-util.h"

typedef struct __dzf_base {
    int length;
    size_t alloc_size;
    size_t elem_size;
} __dzf_base_t;

#define DZF_GET_BASE(self) ((__dzf_base_t*)self)

DZF_PRIVATE
static inline int
__dzf_base_set_length(void *self,
                      int length)
{
    return (DZF_GET_BASE(self)->length = length, length);
}

DZF_PRIVATE
static inline int
__dzf_base_get_length(void *self)
{
    return DZF_GET_BASE(self)->length;
}

DZF_PRIVATE
static inline size_t
__dzf_base_set_alloc_size(void *self,
                          size_t new_size)
{
    return (DZF_GET_BASE(self)->alloc_size = new_size, new_size);
}
#define __dzf_base_set_capacity __dzf_base_set_alloc_size

DZF_PRIVATE
static inline size_t
__dzf_base_get_alloc_size(void *self)
{
    return DZF_GET_BASE(self)->alloc_size;
}
#define __dzf_base_get_capacity __dzf_base_get_alloc_size

DZF_PRIVATE
static inline size_t
__dzf_base_set_elem_size(void *self,
                         size_t new_size)
{
    return (DZF_GET_BASE(self)->elem_size = new_size, new_size);
}

DZF_PRIVATE
static inline size_t
__dzf_base_get_elem_size(void *self)
{
    return DZF_GET_BASE(self)->elem_size;
}

DZF_PRIVATE
static inline void
__dzf_base_init(void *self,
                int length, size_t capacity, size_t elem_size)
{
    __dzf_base_set_length(self, length);
    __dzf_base_set_capacity(self, capacity);
    __dzf_base_set_elem_size(self, elem_size);
}

#endif /* DZF_BASE_H */
