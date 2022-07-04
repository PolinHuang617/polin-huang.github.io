```
.
├── CMakeLists.txt
├── LICENSE
└── testFunc
    ├── testFunc.c
    └── testFunc.h
```

```cpp
// testFunc/testFunc.h
#ifndef _TEST_FUNC_H_
#define _TEST_FUNC_H_

void func(int data);

#endif


// testFunc/testFunc.cpp
#include <stdio.h>
#include "testFunc.h"

void func(int data)
{
        printf("data is %d\n", data);
}
```

```cmake
# Run `cmake ..` in build/ to avoid polluting project root dir
cmake_minimum_required (VERSION 2.8.12)

project (demo)

set (SRC_LIST ${PROJECT_SOURCE_DIR}/testFunc/testFunc.c)

add_library (testFunc_shared SHARED ${SRC_LIST})
add_library (testFunc_static STATIC ${SRC_LIST})

set_target_properties (testFunc_shared PROPERTIES OUTPUT_NAME "testFunc")
set_target_properties (testFunc_static PROPERTIES OUTPUT_NAME "testFunc")

set (LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
```
