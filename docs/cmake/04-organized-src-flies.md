```
.
├── CMakeLists.txt
├── include
│   ├── testFunc1.h
│   └── testFunc.h
├── LICENSE
└── src
    ├── main.c
    ├── testFunc1.c
    └── testFunc.c
```

```cpp
// include/testFunc.h
#ifndef _TEST_FUNC_H_
#define _TEST_FUNC_H_

void func(int data);

#endif


// include/testFunc1.h
#ifndef _TEST_FUNC_H_
#define _TEST_FUNC_H_

void func(int data);

#endif
```

```cpp
// src/main.cpp
#include <stdio.h>

#include "testFunc.h"
#include "testFunc1.h"

int main(void)
{
	func(100);
	func1(200);

	return 0;
}


// src/testFunc.cpp
#include <stdio.h>
#include "testFunc.h"

void func(int data)
{
	printf("data is %d\n", data);
}


// src/testFunc1.cpp
#include <stdio.h>
#include "testFunc1.h"

void func1(int data)
{
          printf("data is %d\n", data);
}
```

```cmake
# Run `cmake ..` in build/ to avoid polluting project root dir
cmake_minimum_required (VERSION 2.8.12)

project (demo)

include_directories (include)

aux_source_directory (src SRC_LIST)

set (EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

add_executable (main ${SRC_LIST})
```
