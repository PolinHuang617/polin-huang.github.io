| Signal | Description |
| --- | --- |
| SIGABRT | 程序异常终止, abort |
| SIGFPE | 错误的算术运算，比如除以零或导致溢出的动作 |
| SIGILL | 检测非法指令 |
| SIGINT | 程序终止(Interrupt)信号 |
| SIGSEGV | 非法访问内存 |
| SIGTERM | 发送到程序的终止请求 |

## `void signal(registed signal, signal handler)`
If your program needs to capture system signals, function `signal` should be used to **regist** the signal type.

```cpp
#include <iostream>
#include <csignal>
#include <unistd.h>

using namespace std;

auto signalHandler(int signum) -> void {
    cout << "Interrupt signal (" << signum << ") recieved." << endl;

    // Clean and exit
    exit(signum);
}

auto main() -> int {
    signal(SIGINT, signalHandler);

    while(1) {
        cout << "Going to sleep..." << endl;
        sleep(1);
    }

    return 0;
}
```

## `int raise(signal sig)`

Raise a signal to be caught.

```cpp
#include <iostream>
#include <csignal>
#include <unistd.h>

using namespace std;

auto signalHandler(int signum) -> void {
    cout << "Interrupt signal (" << signum << ") recieved." << endl;

    // Clean and exit
    exit(signum);
}

auto main() -> int {
    signal(SIGINT, signalHandler);

    auto i = 0;
    while(++i) {
        cout << "Going to sleep..." << endl;
        if (i == 3)
            raise(SIGINT);
        sleep(1);
    }

    return 0;
}
```


