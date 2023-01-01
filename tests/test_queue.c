/* test_queue.c
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

#include "test.h"

#include <dzf/dzf-queue.h>

static void queue_int_type(void);
static void queue_func_ptr_type(void);

void
queue_main(void)
{
    border("QUEUE");
    queue_int_type();

    border("FUNCTION POINTER");
    queue_func_ptr_type();
}


/* Test for int type */
static void
queue_int_type(void)
{
    typedef dzf_queue_t(int) queue_int_t;
    queue_int_t queue;
    int i;

    dzf_queue_new(&queue, sizeof(int));
    assert(dzf_queue_capacity(&queue) == DZF_QUEUE_ALLOC_SIZE);
    assert(dzf_queue_elem_size(&queue) == sizeof(int));
    assert(dzf_queue_front(&queue) == -1);
    assert(dzf_queue_rear(&queue) == -1);

    for (i = 0; i < 100; i++) {
        dzf_queue_enq(&queue, i);
        (void)dzf_queue_deq(&queue);
    }
    assert(dzf_queue_front(&queue) == -1);
    assert(dzf_queue_rear(&queue) == -1);

    dzf_queue_enq(&queue, 4);
    dzf_queue_enq(&queue, 100);
    dzf_queue_enq(&queue, 200);
    assert(dzf_queue_rear(&queue) == 2);

    assert(dzf_queue_deq(&queue) == 4);
    assert(dzf_queue_deq(&queue) == 100);
    assert(dzf_queue_deq(&queue) == 200);

    for (i = 0; i < 100; i++) {
        if (!dzf_queue_is_full(&queue))
            dzf_queue_enq(&queue, i);
    }

    dzf_queue_data_free(&queue);
}


/* Test for function pointer type */
typedef void *(*pfunc)(void);

void *test(void) {
    return NULL;
}

static void
queue_func_ptr_type(void)
{
    typedef dzf_queue_t(pfunc) queue_pfn_t;
    queue_pfn_t queue;

    volatile pfunc tmp;

    dzf_queue_init(&queue, sizeof(pfunc), 32);
    assert(dzf_queue_capacity(&queue) == 32);
    assert(dzf_queue_elem_size(&queue) == sizeof(pfunc));
    assert(dzf_queue_front(&queue) == -1);
    assert(dzf_queue_rear(&queue) == -1);

    dzf_queue_enq(&queue, test);

    assert(dzf_queue_front(&queue) == 0);
    assert(dzf_queue_rear(&queue) == 0);

    tmp = dzf_queue_deq(&queue);

    if (tmp() == NULL) {    /* tmp is as test function */
        printf("tmp has been run.\n");
    }

    dzf_queue_data_free(&queue);
}
