```
.
├── CMakeLists.txt
├── LICENSE
├── main.c
├── testFunc1.c
├── testFunc1.h
├── testFunc.c
└── testFunc.h
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


// testFunc.h
#ifndef _TEST_FUNC_H_
#define _TEST_FUNC_H_

void func(int data);

#endif


// testFunc.cpp
#include <stdio.h>
#include "testFunc.h"

void func(int data)
{
	printf("data is %d\n", data);
}


// testFunc1.h
#ifndef _TEST_FUNC1_H_
#define _TEST_FUNC1_H_

void func1(int data);

#endif


// testFunc1.cpp
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

# Method 1.
# add_executable (main main.c testFunc.c testFunc1.c)

# Method 2.
aux_source_directory (. SRC_LIST)
add_executable (main ${SRC_LIST})
```
