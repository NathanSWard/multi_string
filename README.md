# multi_string

#### Brief
- A `multi_string` is a memory efficient container for holding a constant *N* number of constant strings.

```cpp
int main() {
    multi_string str("hello ", "world", "!\n");
    for (auto&& s : str)
        std::cout << s;
}
```

#### Usecase
- In developing a NoSQL database (similar to that of MongoDB), I was implementing MongoDB-like compound indices. A compound index is a reference to *N* number of document fields, and each index must keep track of those field names. My initial approach was to use a `std::vector<std::string>` however, this would not be memory efficent as I know the number of fields by creation time. Also, each `std::string` would be in its own allocation (ignoring SBO), which is not necessary since the field names will not change.

#### Implementation Details
- Memory efficieny is achieved by placing all strings in a single allocation and keeping track of their locations.
- The allocated buffer has some metadata followed by the character array (omitting null terminators).
- The metadata has two different implementations:
  - `stores_ptrs::multi_string`
    - The metadata stores a pointer to the string within the character array. 
    - **benefit**: indexing into a `multi_string` is trivial as you simply index into the pointer array and then dereference the according pointer.
    - **drawback**: coppying a `multi_string` is not trivial as each new metadata pointer must be individually calculated.
  - `stores_sizes::multi_string`
    - The metadata stores each string's size.
    - **benefit**: coppying a `multi_string` is trivial as you can simply `memcpy` the buffer.
    - **draw back**: when indexing into the `multi_string`, the sizes of the strings must be accumulated to find the position in the followig buffer. 
