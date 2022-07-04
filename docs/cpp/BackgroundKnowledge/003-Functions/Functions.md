<a name="KGU7b"></a>
## Normal function
<a name="H0tvl"></a>
### Declaration
```cpp
// Before C++11
return_value function_name(para1, para2, ...);

// C++11 or newer
auto function_name(para1, para2, ...) -> return_value;
```
<a name="hBY0F"></a>
### Definition
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
<a name="egcST"></a>
### Calling
```cpp
receptor = function_name(para1, para2, ...);
```
<a name="dCCMh"></a>
## The `main` function
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
Return value of `main`:

| Value | Description |
| --- | --- |
| 0 | The program was successful |
| EXIT_SUCCESS | The program was successful (same as above). Defined in `<cstdlib>`. |
| EXIT_FAILURE | The program failed. Defined in `<cstdlib>`. |

## `inline` function

#### Declaration

```cpp
// Before C++11
inline return_value function_name(para1, para2, ...);

// C++11 or newer
inline auto function_name(para1, para2, ...) -> return_value;
```
#### Definition

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
## lambda function

### Definition

```cpp
auto function_name = [capture_list](para1, para2, ...) -> return_value {

    return ...;
}
```

In capture_list, `=` means parameters passed by **value**, `&` means that passed by **reference**. **Capture value **may entail parameter duplication occurred, if that is complicated data type will take much time to complete duplicating process. However, the cost of **capture reference **is much cheaper, thanks to reference machanism.

## Try / catch / exception

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

## Overloaded function

```cpp
#include <iostream>
using namespace std;

int operate (int a, int b)
{
  return (a*b);
}

double operate (double a, double b)
{
  return (a/b);
}

int main ()
{
  int x=5,y=2;
  double n=5.0,m=2.0;
  cout << operate (x,y) << '\n';
  cout << operate (n,m) << '\n';
  return 0;
}
```

## Function template

```cpp
#include <iostream>
using namespace std;

template <class T>
T sum (T a, T b)
{
  T result;
  result = a + b;
  return result;
}

int main () {
  int i=5, j=6, k;
  double f=2.0, g=0.5, h;
  k=sum<int>(i,j);
  h=sum<double>(f,g);
  cout << k << '\n';
  cout << h << '\n';
  return 0;
}
```

If `template`functions defined in specified header and cpp files, calling it in `main`or other functions will due to `undefined function`error.<br />The solution is write `tempalte`functions in header files only. Because when compiler seeks it in header files, compiler will ignore the function definition in cpp file, which means `undefined`.

```cpp
#include "l.h"

auto main() -> int
{
    std::string s = "1";
    double a = EQ::type_cast<double>(s);

    return EXIT_SUCCESS;
}
```

```cpp
#ifndef __L_H__
#define __L_H__

#include <iostream>
#include <boost/lexical_cast.hpp>

namespace EQ
{

template <typename Target, typename Source>
Target type_cast(const Source& source)
{
    Target res;
    try {
        res = boost::lexical_cast<Target>(source);
    }
    catch (const std::exception& e) {
        std::cout << "Cannot convert " << source << " from " << typeid(source).name() << " to " << typeid(res).name() << std::endl;
    }
    return res;
}

}
```

### Todo 可变参函数

The template parameters can not only include types introduced by class or typename, but can also include expressions of a particular type:

```cpp
#include <iostream>
using namespace std;

template <class T, int N>
T fixed_multiply (T val)
{
  return val * N;
}

int main() {
  std::cout << fixed_multiply<int,2>(10) << '\n';
  std::cout << fixed_multiply<int,3>(10) << '\n';
}
```

