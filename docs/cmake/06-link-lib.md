```
.
├── CMakeLists.txt
├── LICENSE
├── src
│   └── main.c
└── testFunc
    ├── inc
    │   └── testFunc.h
    └── lib
        ├── libtestFunc.a
        └── libtestFunc.so
```

```cpp
// src/main.cpp
#include <stdio.h>

#include "testFunc.h"

int main(void)
{
	func(100);

	return 0;
}


// testFunc/inc/testFunc.h
#ifndef _TEST_FUNC_H_
#define _TEST_FUNC_H_

void func(int data);

#endif
```

```cmake
# Run `cmake ..` in build/ to avoid polluting project root dir
cmake_minimum_required (VERSION 2.8.12)

project (demo)

set (EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

set (SRC_LIST ${PROJECT_SOURCE_DIR}/src/main.c)

# Find testFunc.h
include_directories (${PROJECT_SOURCE_DIR}/testFunc/inc)

find_library (TESTFUNC_LIB testFunc HINTS ${PROJECT_SOURCE_DIR}/testFunc/lib)

add_executable (main ${SRC_LIST})

target_link_libraries (main ${TESTFUNC_LIB})
```
