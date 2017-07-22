## Output debug stream(`cowl_debugout.h`)

---

### Purpose

- Defines debug streams and stream buffers.

### Defines debug streams and stream buffers

#### `basic_odebugsttream` and `basic_debugbuf`

These class templates implement output to DebugView application.

You can use these class templates via `<<` operator. Like this:

```cpp
basic_odebugstream< char > ds;
ds << "Last error is " << GetLastError() << std::endl;
```

### Limitation

- These class templates can be used on Windows operating system.
