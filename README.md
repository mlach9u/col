
# Collection of libraries.

![C/C++ CI](https://github.com/mlach9u/col/workflows/C/C++%20CI/badge.svg?branch=master)

---

## Notice

These are in global namespace. To declare in other namespace, following this:

1. Include `inclusion_xxx.h` file in global namespace.
2. Include the main file in available namespace.

For example,

```cpp
#include "src\\stringt\\inclusion_stringt.h"
namespace something
{
#include "src\\stringt\\stringt.h"
}
```

If you use these in global namespace, you should not use `using namespace std;`.

## License

These are in the Public Domain.
