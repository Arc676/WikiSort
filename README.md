# WikiSort
A GPL C library of sorting algorithms found on Wikipedia

## Available Sorting Algorithms

This table provides links to the Wikipedia pages regarding each sorting algorithm as well as the time complexity of the algorithm.

When two cases have the same time complexity, this is indicated with `=[case]`.

### Exchange sorts
| Name | Worst | Average | Best |
| --- | --- | --- | --- |
| [Bubble sort](https://en.wikipedia.org/wiki/Bubble_sort) | =Average | O(n^2) | O(n) |
| [Quicksort](https://en.wikipedia.org/wiki/Quicksort) | O(n^2) | O(nlogn) | O(n)/O(nlogn) |
| [Odd-even sort](https://en.wikipedia.org/wiki/Odd%E2%80%93even_sort) | =Average | O(n^2) | O(n) |
| [Comb sort](https://en.wikipedia.org/wiki/Comb_sort) | O(n^2) | Θ(nlogn) | Ω(n^2/2^p) where p is the number of increments |
| [Cocktail sort](https://en.wikipedia.org/wiki/Cocktail_shaker_sort) | =Average | O(n^2) | O(n) |
| [Gnome sort](https://en.wikipedia.org/wiki/Gnome_sort) | =Average | O(n^2) | Ω(n) |
| [Stooge sort](https://en.wikipedia.org/wiki/Stooge_sort) | =Best | =Best | O(n^log3/log1.5) = O(n^2.7095) |
| [Slowsort](https://en.wikipedia.org/wiki/Slowsort) | =Best | =Best | Ω(n^(logn / (2 + ε))) for ε > 0 |
| [Bogosort](https://en.wikipedia.org/wiki/Bogosort) | Unbounded (random), =Average (deterministic) | O((n + 1)!) | O(n) |

### Selection sorts
| Name | Worst | Average | Best |
| --- | --- | --- | --- |
| [Selection sort](https://en.wikipedia.org/wiki/Selection_sort) | =Best | =Best | O(n^2) comparisons, O(n) swaps |
| [Cycle sort](https://en.wikipedia.org/wiki/Cycle_sort) | =Best | =Best | Θ(n^2) |
| [Heapsort](https://en.wikipedia.org/wiki/Heapsort) | =Average | O(nlogn) | O(nlogn) (distinct keys); O(n) (equal keys) |

### Insertion sorts
| Name | Worst | Average | Best |
| --- | --- | --- | --- |
| [Insertion sort](https://en.wikipedia.org/wiki/Insertion_sort) | =Average | O(n^2) comparisons and swaps | O(n) comparisons, O(1) swaps |
| [Shellsort](https://en.wikipedia.org/wiki/Shellsort) | O(n^2) worst known gaps, O(nlog^2n) best known gaps | depends on gaps | O(nlogn)

### Merge sorts
| Name | Worst | Average | Best |
| --- | --- | --- | --- |
| [Merge sort](https://en.wikipedia.org/wiki/Merge_sort) | =Average | O(nlogn) | O(n)/O(nlogn) |

### Distribution sorts
| Name | Worst | Average | Best |
| --- | --- | --- | --- |

### Concurrent sorts
| Name | Worst | Average | Best |
| --- | --- | --- | --- |

### Hybrid sorts
| Name | Worst | Average | Best |
| --- | --- | --- | --- |
| [Introsort](https://en.wikipedia.org/wiki/Introsort) | =Best | =Best | O(nlogn) |
| [Timsort](https://en.wikipedia.org/wiki/Timsort) | =Average | O(nlogn) | O(n) |

### Other
| Name | Worst | Average | Best |
| --- | --- | --- | --- |

## Implementation

A `void` pointer can't be dereferenced in C and the language doesn't allow arrays to contain arbitrary information. Instead, this implementation circumvents the problem by making it the responsibility of the caller to specify the relevant data type sizes. Arrays are stored as `void**`. A custom advancing function (`void** adv(void**, int)`) is used to access memory locations at any arbitrary distance from the beginning of the given memory location. Element comparison is delegated to a separate function, indicated with a function pointer. This can either be a predefined one from the library or it can be defined in the calling program. Together, these techniques mean that the memory is never accessed directly by the library, so no type information needs to be stored or specified, allowing arrays of any type to be sorted.

## Data

In the `data` folder in the repository's root, there are programs and spreadsheets that generate and contain data regarding the runtimes of sorting algorithms, respectively. This information is available for use under [CC BY-NC-SA 4.0](https://creativecommons.org/licenses/by-nc-sa/4.0/). The source code of those programs is still available under GPLv3. If you would like to have data regarding the runtime of sorting algorithms under your own terms, you may compile the test programs using the included Makefile and generate your own data.

## Licensing

Project available under GPLv3. See `LICENSE` for full license text.

Text obtained from Wikipedia (algorithm time complexities) available under [Creative Commons Attribution-ShareAlike 3.0](https://en.wikipedia.org/wiki/Wikipedia:Text_of_Creative_Commons_Attribution-ShareAlike_3.0_Unported_License) license.
