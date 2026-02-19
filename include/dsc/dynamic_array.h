#ifndef DSC_DYNAMIC_ARRAY_H
#define DSC_DYNAMIC_ARRAY_H
#include <stddef.h>

typedef struct dsc_dynamic_array {
    void* data;        // raw memory block.
    size_t item_size;  // size of each item (size of each item)
    size_t size;       // number of items (how many items it has)
    size_t capacity;   // allocated capacity (how many items it fits) 
} dsc_dynamic_array;

// Destructors. O(1)
void dsc_dynamic_array_destroy(dsc_dynamic_array* array);
void dsc_dynamic_array_free(dsc_dynamic_array* array);

// Constructors. O(size)
void dsc_dynamic_array_init(dsc_dynamic_array* array, size_t item_size);
void dsc_dynamic_array_init_with_capacity(dsc_dynamic_array* array, size_t item_size, size_t capacity);
dsc_dynamic_array* dsc_dynamic_array_create(size_t item_size);
dsc_dynamic_array* dsc_dynamic_array_create_with_capacity(size_t item_size, size_t capacity);

// Getters. O(1).
void* dsc_dynamic_array_front(dsc_dynamic_array* array);            // Get first item.
void* dsc_dynamic_array_back(dsc_dynamic_array* array);             // Get last item.
void* dsc_dynamic_array_at(dsc_dynamic_array* array, size_t index); // Get nth item.

// Setters. O(1).
void dsc_dynamic_array_set_at(dsc_dynamic_array* array, size_t index, void* value);

// Size. O(1).
bool dsc_dynamic_array_is_empty(dsc_dynamic_array* array);      // Check if it is empty.
size_t dsc_dynamic_array_size(dsc_dynamic_array* array);        // Get current size
size_t dsc_dynamic_array_max_size(dsc_dynamic_array* array);    // Get maximum size (capacity)

// Resize. O(size)
void dsc_dynamic_array_reserve(dsc_dynamic_array* array, size_t capacity);  // Alocate and do not initialize.
void dsc_dynamic_array_resize(dsc_dynamic_array* array, size_t size);       // Alocate and initialize.
void dsc_dynamic_array_shrink_to_fit(dsc_dynamic_array* array);             // Shrink capacity to fit array.

// Clear array.
void dsc_dynamic_array_clear(dsc_dynamic_array* array);

// Adding and deleting items at arbitrary position. O(N).
void dsc_dynamic_array_add_at(dsc_dynamic_array* array, size_t index, void* value);
void dsc_dynamic_array_delete_at(dsc_dynamic_array* array, size_t index);

// Adding and deleting items at the back. O(1) amortized.
void dsc_dynamic_array_push_back(dsc_dynamic_array* array, void* value);    // Add last item.
void dsc_dynamic_array_pop_back(dsc_dynamic_array* array);                  // Delete last item.

// Internal. Not intended for use. Data might be lost if misused.
// Change capacity by allocating or deallocating space. O(size).
void dsc_dynamic_array_change_capacity(dsc_dynamic_array* array, size_t capacity);

#endif
