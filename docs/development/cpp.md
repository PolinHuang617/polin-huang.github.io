---
title: C++ Notes
---

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

> [Reference](http://c.biancheng.net/cpp/biancheng/view/3297.html)

##### Implicit casting

```cpp
short a = 1;
int b = a;
```

##### Explicit casting

```cpp
auto b = (int*)a;
```

##### `static_cast`

1. Process conversion during **compiling**. If conversion failed, throw a compiling error. In runtime period, it doesn't incur type-safety check like `dynamic_cast`.

2. Mainly usage:
    - Built-in type conversion, e.g. `short` => `int`, `int` => `double`, etc.
    - Upcasting (pointer-to-derived => pointer-to-base).
    - `void*` => concrete pointer, e.g. `void*` => `int*`, `cahr*` => `void*`, etc.
    - Convert class with converting constructor and type-casting function.

3. Cannot convert:
    - No-related concrete **pointer**, e.g. `int*` => `double*`, because their storage structure in memory is totally different.
    - `int` and pointer, becuase a user-defined number seldom correctly mapping to a valid memory address.
	- convert `const` or `volatile` => `non-const` or `non-volatile` type.

    ```cpp
    #include <iostream>
    #include <cstdlib>
    using namespace std;

    class Complex {
    public:
        // 默认构造函数
        Complex(double real = 0.0, double imag = 0.0) 
		        : m_real(real), m_imag(imag) { }

        // 转换构造函数
        inline Complex(int num) { m_real = static_cast<double>(num); }

    public:
        //类型转换函数
        inline operator double() const { return m_real; }

    private:
        double m_real;
        double m_imag;
    };

    int main() {
        //下面是正确的用法
        int m = 100;
        Complex c(12.5, 23.8);
        long n = static_cast<long>(m);  //宽转换，没有信息丢失
        char ch = static_cast<char>(m);  //窄转换，可能会丢失信息

        //将void指针转换为具体类型指针
        int *p1 = static_cast<int*>( malloc(10 * sizeof(int)) );

        //将具体类型指针，转换为void指针
        void *p2 = static_cast<void*>(p1);
        double real= static_cast<double>(c);  //调用类型转换函数
        Complex c1 = static_cast<Complex>(m);

        //下面的用法是错误的
        //不能在两个具体类型的指针之间进行转换
        // float *p3 = static_cast<float*>(p1);

        //不能将整数转换为指针类型
        // p3 = static_cast<float*>(0X2DF9);
    
        return 0;
    }
    ```

##### `const_cast`

Convert `const` or `volatile` to `non-const` or `non-volatile`

```cpp
#include <iostream>
using namespace std;

int main() {
    const int n = 100;
    int *p = const_cast<int*>(&n);
    *p = 234;
    cout<<"n = "<<n<<endl;
    cout<<"*p = "<<*p<<endl;

    return 0;
}
```

##### `dynamic_cast`

1. `dynamic_cast<newType>(expr)` 

    `newType` and `expr` must be pointer or reference at the same time, meaning that `dynamic_cast` can only convert pointer or reference, instead of `int`, `double`, `class` or `struct`.

2. `dynamic_cast` is opposite with `static_cast`, the former processes type-safety check and conversion using RTTI during runtime.

3. `dynamic_cast` can achieve both upcasting and downcasting, but needs **base class contains virtual function**. After converted, program reaches variable function according to **virtual function table**.

4. Upcasting (Base <= Derived)

    Unconditionally succeed, because RTTI can always find effective base class for derived class in the inheritance chain. Type-safety check won't be triggered at this scenario, at which `dynamic_cast` is like `static_cast`.

    ```cpp
    #include <iostream>
    #include <iomanip>
    using namespace std;
    
    class Base{
    public:
        Base(int a = 0): m_a(a){ }
        int get_a() const{ return m_a; }
        virtual void func() const { }
    protected:
        int m_a;
    };
    
    class Derived: public Base{
    public:
        Derived(int a = 0, int b = 0): Base(a), m_b(b){ }
        int get_b() const { return m_b; }
    private:
        int m_b;
    };
    
    int main(){
        //情况1
        Derived *pd1 = new Derived(35, 78);
        Base *pb1 = dynamic_cast<Derived*>(pd1);
        cout<<"pd1 = "<<pd1<<", pb1 = "<<pb1<<endl;
        cout<<pb1->get_a()<<endl;
        pb1->func();
    
        //情况2
        int n = 100;
        Derived *pd2 = reinterpret_cast<Derived*>(&n);
        Base *pb2 = dynamic_cast<Base*>(pd2);
        cout<<"pd2 = "<<pd2<<", pb2 = "<<pb2<<endl;
        cout<<pb2->get_a()<<endl;  //输出一个垃圾值
        pb2->func();  //内存错误
    
        return 0;
    }
	```

5. Downcasting (Base => Derived)

    Program, according to inheritance chain, determins conversion successful or not.

    ```cpp
    #include <iostream>
    using namespace std;
    
    class A{
    public:
        virtual void func() const { cout<<"Class A"<<endl; }
    private:
        int m_a;
    };
    
    class B: public A{
    public:
        virtual void func() const { cout<<"Class B"<<endl; }
    private:
        int m_b;
    };
    
    class C: public B{
    public:
        virtual void func() const { cout<<"Class C"<<endl; }
    private:
        int m_c;
    };
    
    class D: public C{
    public:
        virtual void func() const { cout<<"Class D"<<endl; }
    private:
        int m_d;
    };
    
    int main(){
        A *pa = new A();
        B *pb;
        C *pc;
       
        //情况1
        pb = dynamic_cast<B*>(pa);  //向下转型失败
        if(pb == NULL){
            cout<<"Downcasting failed: A* to B*"<<endl;
        }else{
            cout<<"Downcasting successfully: A* to B*"<<endl;
            pb -> func();
        }
        pc = dynamic_cast<C*>(pa);  //向下转型失败
        if(pc == NULL){
            cout<<"Downcasting failed: A* to C*"<<endl;
        }else{
            cout<<"Downcasting successfully: A* to C*"<<endl;
            pc -> func();
        }
       
        cout<<"-------------------------"<<endl;
       
        //情况2
        pa = new D();  //向上转型都是允许的
        pb = dynamic_cast<B*>(pa);  //向下转型成功
        if(pb == NULL){
        cout<<"Downcasting failed: A* to B*"<<endl;
        }else{
            cout<<"Downcasting successfully: A* to B*"<<endl;
            pb -> func();
        }
        pc = dynamic_cast<C*>(pa);  //向下转型成功
        if(pc == NULL){
            cout<<"Downcasting failed: A* to C*"<<endl;
        }else{
            cout<<"Downcasting successfully: A* to C*"<<endl;
            pc -> func();
        }
       
        return 0;
    }
	```

	![Inheritance chain](cpp/inheritance_chain.jpg)

##### `reinterpret_cast`

As its name implies, **re-interpret** binary bits in memory, regardless of conversion rules for data, risking a lot.

`reinterpret_cast` is often as supplement of `static_cast` to force converting variables.

```cpp
#include <iostream>
using namespace std;

class A{
public:
    A(int a = 0, int b = 0): m_a(a), m_b(b){}
private:
    int m_a;
    int m_b;
};

int main(){
    //将 char* 转换为 float*
    char str[]="http://c.biancheng.net";
    float *p1 = reinterpret_cast<float*>(str);
    cout<<*p1<<endl;
    //将 int 转换为 int*
    int *p = reinterpret_cast<int*>(100);
    //将 A* 转换为 int*
    p = reinterpret_cast<int*>(new A(25, 96));
    cout<<*p<<endl;
   
    return 0;
}
```

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

#### Overloaded function
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

#### Function template

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

#### Non-type template arguments

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

### Pointer / Reference / Dynamic memory

#### Pointer & reference

``cpp
#include <iostream>
#include <cstdlib>

// swap using pointer
auto swap(int *a, int *b) -> void {
    auto c = *a;
    *a = *b;
    *b = c;
}

// swap using reference 
auto swap(int &a, int &b) -> void {
    auto c = a;
    a = b;
    b = c;
}

auto main(int argc, char **argv) -> int {
    try {
        auto a = 1, b = 2;
        auto *pa = &a, *pb = &b;
        swap(pa, pb);
        std::cout << a << "," << b << std::endl;

        swap(a, b);
        std::cout << a << "," << b << std::endl;

        return EXIT_SUCCESS;
    }
    catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    catch (...) {
        std::cerr << "Unkwon error." << std::endl;
        return EXIT_FAILURE;
    }
}
```

> `malloc`, `calloc`, `realloc` & `free` and `new` & `delete` apply memory blocks in **heap**.

- `malloc` & `calloc` & `realloc` & `free`

> [Reference](https://www.cnblogs.com/zzzsj/p/14428393.html)

```cpp
#include <iostream>
#include <cstdlib>
#include <cstring>

auto main(int argc, char **argv) -> int {
    try {
        int *p;
        // void* malloc(unsigned int size)
        // malloc apply a random memory block without initialization.
        p = static_cast<int*>( std::malloc(10 * sizeof(int)) );
        // it often use memset to initialize. But for data type other than
        // char, memset can only initialize with value 0 or -1, becuase it sets
        // memory by byte.
        std::memset(p, -1, 10 * sizeof(int));
        for (std::size_t i = 0; i < 10; ++i)
            std::cout << p[i] << " ";
        std::cout << std::endl;
        // Free this block after its work done.
        std::free(p);

	// void* calloc(std::size_t numOfElements, std::size_t sizeOfElement)
        // calloc apply a random memory block and initialize with value 0.
        p = static_cast<int*>( std::calloc(20, sizeof(int)) );
        for (std::size_t i = 0; i <= 20; ++i)
            std::cout << p[i] << " ";
        std::cout << std::endl;

        // void* realloc(void* ptr, std::size_t newSize)
        // realloc resize a applied block to new size.
        p = static_cast<int*>( std::realloc(p, 50 * sizeof(int)) );

        std::free(p);

        return EXIT_SUCCESS;
    }
    catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    catch (...) {
        std::cerr << "Unkwon error." << std::endl;
        return EXIT_FAILURE;
    }
}
```

- `new` & `delete`

```cpp
#include <cstdlib>

auto main(int argc, char **argv) -> int {
    try {
        int *p;
        p = new int[10];

        for (std::size_t i = 0; i < 10; ++i)
            std::cout << p[i] << " ";
        std::cout << std::endl;

        // delete p => array using delete[]
        delete[] p;

        // delete p => int using delete
        p = new int(9);
        delete p;

        return EXIT_SUCCESS;
    }
    catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    catch (...) {
        std::cerr << "Unkwon error." << std::endl;
        return EXIT_FAILURE;
    }
}
```

#### Pointer to function

```cpp
#include <iostream>
#include <cstdlib>

auto add(int a, int b) -> int { return a + b; }

auto sub(int a, int b) -> int { return a - b; }

auto operation(int x, int y, int (*callback)(int, int)) -> int {
    return (*callback)(x, y); 
}

auto main(int argc, char **argv) -> int {
    try {
        auto (*minus)(int, int) = sub;

        auto m = operation(7, 5, add);
        auto n = operation(20, m, minus);

        std::cout << n << std::endl;

        return EXIT_SUCCESS;
    }   
    catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }   
    catch (...) {
        std::cerr << "Unkwon error." << std::endl;
        return EXIT_FAILURE;
    }   
}
```

#### `unique_ptr`

`unique_ptr` has exclusive right to what it points to. **The right cannot be copied but only moved**. When it leaves its scope, it will be deleted automatically, by calling `operator delete`, which can be customized by user.

```cpp
#include <iostream>
#include <memory>

auto main(int argc, char **argv) -> int {
    try {
        std::unique_ptr<int> up(new int(100));
        // auto up1 = up;  // Cannot copy up, becuase it's unique.
        auto up2 = std::move(up);  // up can be moved to up2, 
                                   // but up will point to nothing, meaning
                                   // that up has no right to access to origin
                                   // memory any more.

        return EXIT_SUCCESS;
    }
    catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    catch (...) {
        std::cerr << "Unkwon error." << std::endl;
        return EXIT_FAILURE;
    }
}
```

#### `shared_ptr`

`shared_ptr` allows many to share the access right to the same memory, using **reference counting** to record how many pointers points to. Once the count comes back to 0, the pointed memory will be freed.

```cpp
#include <iostream>
#include <memory>

auto main(int argc, char **argv) -> int {
    try {
        std::shared_ptr<int> sp(new int(100));
        auto sp1 = sp;  // sp can be copied.

        auto sp2 = std::move(sp);  // sp can be moved, but it will lose its right.

        std::cout << sp1.use_count() << std::endl;
        std::cout << sp2.use_count() << std::endl;  // Output: 2

        sp1.reset();
        std::cout << sp2.use_count() << std::endl;  // Output: 1
        sp2.reset();
        std::cout << sp2.use_count() << std::endl;  // Output: 0

        return EXIT_SUCCESS;
    }
    catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    catch (...) {
        std::cerr << "Unkwon error." << std::endl;
        return EXIT_FAILURE;
    }
}
```

#### `weak_ptr`

`weak_ptr` is used to assist `shared_ptr`. It ponits to `shared_ptr`'s object but not increase reference count, which means `weak_ptr` does not own that memory. Use `lock` function can get a new `shared_ptr`. If their targeted object was freed, `nullptr` will return.

```cpp
#include <iostream>
#include <memory>

auto main(int argc, char **argv) -> int {
    try {
        std::shared_ptr<int> sp(new int(100));
        auto sp1 = sp;  // sp can be copied.

        std::cout << sp1.use_count() << std::endl;

        std::weak_ptr<int> wp = sp;
        std::weak_ptr<int> wp1 = sp;

        std::cout << sp1.use_count() << std::endl;  // Output: 2
        std::cout << wp.use_count() << std::endl;   // Output: 2
        std::cout << wp1.use_count() << std::endl;  // Output: 2

        auto checkWeakPtr = [&wp]() {
            // lock() returns a new shared_ptr points to origin target.
            auto tsp = wp.lock();
            if (tsp != nullptr)
                std::cout << tsp.use_count() << std::endl;  // Output: 3
            else
                std::cout << "weak ptr has been freed." << std::endl;
        };

        checkWeakPtr();

        sp1.reset();

        checkWeakPtr();

        return EXIT_SUCCESS;
    }
    catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    catch (...) {
        std::cerr << "Unkwon error." << std::endl;
        return EXIT_FAILURE;
    }
}
```

### Date

### File I/O

### Precompile commands

### Signals

### Class

### Multi-threading

### TCP / UDP / Web
