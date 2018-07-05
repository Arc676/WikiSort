# WikiSort
A GPL C library of sorting algorithms found on Wikipedia

## Available Sorting Algorithms

This table provides links to the Wikipedia pages regarding each sorting algorithm as well as the time complexity of the algorithm.

| Name | Worst | Average | Best |
| --- | --- | --- | --- |
| [Merge sort](https://en.wikipedia.org/wiki/Merge_sort) | O(nlogn) | O(nlogn) | O(n)/O(nlogn) |
| [Bubble sort](https://en.wikipedia.org/wiki/Bubble_sort) | O(n^2) | O(n^2) | O(n) |

## Implementation

A `void` pointer can't be dereferenced in C and the language doesn't allow arrays to contain arbitrary information. Instead, this implementation circumvents the problem by making it the responsibility of the caller to specify the relevant data type sizes. Arrays are stored as `void**`. A custom advancing function (`void** adv(void**, size_t)`) is used to access memory locations at any arbitrary distance from the beginning of the given memory location. Element comparison is delegated to a separate function, indicated with a function pointer. This can either be a predefined one from the library or it can be defined in the calling program. Together, these techniques mean that the memory is never accessed directly by the library, so no type information needs to be stored or specified, allowing arrays of any type to be sorted.

## Licensing

Project available under GPLv3. See `LICENSE` for full license text.
