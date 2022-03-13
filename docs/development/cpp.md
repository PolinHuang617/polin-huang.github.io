## C++ Notes

> [Mocrosoft C++ Reference](https://docs.microsoft.com/zh-cn/cpp/cpp/cpp-language-reference?view=msvc-170)

> [Cplusplus Reference](https://www.cplusplus.com/)

### Variables

#### Fundamental data types

<table>
<thead>
  <tr>
    <th>Group</th>
    <th colspan="2">Type names</th>
    <th colspan="2">Notes on size / Precision</th>
  </tr>
</thead>
<tbody>
  <tr>
    <td rowspan="4">Character types</td>
    <td colspan="2">char</td>
    <td colspan="2">Exactly one byte. At least 8 bits</td>
  </tr>
  <tr>
    <td colspan="2">char16_t</td>
    <td colspan="2">&gt; char. At least 16 bits</td>
  </tr>
  <tr>
    <td colspan="2">char32_t</td>
    <td colspan="2">&gt; char16_t. At least 32 bits</td>
  </tr>
  <tr>
    <td colspan="2">wchar_t</td>
    <td colspan="2">Can represent the largest supported char set</td>
  </tr>
  <tr>
    <td rowspan="5">Integer types signed</td>
    <td colspan="2">signed char</td>
    <td colspan="2">= char. At least 8 bits</td>
  </tr>
  <tr>
    <td colspan="2">signed short</td>
    <td colspan="2">&gt; char. At least 16 bits</td>
  </tr>
  <tr>
    <td colspan="2">signed int</td>
    <td colspan="2">&gt;= short. At 16 bits</td>
  </tr>
  <tr>
    <td colspan="2">signed long</td>
    <td colspan="2">&gt; int. At least 32 bits</td>
  </tr>
  <tr>
    <td colspan="2">signed long long</td>
    <td colspan="2">&gt; long. At least 64 bits</td>
  </tr>
  <tr>
    <td rowspan="5">Integer types unsigned</td>
    <td colspan="2">unsigned char</td>
    <td colspan="2" rowspan="5">Same size as their signed counterparts</td>
  </tr>
  <tr>
    <td colspan="2">unsigned short</td>
  </tr>
  <tr>
    <td colspan="2">unsigned int</td>
  </tr>
  <tr>
    <td colspan="2">unsigned long</td>
  </tr>
  <tr>
    <td colspan="2">unsigned long long</td>
  </tr>
  <tr>
    <td rowspan="3">Floating-point types</td>
    <td colspan="2">float</td>
    <td colspan="2"></td>
  </tr>
  <tr>
    <td colspan="2">double</td>
    <td colspan="2">Precision &gt; float</td>
  </tr>
  <tr>
    <td colspan="2">long double</td>
    <td colspan="2">Precision &gt; double</td>
  </tr>
  <tr>
    <td>Boolean types</td>
    <td colspan="2">bool</td>
    <td colspan="2"></td>
  </tr>
  <tr>
    <td>Void type</td>
    <td colspan="2">void</td>
    <td colspan="2">No storage</td>
  </tr>
  <tr>
    <td>Null pointer</td>
    <td colspan="2">decltype(nullptr)</td>
    <td colspan="2"></td>
  </tr>
</tbody>
</table>

#### Type deduction: `auto` and `decltype`

```cpp
#include <iostream>
#include <typeinfo>

int a = 0;
auto b = a; // same as: int b = a;

decltype(a) b; // same as: int b;

std::cout << typeif(a).name() << std::endl;
std::cout << typeif(b).name() << std::endl;
```

##### `auto` vs. `decltype`

`auto` discards qualified properties of variable, but `delctype` remains them. e.g.

```cpp
const int a = 1;
auto b = a;  // auto discards const property, and this is same as: int b = a;
decltype(a) c;  // delctype remains const property: const int c;
```

> `const` and `volatile` are antonym.

> `const` means variable is readonly.

> `volatile` means variable is easy to be changed, which means compiler will keep it in cpu register to optimize performance.

```cpp
int a = 10;
int &ra1 = a;

auto ra2 = ra1;
ra2 = 20;
// a: 10, ra1: 10, ra2: 20

decltype(ra) ra3 = 30;
// a: 30, ra1: 30, ra3: 30
```

For reference, `auto` still discards variable's qualified property, deducing variable type to its origin type (`int`). Butt `decltype` remains its reference property(`int &`).

#### Type conversion

##### Implicit casting

##### Explicit casting

##### `static_casti`

##### `dynamic_cast`

##### `const_cast`

##### `reinterpret_cast`

### Flow control

#### `condition ? expr1 : expr2`

```cpp
condition 
    ? expr1
    : expr2;
```

#### `if-else`

```cpp
if (condition0) {
    // code ...
}
else if (condition1){
    // code ...
}
else {
    // code ...
}
```

#### `switch`

```cpp
switch(enum_condition) {
    case enum0: {
        // code ...
        break;
    }
    case enum1:
    case enum2:
    case enum3: {
        // code ...
        break;
    }
    default:
        // code ...
        break;
}
```

#### `while`

```cpp
while(condition) {
    // code ...
}

do {

} while(condition);
```

#### `for`

```cpp
// Basic for loop
for (std::size_t i = 0; i < vec.size(); ++i) {
    // code ...
}

// iter can be changeable loop
for (auto iter  = vec.begin(); iter != vec.end(); ++iter) {
    // code ...
}

// iter is const
for (auto iter = vec.cbegin(); iter != vec.cend(); ++iter) {
    // code ...
}

// range for loop, changeable
for (auto &iter : vec) {
    iter = ...;
}

// ange for loop, unchangeable
for (const auto &iter : vec) {
    // readonly operation ...
}
```

### Functions

#### Normal function

- Declaration

```cpp
// Before C++11
return_value function_name(para1, para2, ...);

// C++11 or newer
auto function_name(para1, para2, ...) -> return_value;
```

- Definition

```cpp
// Before C++11
return_value function_name(para1, para2, ...) {
    // code ...

    return ...;
}

// C++11 or newer
auto function_name(para1, para2, ...) -> return_value {
    // code ...

    return ...;
}
```

- Call

```cpp
receptor = function_name(para1, para2, ...);
```

#### `main` function

The entry of program.

```cpp
// Before C++11
int main(int argv, char** argc) {

    return ...;
}

// C++11 or newer
auto main(int argv, char** argc) -> int {

    return ...;
}
```

About return value of `main`:

|     Value    | Description                                                         |
|:------------:|---------------------------------------------------------------------|
|       0      | The program was successful                                          |
| EXIT_SUCCESS | The program was successful (same as above). Defined in `<cstdlib>`. |
| EXIT_FAILURE | The program failed. Defined in `<cstdlib>`.                         |

#### `inline` function

- Declaration

```cpp
// Before C++11
inline return_value function_name(para1, para2, ...);

// C++11 or newer
inline auto function_name(para1, para2, ...) -> return_value;
```

- Definition

```cpp
// Before C++11
inline return_value function_name(para1, para2, ...) {

    return ...;
}

// C++11 or newer
inline auto function_name(para1, para2, ...) -> return_value {

    return ...;
}
```

#### lambda function

- Definition

```cpp
auto function_name = [capture_list](para1, para2, ...) -> return_value {

    return ...;
}
```

In capture_list, `=` means parameters passed by value, `&` means that passed by reference.

Capture value may entail parameter duplication occurred, when that is complicated data type will take much time to archive duplicating process.

The cost of capture reference is much cheaper, thanks of reference machanism.

### Try / Catch / Exception

```cpp
auto main(int argc, char **argv) -> int {
    try {
        // code ...
        throw std::exception("Built-in error type");
        // code ...
        throw customException("custom error type");

        return EXIT_SUCCESS;
    }
    catch(const std::exception &e) {
        LOG_ERROR(e.what());
        return EXIT_FAILURE;
    }
    catch(const customException &c) {
        LOG_ERROR(c.what());
        return EXIT_FAILURE;
    }
    catch(...) {
        LOG_ERROR("Unknown error type");
        return EXIT_FAILURE;
    }
}
```

### Overloads and Template

### Pointer / Reference / Dynamic memory

### Date

### File I/O

### Precompile commands

### Signals

### Class

### Multi-threading

### TCP / UDP / Web
