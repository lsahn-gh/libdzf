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

#ifndef __DZF_OBJECT_H__
#define __DZF_OBJECT_H__

#if !defined (__LIBDZF_H_INCLUDE__)
#   error "Only <dzf.h> can be included directly"
#endif

typedef struct
{
    unsigned int magic;
} dzf_object_t;

#define OBJ_MAGIC   0x82AF0000

#define DZF_OBJECT(_ptr)        ((dzf_object_t*)(_ptr))

void
__dzf_obj_set_magic(dzf_object_t *obj,
                    unsigned int new_magic)
{
    obj->magic = new_magic;
}

#endif
