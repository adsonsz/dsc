#include <stdio.h>
#include <stdlib.h>
#include <dsc/dynamic_array.h>

struct custom {
    int x;
    float y;
};

void example_ints() {
    dsc_dynamic_array arr;
    dsc_dynamic_array_init(&arr, sizeof(int));

    int a = 2;
    int b = 5;

    dsc_dynamic_array_push_back(&arr, &a);
    dsc_dynamic_array_push_back(&arr, &b);

    for (size_t i = 0; i < arr.size; i++) {
        int* value = dsc_dynamic_array_at(&arr, i);
        printf("%d\n", *value);
    }

    dsc_dynamic_array_destroy(&arr);
}

void example_structs() {
    dsc_dynamic_array arr;
    dsc_dynamic_array_init(&arr, sizeof(struct custom));

    struct custom c1 = {1, 1.5f};
    struct custom c2 = {2, 2.5f};

    dsc_dynamic_array_push_back(&arr, &c1);
    dsc_dynamic_array_push_back(&arr, &c2);

    for (size_t i = 0; i < arr.size; i++) {
        struct custom* c = dsc_dynamic_array_at(&arr, i);
        printf("x=%d y=%.2f\n", c->x, c->y);
    }

    dsc_dynamic_array_destroy(&arr);
}

void example_struct_pointers() {
    dsc_dynamic_array arr;
    dsc_dynamic_array_init(&arr, sizeof(struct custom*));

    struct custom* c1 = malloc(sizeof(struct custom));
    struct custom* c2 = malloc(sizeof(struct custom));

    c1->x = 10; c1->y = 10.5f;
    c2->x = 20; c2->y = 20.5f;

    dsc_dynamic_array_push_back(&arr, &c1);
    dsc_dynamic_array_push_back(&arr, &c2);

    for (size_t i = 0; i < arr.size; i++) {
        struct custom** ptr = dsc_dynamic_array_at(&arr, i);
        struct custom* c = *ptr;
        printf("x=%d y=%.2f\n", c->x, c->y);
    }

    // Free memory.
    free(c1);
    free(c2);
    dsc_dynamic_array_destroy(&arr);
}

int main() {
    example_ints();
    example_structs();
    example_struct_pointers();
}
