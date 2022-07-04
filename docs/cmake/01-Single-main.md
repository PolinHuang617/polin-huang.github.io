```
.
├── CMakeLists.txt
├── LICENSE
└── main.c
```

```cpp
#include <cstdio>

int main(void) {
  printf("Hello World\n");

  return 0;
}
```

```cmake
cmake_minimum_required (VERSION 3.8)

project (demo)

add_executable (main main.cpp)
```
