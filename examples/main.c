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

/*! @file main.c
 *
 * @brief Test cases for APIs.
 * 
 * @details
 * Please take a look at source file, \b examples/main.c
 */

#include <assert.h>
#include "dzf/dzf.h"

#define border(...) printf("\n--------------" __VA_ARGS__ "---------------\n")

static void stack_test(void);
static void vector_test(void);
static void queue_test(void);


int
main(int argc, char **argv)
{
    border("STACK");
    stack_test();

    border("VECTOR");
    vector_test();

    border("QUEUE");
    queue_test();

    return 0;
}


static void
stack_test(void)
{
    typedef dzf_stack_t(int) stk_int_t;
    stk_int_t intstk;

    int temp;

    /* skt_int_t */
    dzf_stack_new_with(&intstk, 32);
    assert(dzf_stack_size(&intstk) == 0);
    // assert(dzf_stack_cap(&intstk) == 8);

    dzf_stack_push(&intstk, 8);
    dzf_stack_push(&intstk, 100);
    dzf_stack_push(&intstk, 1);
    dzf_stack_push(&intstk, 3);
    dzf_stack_push(&intstk, 4);

    assert(dzf_stack_size(&intstk) == 5);
    assert(dzf_stack_pop(&intstk) == 4);
    assert(dzf_stack_pop(&intstk) == 3);
    assert(dzf_stack_size(&intstk) == 3);

    dzf_stack_push(&intstk, 4);
    dzf_stack_push(&intstk, 4);
    dzf_stack_push(&intstk, 4);
    dzf_stack_push(&intstk, 4);
    dzf_stack_push(&intstk, 4);

    temp = dzf_stack_pop(&intstk);
    printf("A data that popped from stack : %d\n", temp);

    dzf_stack_push(&intstk, 100);
    dzf_stack_push(&intstk, 100);
    dzf_stack_push(&intstk, 100);
    dzf_stack_push(&intstk, 100);
    dzf_stack_push(&intstk, 100);
    // assert(dzf_stack_cap(&intstk) == 16);

    dzf_stack_push(&intstk, 100);
    dzf_stack_push(&intstk, 100);
    dzf_stack_push(&intstk, 100);
    dzf_stack_push(&intstk, 900);
    dzf_stack_push(&intstk, 100);
    assert(dzf_stack_cap(&intstk) == 32);

    void stack_print(const int *, ...);
    dzf_stack_foreach(&intstk, stack_print, NULL);
    putchar('\n');

    temp = dzf_stack_pop(&intstk);
    printf("A data that popped from stack : %d\n", temp);
    printf("Size of stack: %d\n", dzf_stack_size(&intstk));

    dzf_stack_free(&intstk);
    assert(intstk.data == NULL);
}

void
stack_print(const int *item, ...)
{
    printf("%d ", *item);
}



static void
vector_test(void)
{
    typedef dzf_vec_t(char *) vec_str_t;
    vec_str_t str;


    dzf_vec_new(&str);
    dzf_vec_add(&str, "Hello World");

    assert(dzf_vec_size(&str) == 1);
    assert(dzf_vec_cap(&str) == 8);

    void vec_print(char **, ...);
    dzf_vec_foreach(&str, vec_print, NULL);

    dzf_vec_add(&str, "Hello World 2");
    dzf_vec_add(&str, "Hello World 3");
    dzf_vec_add(&str, "Hello World 4");
    dzf_vec_add(&str, "Hello World 5");
    dzf_vec_add(&str, "Hello World 6");
    dzf_vec_add(&str, "Hello World 7");
    dzf_vec_add(&str, "Hello World 8");
    dzf_vec_add(&str, "Hello World 9");
    assert(strcmp(dzf_vec_at(&str, 0), "Hello World") == 0);

    dzf_vec_foreach(&str, vec_print, NULL);
    dzf_vec_set(&str, dzf_vec_size(&str)-1, "This is not hell world");

    printf("print element at %d: %s\n", 5, dzf_vec_at(&str, 5));

    dzf_vec_rmv(&str, 0);
    dzf_vec_foreach(&str, vec_print, NULL);
    assert(dzf_vec_size(&str) == 8);

    printf("print element at %d: %s\n", 5, dzf_vec_at(&str, 5));
    
    dzf_vec_free(&str);
}

void
vec_print(char **str, ...)
{
    printf("%s\n", *str);
}



static void
queue_test(void)
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

    void queue_print(const int *, ...);
    dzf_queue_foreach(&queue, queue_print, NULL);
    putchar('\n');

    dzf_queue_free(&queue);
}

void
queue_print(const int *item, ...)
{
    printf("%d ", *item);
}
