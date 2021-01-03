# WikiSort

A GPL C library of sorting algorithms found on Wikipedia and a sorting algorithm visualizer.

## Available Sorting Algorithms

These tables list the implemented sorting algorithms and provide their time complexities and links to their corresponding Wikipedia pages.

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
| [Cartesian Tree Sort](https://en.wikipedia.org/wiki/Cartesian_tree) | O(nlogk) | O(nlogn) | O(n) |

### Insertion sorts
| Name | Worst | Average | Best |
| --- | --- | --- | --- |
| [Insertion sort](https://en.wikipedia.org/wiki/Insertion_sort) | =Average | O(n^2) comparisons and swaps | O(n) comparisons, O(1) swaps |
| [Shellsort](https://en.wikipedia.org/wiki/Shellsort) | O(n^2) worst known gaps, O(nlog^2n) best known gaps | depends on gaps | O(nlogn) |
| [Patience Sorting](https://en.wikipedia.org/wiki/Patience_sorting) | =Average | O(nlogn) | O(n) |
| [Tree sort](https://en.wikipedia.org/wiki/Tree_sort) | O(n^2) | =Best | O(nlogn) |
| [Splaysort](https://en.wikipedia.org/wiki/Splaysort) | =Average | O(nlogn) | O(n) |

### Merge sorts
| Name | Worst | Average | Best |
| --- | --- | --- | --- |
| [Merge sort](https://en.wikipedia.org/wiki/Merge_sort) | =Average | O(nlogn) | O(n)/O(nlogn) |

### Distribution sorts
| Name | Worst | Average | Best |
| --- | --- | --- | --- |
| [Radix sort](https://en.wikipedia.org/wiki/Radix_sort) | =Best | =Best | O(wn) |
| [Counting sort](https://en.wikipedia.org/wiki/Counting_sort) | =Best | =Best | O(n + k) |
| [Bucket sort](https://en.wikipedia.org/wiki/Bucket_sort) | O(nlogn) | Θ(n + k) | Ω(n + k) |
| [Pigeonhole sort](https://en.wikipedia.org/wiki/Pigeonhole_sort) | =Best | =Best | O(n + k) |

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
| [Pancake sorting](https://en.wikipedia.org/wiki/Pancake_sorting) | =Average | O(n^2) | O(n) |

## Implementation

A `void` pointer can't be dereferenced in C and the language doesn't allow arrays to contain arbitrary information. Instead, this implementation circumvents the problem by making it the responsibility of the caller to specify the relevant data type sizes. Arrays are stored as `void**`. A custom advancing function (`void** adv(void**, int)`) is used to access memory locations at any arbitrary distance from the beginning of the given memory location. Element comparison is delegated to a separate function, indicated with a function pointer. This can either be a predefined one from the library or it can be defined in the calling program. Together, these techniques mean that the memory is never accessed directly by the library, so no type information needs to be stored or specified, allowing arrays of any type to be sorted.

## Data

In the `data` folder in the repository's root, there are programs and spreadsheets that generate and contain data regarding the runtimes of sorting algorithms, respectively. This information is available for use under [CC BY-NC-SA 4.0](https://creativecommons.org/licenses/by-nc-sa/4.0/). The source code of those programs is still available under GPLv3. If you would like to have data regarding the runtime of sorting algorithms under your own terms, you may compile the test programs using the included Makefile and generate your own data.

## Compilation

Use the included `Makefile`s to compile the WikiSort library and the test programs. When compiling the library, you can define the variables `_32BITMODE` and `VISUALIZER` to enable 32 bit mode and visualization function calls, respectively. In 32 bit mode, pointers are advanced using `uint32_t` instead of `uint64_t`.

In `src/wikisort.h`, there are type definitions for function pointers that are called when swapping elements or advancing pointers. These are only compiled when visualizer mode is enabled. When creating a sorting algorithm visualizer or other program that needs to be notified when elements in a list are swapped, define `VISUALIZER` when calling `make` to enable these features. During linking, appropriate functions must be defined and set.

Refer to `examples/random.c` for an example of how this might be used.

## Visualizer

The repository also includes a visualizer for the sorting algorithms. The visualizer uses [ImGui](https://github.com/ocornut/imgui) for its interface. The visualizer output can also be recorded to video files (MPEG, `.mpg`) using the [OpenGL recorder library](https://github.com/Arc676/OpenGLRecorder) available under GPLv3. A Makefile to compile the visualizer is included in the folder; the submodules must also be cloned before compilation.

## Licensing

Project available under GPLv3. See `LICENSE` for full license text. ImGui is available under the MIT license.

Text obtained from Wikipedia (algorithm time complexities) available under [Creative Commons Attribution-ShareAlike 3.0](https://en.wikipedia.org/wiki/Wikipedia:Text_of_Creative_Commons_Attribution-ShareAlike_3.0_Unported_License) license.
