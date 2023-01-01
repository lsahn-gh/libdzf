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
#include <string.h>

static void stack_int_type(void);
static void stack_str_type(void);

void
stack_main(void)
{
    border("STACK INT TYPE");
    stack_int_type();

    border("STACK STRING TYPE");
    stack_str_type();
}


/* Test for string type with DYNAMIC_STACK */
#define DZF_STACK_DYNAMIC_GROW
#include <dzf/dzf-stack.h>

static void stack_str_print(char **str, ...);
static void stack_str_free_all(char **str, ...);

static void
stack_str_type(void)
{
    typedef dzf_stack_t(char *) stack_str_t;
    stack_str_t str;

    char buf[30];
    char *item;

    dzf_stack_new(&str, sizeof(char *));
    assert(dzf_stack_capacity(&str) == DZF_STACK_ALLOC_SIZE);
    assert(dzf_stack_is_empty(&str) == TRUE);
    assert(dzf_stack_is_full(&str) == FALSE);

    for (int i = 0; i < 40; i++) {
        char *tmp;
        size_t len = 0;

        snprintf(buf, 30, "stack str type %d", i);
        len = strlen(buf)+1;
        tmp = malloc(len * sizeof(char));
        memcpy(tmp, buf, len);

        dzf_stack_push(&str, tmp);
    }

    assert(dzf_stack_capacity(&str) == 64);
    assert(dzf_stack_size(&str) == 40);
    assert(dzf_stack_is_empty(&str) == FALSE);

    dzf_stack_foreach(&str, stack_str_print, NULL);

    item = dzf_stack_pop(&str);
    printf("Just popped from the stack: %s.\n", item);
    free(item); /* free the item. */

    assert(dzf_stack_size(&str) == 39);

    /* free all items from malloc'd above. */
    dzf_stack_foreach(&str, stack_str_free_all, NULL);
    /* free the stack. */
    dzf_stack_data_free(&str);
}

static void
stack_str_print(char **str, ...)
{
    printf("%s\n", *str);
}

static void
stack_str_free_all(char **str, ...)
{
    if (str == NULL || *str == NULL)
        return;

    free(*str);
    *str = NULL;
}


/* Test for int type */
static void stack_int_print(const int *, ...);

static void
stack_int_type(void)
{
    typedef dzf_stack_t(int) stack_int_t;
    stack_int_t stack;

    int temp;

    /* skt_int_t */
    dzf_stack_new(&stack, sizeof(int));
    assert(dzf_stack_size(&stack) == 0);
    assert(dzf_stack_capacity(&stack) == DZF_STACK_ALLOC_SIZE);

    dzf_stack_push(&stack, 8);
    dzf_stack_push(&stack, 100);
    dzf_stack_push(&stack, 1);
    dzf_stack_push(&stack, 3);
    dzf_stack_push(&stack, 4);

    assert(dzf_stack_size(&stack) == 5);
    assert(dzf_stack_pop(&stack) == 4);
    assert(dzf_stack_pop(&stack) == 3);
    assert(dzf_stack_size(&stack) == 3);

    dzf_stack_push(&stack, 4);
    dzf_stack_push(&stack, 4);
    dzf_stack_push(&stack, 4);
    dzf_stack_push(&stack, 4);
    dzf_stack_push(&stack, 4);
    assert(dzf_stack_size(&stack) == 8);

    temp = dzf_stack_pop(&stack);
    printf("A data that popped from stack : %d\n", temp);

    dzf_stack_push(&stack, 100);
    dzf_stack_push(&stack, 100);
    dzf_stack_push(&stack, 100);
    dzf_stack_push(&stack, 100);
    dzf_stack_push(&stack, 100);

    dzf_stack_push(&stack, 100);
    dzf_stack_push(&stack, 100);
    dzf_stack_push(&stack, 100);
    dzf_stack_push(&stack, 900);
    dzf_stack_push(&stack, 100);
    assert(dzf_stack_size(&stack) == 17);

    printf("%zd\n", dzf_stack_capacity(&stack));
    assert(dzf_stack_capacity(&stack) == 32);

    dzf_stack_foreach(&stack, stack_int_print, NULL);
    putchar('\n');

    temp = dzf_stack_pop(&stack);
    printf("A data that popped from stack : %d\n", temp);
    printf("Size of stack: %d\n", dzf_stack_size(&stack));

    dzf_stack_data_free(&stack);
    assert(stack.data == NULL);
}

static void
stack_int_print(const int *item, ...)
{
    printf("%d ", *item);
}
