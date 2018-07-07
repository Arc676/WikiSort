# WikiSort
A GPL C library of sorting algorithms found on Wikipedia

## Available Sorting Algorithms

This table provides links to the Wikipedia pages regarding each sorting algorithm as well as the time complexity of the algorithm.

When two cases have the same time complexity, this is indicated with `=[case]`.

| Name | Worst | Average | Best |
| --- | --- | --- | --- |
| [Merge sort](https://en.wikipedia.org/wiki/Merge_sort) | =Average | O(nlogn) | O(n)/O(nlogn) |
| [Bubble sort](https://en.wikipedia.org/wiki/Bubble_sort) | =Average | O(n^2) | O(n) |
| [Selection sort](https://en.wikipedia.org/wiki/Selection_sort) | =Best | =Best | O(n^2) comparisons, O(n) swaps |
| [Insertion sort](https://en.wikipedia.org/wiki/Insertion_sort) | =Average | O(n^2) comparisons and swaps | O(n) comparisons, O(1) swaps |
| [Quicksort](https://en.wikipedia.org/wiki/Quicksort) | O(n^2) | O(nlogn) | O(n)/O(nlogn) |
| [Shellsort](https://en.wikipedia.org/wiki/Shellsort) | O(n^2) worst known gaps, O(nlog^2n) best known gaps | depends on gaps | O(nlogn)
| [Odd-even sort](https://en.wikipedia.org/wiki/Odd%E2%80%93even_sort) | =Average | O(n^2) | O(n) |
| [Comb sort](https://en.wikipedia.org/wiki/Comb_sort) | O(n^2) | Θ(nlogn) | Ω(n^2/2^p) where p is the number of increments |

## Implementation

A `void` pointer can't be dereferenced in C and the language doesn't allow arrays to contain arbitrary information. Instead, this implementation circumvents the problem by making it the responsibility of the caller to specify the relevant data type sizes. Arrays are stored as `void**`. A custom advancing function (`void** adv(void**, size_t)`) is used to access memory locations at any arbitrary distance from the beginning of the given memory location. Element comparison is delegated to a separate function, indicated with a function pointer. This can either be a predefined one from the library or it can be defined in the calling program. Together, these techniques mean that the memory is never accessed directly by the library, so no type information needs to be stored or specified, allowing arrays of any type to be sorted.

## Licensing

Project available under GPLv3. See `LICENSE` for full license text.

Text obtained from Wikipedia (algorithm time complexities) available under [Creative Commons Attribution-ShareAlike 3.0](https://en.wikipedia.org/wiki/Wikipedia:Text_of_Creative_Commons_Attribution-ShareAlike_3.0_Unported_License) license.
