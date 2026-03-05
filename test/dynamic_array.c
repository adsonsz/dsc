#include <dsc/dynamic_array.h>
#include <assert.h>
#include <stdio.h>

void integer_pushback() {
    dsc_dynamic_array arr;
    dsc_dynamic_array_init(&arr, sizeof(int));
    assert(arr.size == 0);
    assert(arr.item_size == sizeof(int));

    int a = 0;
    int b = 1;
    int c = 2;
    int d = 3;
    int e = 4;
    int f = 5;

    dsc_dynamic_array_push_back(&arr, &a);
    assert(arr.size == 1);

    dsc_dynamic_array_push_back(&arr, &b);
    assert(arr.size == 2);

    dsc_dynamic_array_push_back(&arr, &c);
    assert(arr.size == 3);

    dsc_dynamic_array_push_back(&arr, &d);
    assert(arr.size == 4);

    dsc_dynamic_array_push_back(&arr, &e);
    assert(arr.size == 5);

    dsc_dynamic_array_push_back(&arr, &f);
    assert(arr.size == 6);

    for (size_t i = 0; i < arr.size; i++) {
        int ii = (int)i;
        int* value = dsc_dynamic_array_at(&arr, i);
        assert(ii == *value);
    }

    dsc_dynamic_array_destroy(&arr);
    assert(arr.size == 0);
    assert(arr.capacity == 0);
}

void iterator_test() {
    dsc_dynamic_array array;
    dsc_dynamic_array_init(&array, sizeof(int));

    // Push back
    for (int i = 0; i < 10; ++i) {
        dsc_dynamic_array_push_back(&array, &i);
    };

    // Test values
    for (int i = 0; i < 10; ++i) {
        int* value = (int*)dsc_dynamic_array_at(&array, i);
        assert(*value == i);
    }

    // Test values using iterator
    int counter = 0;
    dsc_dynamic_array_iterator it = dsc_dynamic_array_iterator_begin(&array);
    for (; !dsc_dynamic_array_iterator_is_end(&array, &it); dsc_dynamic_array_iterator_next(&array, &it)) {
        int* value = (int*)it.pointer;
        printf("[%d] value=%d\n", counter, *value);
        assert(*value == counter);
        ++counter;
    }
}

int main() {
    integer_pushback();
    iterator_test();
}
