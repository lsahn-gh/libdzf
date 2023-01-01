/* test_vector.c
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

#include <dzf/dzf-vector.h>

#include <float.h>
#include <math.h>

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


static void
vector_string_type(void)
{
    typedef dzf_vec_t(char *) vec_str_t;
    vec_str_t str;

    dzf_vec_new(&str, sizeof(char*));
    assert(dzf_vec_get_capacity(&str) == 8);

    dzf_vec_add_tail(&str, "Hello World");
    assert(dzf_vec_get_length(&str) == 1);

    dzf_vec_add_tail(&str, "Hello World 2");
    dzf_vec_add_tail(&str, "Hello World 3");
    dzf_vec_add_tail(&str, "Hello World 4");
    dzf_vec_add_tail(&str, "Hello World 5");
    dzf_vec_add_tail(&str, "Hello World 6");
    assert(strcmp(dzf_vec_get_value_at(&str, 0), "Hello World") == 0);
    assert(strcmp(dzf_vec_get_value_at(&str, dzf_vec_get_length(&str)-1), "Hello World 6") == 0);

    dzf_vec_set_value(&str, dzf_vec_get_length(&str)-1, "This is not hell world");
    assert(strcmp(dzf_vec_get_value_at(&str, dzf_vec_get_length(&str)-1), "This is not hell world") == 0);

    dzf_vec_rmv_head(&str);
    assert(dzf_vec_get_length(&str) == 5);
    assert(strcmp(dzf_vec_get_value_at(&str, 0), "Hello World 2") == 0);
    
    dzf_vec_data_free(&str);
}


// Test for double type.
static void
vector_double_type(void)
{
    typedef dzf_vec_t(double) vec_double_t;
    vec_double_t dvec;
    double *elem;
    size_t i;

    dzf_vec_new(&dvec, sizeof(double));
    assert(dzf_vec_get_length(&dvec) == 0);
    assert(dzf_vec_get_capacity(&dvec) == 8);

    dzf_vec_add_tail(&dvec, 9.8);
    dzf_vec_add_tail(&dvec, 3.14);
    dzf_vec_add_tail(&dvec, 1.0);
    
    dzf_vec_for_each(elem, &dvec, i) {
        printf("%.2lf ", *elem);
    }
    putchar('\n');

    assert(dzf_vec_get_length(&dvec) == 3);

    dzf_vec_for_each(elem, &dvec, i) {
        *elem += 1.0;
    }
    assert(fabs(dzf_vec_get_value(&dvec, 0) - 10.8) < DBL_EPSILON);

    dzf_vec_for_each(elem, &dvec, i) {
        printf("%.2lf ", *elem);
    }
    putchar('\n');

    dzf_vec_data_free(&dvec);
}


// Test for user-defined struct type.
typedef struct {
    char *name;
    int age;
} user_t;

static void
vector_user_struct_type(void)
{
    typedef dzf_vec_t(user_t) vec_user_t;
    vec_user_t users;
    user_t *elem;
    size_t i;

    dzf_vec_new_with(&users, sizeof(vec_user_t), 32);
    assert(dzf_vec_get_capacity(&users) == 32);

    user_t jeremy = {
        "Jeremy", 28
    };

    dzf_vec_add_tail(&users, jeremy);

    dzf_vec_for_each(elem, &users, i) {
        printf("Name: %s, Age: %d\n", elem->name, elem->age);
    }

    user_t *temp = dzf_vec_get_ptr(&users, 0);
    temp->age = 10;

    user_t temp2 = dzf_vec_get_value(&users, 0);
    printf("Name: %s, Age: %d\n", temp2.name, temp2.age);

    dzf_vec_data_free(&users);
}
