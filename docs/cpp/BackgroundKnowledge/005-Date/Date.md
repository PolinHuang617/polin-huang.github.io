C++ used `<ctime>` to instantial time-relatived function, which is `tm` and `time_t`.

## `struct tm`

```cpp
struct tm {
  int tm_sec;   // 秒，正常范围从 0 到 59，但允许至 61
  int tm_min;   // 分，范围从 0 到 59
  int tm_hour;  // 小时，范围从 0 到 23
  int tm_mday;  // 一月中的第几天，范围从 1 到 31
  int tm_mon;   // 月，范围从 0 到 11
  int tm_year;  // 自 1900 年起的年数
  int tm_wday;  // 一周中的第几天，范围从 0 到 6，从星期日算起
  int tm_yday;  // 一年中的第几天，范围从 0 到 365，从 1 月 1 日算起
  int tm_isdst; // 夏令时
};
```

## `time_t`

```cpp
#include <iostream>
#include <ctime>

auto main(int argc, char **argv) -> int {
    try {
        // time based on current system clock
        std::time_t now = std::time(0);

        // convert time_t => char*
        char* time_string = std::ctime(&now);

        std::cout << "Local time: " << time_string << std::endl;

        std::tm *gmTime = std::gmtime(&now);

        time_string = std::asctime(gmTime);

        std::cout << "UTC time: " << time_string << std::endl;

        std::cout << "date(" << gmTime->tm_zone << "): "
                  << (1900 + gmTime->tm_year) << "-" << (1 + gmT
ime->tm_mon) << "-" << gmTime->tm_mday
                  << std::endl;

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
