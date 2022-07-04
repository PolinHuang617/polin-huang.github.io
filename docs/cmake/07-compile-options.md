```
.
├── CMakeLists.txt
├── LICENSE
└── src
    └── main.cpp
```

```cpp
// src/main.cpp
#include <iostream>

int main(void)
{
    auto data = 100;
    std::cout << "data: " << data << "\n";
    return 0;
}
```

```cmake
# Run `cmake ..` in build/ to avoid polluting project root dir
cmake_minimum_required (VERSION 2.8.12)

project (demo)

set (EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

set (SRC_LIST ${PROJECT_SOURCE_DIR}/src/main.cpp)

add_compile_options (-std=c++17 -Wall)

add_executable (main ${SRC_LIST})
```
