```
.
├── CMakeLists.txt
├── LICENSE
├── main.c
├── testFunc
│   ├── testFunc.c
│   └── testFunc.h
└── testFunc1
    ├── testFunc1.c
    └── testFunc1.h
```

```cpp
// main.cpp
#include <stdio.h>

#include "testFunc.h"
#include "testFunc1.h"

int main(void)
{
	func(100);
	func1(200);

	return 0;
}
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

```cpp
// testFunc1/testFunc1.h
#ifndef _TEST_FUNC1_H_
#define _TEST_FUNC1_H_

void func1(int data);

#endif


// testFunc1/testFunc1.cpp
#include <stdio.h>
#include "testFunc1.h"

void func1(int data)
{
	printf("data is %d\n", data);
}
```

```cmake
cmake_minimum_required (VERSION 2.8.12)

project (demo)

include_directories (testFunc testFunc1)

# 查找目录下所有源文件
aux_source_directory (testFunc SRC_LIST)
aux_source_directory (testFunc1 SRC_LIST1)

add_executable (main main.c ${SRC_LIST} ${SRC_LIST1})
```
