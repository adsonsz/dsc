#include <stdlib.h>
#include <string.h>
#include <dsc/dynamic_array.h>
#include <stdio.h>

void dsc_dynamic_array_destroy(dsc_dynamic_array* array) {
    #ifdef DSC_DEBUG
    printf("%s(array=%p\n", __func__, (void*)array);
    #endif
    
    free(array->data);
    dsc_dynamic_array_init(array, 0);
}

void dsc_dynamic_array_free(dsc_dynamic_array* array) {
    #ifdef DSC_DEBUG
    printf("%s(array=%p\n", __func__, (void*)array);
    #endif

    free(array->data);
    free(array);
}

void dsc_dynamic_array_init(dsc_dynamic_array* array, size_t item_size) {
    #ifdef DSC_DEBUG
    printf("%s(array=%p, item_size=%ld)\n", __func__, (void*)array, item_size);
    #endif

    array->data = NULL;
    array->item_size = item_size;
    array->size = 0;
    array->capacity = 0;
}

void dsc_dynamic_array_init_with_capacity(dsc_dynamic_array* array, size_t item_size, size_t capacity) {
    #ifdef DSC_DEBUG
    printf(
        "%s(array=%p, item_size=%ld, capacity=%ld)\n", __func__, 
        (void*)array, item_size, capacity
    );
    #endif

    array->data = malloc(item_size * capacity);
    array->item_size = item_size;
    array->size = 0;
    array->capacity = capacity;
}

dsc_dynamic_array* dsc_dynamic_array_create(size_t item_size) {
    #ifdef DSC_DEBUG
    printf("%s(item_size=%ld)\n", __func__, item_size);
    #endif

    dsc_dynamic_array* result = malloc(sizeof(dsc_dynamic_array));
    dsc_dynamic_array_init(result, item_size);
    return result;
}

dsc_dynamic_array* dsc_dynamic_array_create_with_capacity(size_t item_size, size_t capacity) {
    #ifdef DSC_DEBUG
    printf("%s(item_size=%ld, capacity=%ld)\n", __func__, item_size, capacity);
    #endif

    dsc_dynamic_array* result = malloc(sizeof(dsc_dynamic_array));
    dsc_dynamic_array_init_with_capacity(result, item_size, capacity);
    return result;
}

void* dsc_dynamic_array_front(dsc_dynamic_array* array) {
    #ifdef DSC_DEBUG
    printf("%s(array=%p)\n", __func__, (void*)array);
    #endif

    #ifdef DSC_OVERFLOW_CHECK
    if (array->size == 0) {
        fprintf(stderr, 
            "Overflow in dsc_dynamic_array. [array=%p]\n" 
            "Tried to read index=%ld whose array has size=%ld\n",
        (void*)array, index, array->size);

        #ifdef DSC_OVERFLOW_STOP
        exit(1);
        #endif
    }
    #endif

    return (char*)array->data;
}

void* dsc_dynamic_array_back(dsc_dynamic_array* array) {
    #ifdef DSC_DEBUG
    printf("%s(array=%p)\n", __func__, (void*)array);
    #endif

    #ifdef DSC_OVERFLOW_CHECK
    if (array->size == 0) {
        fprintf(stderr, 
            "Overflow in dsc_dynamic_array. [array=%p]\n" 
            "Tried to read index=%ld whose array has size=%ld\n",
        (void*)array, index, array->size);

        #ifdef DSC_OVERFLOW_STOP
        exit(1);
        #endif
    }
    #endif

    return dsc_dynamic_array_at(array, array->size-1);
}

void* dsc_dynamic_array_at(dsc_dynamic_array* array, size_t index) {
    #ifdef DSC_DEBUG
    printf("%s(array=%p, index=%ld)\n", __func__, (void*)array, index);
    #endif

    #ifdef DSC_OVERFLOW_CHECK
    if (index >= array->size) {
        fprintf(stderr, 
            "Overflow in dsc_dynamic_array. [array=%p]\n" 
            "Tried to read index=%ld whose array has size=%ld\n",
        (void*)array, index, array->size);

        #ifdef DSC_OVERFLOW_STOP
        exit(1);
        #endif
    }
    #endif

    return (char*)array->data + index * array->item_size;
}

void dsc_dynamic_array_set_at(dsc_dynamic_array* array, size_t index, void* value) {
    #ifdef DSC_DEBUG
    printf("%s(array=%p, index=%ld)\n", __func__, (void*)array, index);
    #endif

    #ifdef DSC_OVERFLOW_CHECK
    if (index >= array->size) {
        fprintf(stderr, 
            "Overflow in dsc_dynamic_array. [array=%p]\n" 
            "Tried to write index=%ld whose array has size=%ld\n",
        (void*)array, index, array->size);

        #ifdef DSC_OVERFLOW_STOP
        exit(1);
        #endif
    }
    #endif

    memcpy((char*)array->data + index * array->item_size, value, array->item_size);
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
    #ifdef DSC_DEBUG
    printf("%s(array=%p, capacity=%ld)\n", __func__, (void*)array, capacity);
    #endif

    if (capacity > array->capacity) dsc_dynamic_array_change_capacity(array, capacity);
}

void dsc_dynamic_array_resize(dsc_dynamic_array* array, size_t size) {
    #ifdef DSC_DEBUG
    printf("%s(array=%p, size=%ld)\n", __func__, (void*)array, size);
    #endif

    dsc_dynamic_array_reserve(array, size);
    array->size = size;
}

void dsc_dynamic_array_shrink_to_fit(dsc_dynamic_array* array) {
    #ifdef DSC_DEBUG
    printf("%s(array=%p)\n", __func__, (void*)array);
    #endif

    dsc_dynamic_array_change_capacity(array, array->size);
}

void dsc_dynamic_array_clear(dsc_dynamic_array* array) {
    #ifdef DSC_DEBUG
    printf("%s(array=%p)\n", __func__, (void*)array);
    #endif

    dsc_dynamic_array_destroy(array);
}

void dsc_dynamic_array_push_back(dsc_dynamic_array* array, void* value) {
    #ifdef DSC_DEBUG
    printf("%s(array=%p)\n", __func__, (void*)array);
    #endif
    
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
    #ifdef DSC_DEBUG
    printf("%s(array=%p)\n", __func__, (void*)array);
    #endif

    array->size -= 1;

    // Deallocate memory if needed.
    if (array->size < array->capacity/4) {
        size_t new_capacity = array->capacity / 2;
        if (new_capacity % 2) new_capacity++;
        dsc_dynamic_array_change_capacity(array, new_capacity);
    }
}

void dsc_dynamic_array_change_capacity(dsc_dynamic_array* array, size_t capacity) {
    #ifdef DSC_DEBUG
    printf("%s(array=%p, capacity=%ld)\n", __func__, (void*)array, capacity);
    #endif

    void* new_data = realloc(array->data, capacity * array->item_size);
    array->data = new_data;
    array->capacity = capacity;
}

void dsc_dynamic_array_iterator_next(dsc_dynamic_array* array, dsc_dynamic_array_iterator* it) {
    char* p = (char*)it->pointer;
    p += array->item_size;
    it->pointer = (void*)p;
}

dsc_dynamic_array_iterator* dsc_dynamic_array_iterator_begin(dsc_dynamic_array* array) {
    dsc_dynamic_array_iterator* it = malloc(sizeof(dsc_dynamic_array_iterator));
    it->pointer = array->data;
    return it;
}

bool dsc_dynamic_array_iterator_is_end(dsc_dynamic_array* array, dsc_dynamic_array_iterator* it) {
    return (char*)it->pointer == (char*)array->data + array->item_size * array->size;
}

bool dsc_dynamic_array_iterator_is_equal(dsc_dynamic_array_iterator* it, dsc_dynamic_array_iterator* other){ 
    return it->pointer == other->pointer;
}
