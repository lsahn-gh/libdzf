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

#include "test.h"
#include "dzf/dzf.h"

static void queue_print(const int *, ...);
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
    typedef dzf_queue_t(int) qint_t;
    qint_t queue;

    dzf_queue_new_with(&queue, 10);

    for (int i = 0; i < 100; i++) {
        int tmp;
        dzf_queue_enq(&queue, i);
        dzf_queue_deq(&queue, tmp);
        (void)tmp;  /* To avoid unused warning. */
    }

    assert(dzf_queue_front(&queue) == -1);

    dzf_queue_enq(&queue, 4);
    dzf_queue_enq(&queue, 100);
    dzf_queue_enq(&queue, 200);

    assert(dzf_queue_rear(&queue) == 2);

    dzf_queue_foreach(&queue, queue_print, NULL);
    putchar('\n');

    dzf_queue_free(&queue);
}

static void
queue_print(const int *item, ...)
{
    printf("%d ", *item);
}



/* Test for function pointer type */
typedef void *(*pfunc)(void);

void *test(void) {
    return NULL;
}

static void
queue_func_ptr_type(void)
{
    typedef dzf_queue_t(pfunc) qpfn_t;
    qpfn_t queue;

    pfunc tmp;

    dzf_queue_new_with(&queue, 5);

    assert(dzf_queue_front(&queue) == -1);
    assert(dzf_queue_rear(&queue) == -1);

    dzf_queue_enq(&queue, test);

    assert(dzf_queue_rear(&queue) == 0);

    dzf_queue_deq(&queue, tmp);

    if (tmp() == NULL) {    /* tmp is as test function */
        printf("tmp has been run.\n");
    }

    dzf_queue_free(&queue);
}
