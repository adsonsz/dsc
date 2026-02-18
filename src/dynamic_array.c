#include <stdlib.h>
#include <string.h>
#include <dynamic_array.h>

void dsc_dynamic_array_destroy(dsc_dynamic_array* array) {
    free(array->data);
    array->item_size = 0;
    array->size = 0;
    array->capacity = 0;
}

void dsc_dynamic_array_free(dsc_dynamic_array* array) {
    dsc_dynamic_array_destroy(array);
    free(array);
}

void dsc_dynamic_array_init(dsc_dynamic_array* array, size_t item_size) {
    array->data = NULL;
    array->item_size = item_size;
    array->size = 0;
    array->capacity = 0;
}

void dsc_dynamic_array_init_with_capacity(dsc_dynamic_array* array, size_t item_size, size_t capacity) {
    array->data = malloc(item_size * capacity);
    array->item_size = item_size;
    array->size = 0;
    array->capacity = capacity;
}

dsc_dynamic_array* dsc_dynamic_array_create(size_t item_size) {
    dsc_dynamic_array* result = malloc(sizeof(dsc_dynamic_array));
    dsc_dynamic_array_init(result, item_size);
    return result;
}

dsc_dynamic_array* dsc_dynamic_array_create_with_capacity(size_t item_size, size_t capacity) {
    dsc_dynamic_array* result = malloc(sizeof(dsc_dynamic_array));
    dsc_dynamic_array_init_with_capacity(result, item_size, capacity);
    return result;
}

void* dsc_dynamic_array_front(dsc_dynamic_array* array) {
    return (char*)array->data;
}

void* dsc_dynamic_array_back(dsc_dynamic_array* array) {
    return dsc_dynamic_array_at(array, array->size-1);
}

void* dsc_dynamic_array_at(dsc_dynamic_array* array, size_t index) {
    return (char*)array->data + index * array->item_size;
}

void dsc_dynamic_array_set_at(dsc_dynamic_array* array, size_t index, void* value) {
    memcpy(array->data + array->size * array->item_size, value, array->item_size);
}

bool dsc_dynamic_array_is_empty(dsc_dynamic_array* array) {
    return array->size == 0;
}

size_t dsc_dynamic_array_size(dsc_dynamic_array* array) {
    return array->size;
}

size_t dsc_dynamic_array_max_size(dsc_dynamic_array* array) {
    return array->capacity;
}

void dsc_dynamic_array_reserve(dsc_dynamic_array* array, size_t capacity) {
    void* new_data = realloc(array->data, capacity * array->item_size);
    array->data = new_data;
    array->capacity = capacity;
}

void dsc_dynamic_array_resize(dsc_dynamic_array* array, size_t size) {
    dsc_dynamic_array_reserve(array, size);
    array->size = size;
}

void dsc_dynamic_array_shrink_to_fit(dsc_dynamic_array* array) {

}

void dsc_dynamic_array_clear(dsc_dynamic_array* array) {
    dsc_dynamic_array_destroy(array);
}


void dsc_dynamic_array_push_back(dsc_dynamic_array* array, void* value) {
    // Allocate new memory if needed.
    if (array->size >= array->capacity) {
        size_t new_capacity = array->capacity == 0 ? 2 : array->capacity * 2;
        dsc_dynamic_array_reserve(array, new_capacity);
    }
    
    // Push back.
    dsc_dynamic_array_set_at(array, array->size, value);
    array->size += 1;
}

void dsc_dynamic_array_pop_back(dsc_dynamic_array* array) {
    array->size -= 1;

    // TODO: Deallocate memory if needed.
}
