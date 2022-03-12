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
int a = 0;
auto b = a; // same as: int b = a;

decltype(a) b; // same as: int b;
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

### Condition

### Loops

### Functions

### Try / Catch / Exception

### Pointer / Reference / Dynamic memory

### Date

### File I/O

### template

### Precompile commands

### Signals

### Class

### Multi-threading

### TCP / UDP / Web
