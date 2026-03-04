# DSC
A collection of data structures written in C. The code is written to be peformant, with algorithmic complexity guarantees. The data structures will store raw bytes, and it is up to user to manage proper conversions of data. They are intended for general use, and for storing any kind of data.

## Usage
| Command | Description |
|:---------: |:------------|
|`make all`|Will compile all source code and insert them into a newly created `build/` folder.|
|`make test`|Will compile all unit tests and dependencies, and then will run the tests.|
|`python run_tests.py`|Will simply run all existing compiled tests.|

You can find usage examples inside of the `examples/` folder, where it contains a sample code of how to use the data structures.

## Flags
These are only here for debugging purposes. Ideally, you shouldn't have any of these flags active when compiling the production/release code.
It supports three primary modes that can be set with `#define` preprocesing:
| Flag Name | Description |
|:---------: |:------------|
|`DSC_OVERFLOW_CHECK`| This adds logic into the code to check for overflow and overall bound correctness. It will not stop the code from running.|
|`DSC_OVERFLOW_STOP` | This will stop the program at runtime and call `exit()` if it detects any sort of overflow or invalid memory access. This will only work if `DSC_OVERFLOW_CHECK` is defined.|
|`DSC_OPTIMAL_CHECK` | This adds logic to issue warnings at runtime if one uses the non-optimal `O(N)` algorithms.|
|`DSC_OPTIMAL_STOP`  | This will stop the program at runtime and call `exit()` if any of the non-optimal `O(N)` methods are called. Only efficient `O(1)` and `O(log N)` will be allowed to be called.|
|`DSC_OPTIMAL_ONLY`  | This will erase from the interface any function that is not efficient to run. If you try to use them with this flag defined, they will not exist.|
|`DSC_DEBUG`    | This adds additional informative messages into the interface for easy debugging.|
|`DSC_INTERNAL_INFO` | This adds additional informative messages from internal code for easy debugging and development. (mostly for me).|

To use these flags, you will need to compile the library with them. For example:
```
gcc src/dynamic_array.c test/dynamic_array_debug.c -o bintest -Iinclude -DDSC_DEBUG -DDSC_OVERFLOW_CHECK -DDSC_OVERFLOW_STOP
```

## Array data structures
An array is a type of container that preserves the order in which you insert the data, and allows you to insert/delete from any position, and read/set from any position.

| Array Type| C++ Equivalent | Description |
|:---------: |:------------:|:----------|
|`static_array`|`std::array` |An array with no size changing mechanisms.|
|`dynamic_array`| `std::vector`| An array capable of dynamically change its size.|
|`bt_array`| None |An array whose implementation comes from a binary tree.|
|`single_linked_list`|`std::forward_list` | A single linked list. Stores a pointer for the beginning.|
|`doubly_linked_list`|`std::list` |A doubly linked list. stores a pointer for beginning and end.|


The arrays are meant to be performant, and therefore obeys the following algorithmic complexities:
| Array Type            | Read/Set Front | Read/Set Back | Read/Set At| Add/Delete Front | Add/Delete Back | Add/Delete At|
| :-------------------- | :--------:     | :-----------: |:----------:|:----------------:|:---------------:|:------------:|
| `static_array`        |   `O(1)`       | `O(1)`        | `O(1)`     |   `O(N)`         | `O(N)`          | `O(N)`       |
| `dynamic_array`       |   `O(1)`       | `O(1)`        | `O(1)`     |   `O(1)`         | `O(1) amortized`| `O(1)`       |
| `bt_array`            | `O(log N)`     | `O(log N)`    | `O(log N)` |   `O(log N)`     | `O(log N)`      | `O(log N)`   |
| `single_linked_list`  |  `O(1)`        | `O(N)`        | `O(N)`     |   `O(1)`         | `O(N)`          | `O(1)`       |
| `doubly_linked_list`  |  `O(1)`        | `O(1)`        | `O(N)`     |   `O(1)`         | `O(1)`          | `O(N)`       |

