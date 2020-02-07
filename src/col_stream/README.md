## Streams(`col_stream.h`)

---

### Purpose

1. Defines new streams and stream buffers.
2. Defines new stream manipulators.

### Defines new streams

#### `basic_ostream` and `basic_istream`

These are extended from `std::basic_ostream` and `std::basic_istream` and they're designed for some sequence overriding.

#### `basic_bostream` and `basic_bistream`, `basic_binarybuf` (`bstream.h`)

These class templates implement input, output operations on binary stream. This require stream buffer. If you want to set binary stream in memory, use `basic_binarybuf`. Like this:

```cpp
basic_binarybuf<char> bb;
basic_bostream<char> bo(&bb);
```

Also you can use other stream buffer. For example, `std::basic_filebuf`.

```cpp
std::basic_ofstream<char> of(filename);
basic_bostream<char> bo(of.rdbuf());
```

### Defines new stream manipulators

#### `bins` and `nobins`

1. Enables binary input, output stream.
2. Disables binary input, output stream.

You can use this manipulator with standard stream like this:

```cpp
std::cout << bins << (int)0x30313233 << nobins << std::endl;
// result : 3210
```
