## Pointer & reference

```cpp
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

## Dynamic memory

`malloc`, `calloc`, `realloc` & `free` and `new` & `delete` apply memory blocks in heap.

### `malloc`, `calloc`, `realloc` & `free`
[memset()](https://www.cnblogs.com/zzzsj/p/14428393.html)

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

### `new`, `delete`

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

## Pointer to function

```cpp
#include <iostream>
#include <cstdlib>

auto add(int a, int b) -> int { return a + b; }

auto sub(int a, int b) -> int { return a - b; }

auto operation(int x, int y, int (*callback)(int, int)) -> int {    return (*callback)(x, y);
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

## `unique_ptr`

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

## `shared_ptr`

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

## `weak_ptr`

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


