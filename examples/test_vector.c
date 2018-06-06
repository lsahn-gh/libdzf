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

static void vector_string_type(void);
static void vector_double_type(void);
static void vector_user_struct_type(void);

void
vector_main(void)
{
    border("VECTOR STRING TYPE");
    vector_string_type();

    border("VECTOR DOUBLE TYPE");
    vector_double_type();

    border("VECTOR USER DEFINED STRUCT TYPE");
    vector_user_struct_type();
}


// Test for string type.
static void vector_string_print(char **str, ...);

static void
vector_string_type(void)
{
    typedef dzf_vec_t(char *) vec_str_t;
    vec_str_t str;


    dzf_vec_new(&str);
    dzf_vec_add(&str, "Hello World");

    assert(dzf_vec_size(&str) == 1);
    assert(dzf_vec_cap(&str) == 8);

    dzf_vec_foreach(&str, vector_string_print, NULL);

    dzf_vec_add(&str, "Hello World 2");
    dzf_vec_add(&str, "Hello World 3");
    dzf_vec_add(&str, "Hello World 4");
    dzf_vec_add(&str, "Hello World 5");
    dzf_vec_add(&str, "Hello World 6");
    assert(strcmp(dzf_vec_get_val_at(&str, 0), "Hello World") == 0);

    dzf_vec_foreach(&str, vector_string_print, NULL);
    dzf_vec_set(&str, dzf_vec_size(&str)-1, "This is not hell world");

    printf("print element at %d: %s\n", 5, dzf_vec_get_val_at(&str, 5));

    dzf_vec_rmv(&str, 0);
    dzf_vec_foreach(&str, vector_string_print, NULL);
    assert(dzf_vec_size(&str) == 5);

    printf("print element at %d: %s\n", 5, dzf_vec_get_val_at(&str, 4));
    
    dzf_vec_free(&str);
}

static void
vector_string_print(char **str, ...)
{
    printf("%s\n", *str);
}


// Test for double type.
static void vector_double_plus(double *item, ...);
static void vector_double_print(double *item, ...);

static void
vector_double_type(void)
{
    typedef dzf_vec_t(double) vec_double_t;
    vec_double_t dvec;

    dzf_vec_new(&dvec);
    assert(dzf_vec_size(&dvec) == 0);
    assert(dzf_vec_cap(&dvec) == 8);

    dzf_vec_add(&dvec, 9.8);
    dzf_vec_add(&dvec, 3.14);
    dzf_vec_add(&dvec, 1.0);
    
    dzf_vec_foreach(&dvec, vector_double_print, NULL);
    putchar('\n');

    assert(dzf_vec_size(&dvec) == 3);

    dzf_vec_foreach(&dvec, vector_double_plus, NULL);
    assert(dzf_vec_get_val_at(&dvec, 0) == 10.8);

    dzf_vec_foreach(&dvec, vector_double_print, NULL);
    putchar('\n');


    dzf_vec_free(&dvec);
}

static void
vector_double_plus(double *item, ...)
{
    *item += 1.0;
}

static void
vector_double_print(double *item, ...)
{
    printf("%lf ", *item);
}


// Test for user-defined struct type.
typedef struct {
    char *name;
    int age;
} user_t;

static void vector_user_struct_print(user_t *, ...);

static void
vector_user_struct_type(void)
{
    typedef dzf_vec_t(user_t) vec_user_t;
    vec_user_t users;

    dzf_vec_new_with(&users, 32);
    assert(dzf_vec_cap(&users) == 32);

    user_t jeremy = {
        "Jeremy", 28
    };

    dzf_vec_add(&users, jeremy);

    dzf_vec_foreach(&users, vector_user_struct_print, NULL);

    user_t *temp = dzf_vec_get_ptr_at(&users, 0);
    temp->age = 10;

    user_t temp2 = dzf_vec_get_val_at(&users, 0);
    printf("Name : %s, Age : %d\n", temp2.name, temp2.age);


    dzf_vec_free(&users);
}

static void
vector_user_struct_print(user_t *item, ...)
{
    printf("Name : %s, Age : %d\n", item->name, item->age);
}
