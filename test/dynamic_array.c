#include <dsc/dynamic_array.h>

void integer_tests() {
    {
        dsc_dynamic_array arr;
        dsc_dynamic_array_init(&arr, sizeof(int));
    }
}

int main() {
    integer_tests();
}
