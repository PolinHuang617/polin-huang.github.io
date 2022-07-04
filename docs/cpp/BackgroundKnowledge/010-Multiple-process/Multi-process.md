## `fork`

Parent and child process's fd point to the same file table, sharing the file bias pointer, but reference counter will increase.

GDB debug multi-process:
    Before `fork()`, using `set follow-fork-mode child` to debug child process; using `set follow-fork-mode parent` to debug parent process.

```cpp
#include <iostream>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>

auto main() -> int {
    try {

        // After fork(), parent and child has their
        // own *p respectively.
        auto *p = new int(1);

        // fork() return 0 in child process
        //        return child pid in parent process
        auto pid = fork();

        if (0 > pid) { throw "fork error."; }
        // child process
        else if (0 == pid) {
            std::cout << "child pid: " << getpid()
                << ", parent pid: " << getppid()
                << std::endl;

            for (; *p < 20; ++(*p)) {
                std::cout << "child processing "
                    << *p << " task." << std::endl;
                sleep(1);
            }

            // free child's *p
                        free(p);
            p = nullptr;

            exit(0);
        }

        // parent process
        std::cout << "parent pid: " << getpid()
            << ", parent's parent pid: " << getppid()
            << std::endl;

        std::cout << "parent suspending, waiting for child process ..." << std::endl;
        auto status = 0;
        // parent suspending use wait()
        //        continue use waitpid()
        auto ret = wait(&status);

        std::cout << "child process ends, parent collects its resource." << std::endl;
        // child process status
        if (-1 == ret) { throw "wait error"; }

        // Normally exit
        if (WIFEXITED(status)) {
            // macro WEXITSTATUS to get status code
            std::cout << "child normally exit: "
                << WEXITSTATUS(status) << std::endl;
        }
        // Exit with exception
        // e.g. kill -9 pid
        // use kill -l to list signal can be sent
        // kill -19 pid to suspend child process
        // kill -18 pid to continue child process
        else if (WIFSIGNALED(status)) {
            // macro WTERMSIG to get
            // which signal exits child process
            std::cout << "child exit with exception: "
                << WTERMSIG(status) << std::endl;
        }
        // Stop by what signal
        else if (WIFSTOPPED(status)) {
            // macro WSTOPSIG to get
            // which signal stops child process
            std::cout << "child stop by: "
                << WSTOPSIG(status) << std::endl;
        }

        // free parent's *p
        free(p);
        p = nullptr;

        return EXIT_SUCCESS;
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}
```

-  Orphan process
Parent process has exited, but child not. The orphan will be adopted by init process (pid 1). Orphan process has few impact. 
-  Zombie process
Parent process fails to collect child's resource, which remaining in memory, ocuppying pid. If it has too many zombies, kernel will fail to allocate new process.
Zombies should use `wait` or `waitpid` to kill. 

## Nameless pipe

- 半双工，同一时刻仅有一个方向有数据流动
- FIFO
- 无格式数据，要求读写双方实现约定好数据格式
- 数据一次性读写，读取后即丢弃
- pipe只在内存中，没有名字，只有公共祖先进程
- 默认阻塞，读方等待pipe中有数据才读取

Creation:

```cpp
#include <unistd.h>

// pipefd[0] => read side, default
// pipefd[1] => write side, default
//
// return 0 => success
//       -1 => failed
int pipe(int pipefd[2])

// use ulimit -a to check pipe block size
// name:
//     _PC_PIPE_BUF => Check buffer size
//     _PC_NAME_MAX => Check buffer maximun
long fpathconf(int fd, int name)

// set pipe mode to no block,
// if pipe has no data, read() return -1
//     acquire fd flag
int flag = fcntl(fd[0], F_GETFL);
//     set new flag
flag |= O_NOBLOCK;
fcntl(fd[0], F_SETFL, flag);
```

e.g.

```cpp
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <cstring>

#define SIZE 64

auto main() -> int {
    try {
        // Create pipe
        char buffer[SIZE];
        int fds[2];
        auto ret = pipe(fds);
        if (-1 == ret) { throw "pipe creation error."; }

        // Spawn child
        auto pid = fork();
        if (pid < 0) { throw "fork error."; }

        // child process: reade side
        if (0 == pid) {
            // close write fd
            close(fds[1]);

            memset(buffer, 0, SIZE);
            ret = read(fds[0], buffer, SIZE);
            if (-1 == ret) { throw "read error"; }

            std::cout << "Child read: " << buffer << std::endl;
            close(fds[0]);
            exit(0);
        }

        // parent process: write side
        // close read side
        close(fds[0]);

        memset(buffer, 0, SIZE);
        std::string buffer1 = "ABCDEFG12345678!@#$%^&*";
        ret = write(fds[1], buffer1.c_str(), SIZE);
        if (-1 == ret) { throw "write error"; }

        std::cout << "Parent write: " << buffer1
            << ", status: " << ret << std::endl;

        // write ends, close write side
        close(fds[1]);

        // wait child process ends
        std::cout << "parent suspending, waiting for child process ..." << std::endl;

        // parent suspending use wait()
        auto status = 0;
        ret = wait(&status);

        std::cout << "child process ends, parent collects its resource." << std::endl;
        // child process status
        if (-1 == ret) { throw "wait error"; }

        return EXIT_SUCCESS;
    }catch(const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}
```

## FIFO pipe

- 无名管道只能用于有亲缘关系的进程，为了克服这个缺点，有名管道提供了可以根据路径进行关联的使用方式。
- FIFO，管道文件保存在文件系统中，其中的数据保存在**内存**中。
- 当有名管道使用完成后，继续保存在文件系统中，以后仍可使用。

Create fifo pipe using linux command:

```bash
root@Debian11:~/workspace# mkfifo fifo
root@Debian11:~/workspace# ll
prw-r--r-- 1 root root    0 Mar 22 12:04 fifo|
```

```cpp
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string>

auto main() -> int {
    try {
        // Create fifo pipe
        //
        // mode_t is like linux normal permission code,
        // like 0777, 0644
        // int mkfifo(const char* pathName, mode_t mode)
        const std::string fifoPipe = "fifo";
        
        if ( access(fifoPipe.c_str(), F_OK) != -1 )
            std::cerr << "FIFO pipe already exsited." << std::endl;
        
        auto ret = mkfifo(fifoPipe.c_str(), 0644);
        if (-1 == ret)
            std::cerr << "FIFO pipe creation failed." << std::endl;
        else
            std::cout << "FIFO pipe created at " << fifoPipe << std::endl;
        
        return EXIT_SUCCESS;
    } catch(const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}
```

### Write to pipe

```cpp
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <cstdio>
#include <cstring>

#define SIZE 256

auto main() -> int {
    try {
        char *buffer = new char[SIZE];

        // 1. Create fifo pipe in write-only mode
        auto fd = open("fifo", O_WRONLY);
        if (-1 == fd)
            std::cerr << "Open pipe error." << std::endl;
        else
            std::cout << "Open fifo in write-only mode." << std::endl;

        // 2. Write data to pipe
        int i = 0;
        while (true) {
            std::sprintf(buffer, "Hello %d FIFO pipe.", i++);
            auto ret = write(fd, buffer, std::strlen(buffer));
            if (-1 == ret) {
                std::cerr << "Write error." << std::endl;
                break;
            }

            std::cout << "Write: " << buffer << std::endl;
            sleep(1);
        }

        // 3. Close pipe
        close(fd);
        delete[] buffer;
        buffer = nullptr;

        return EXIT_SUCCESS;
    }catch(const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}
```

### Read from pipe

```cpp
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <cstdio>
#include <cstring>

#define SIZE 256

auto main() -> int {
    try {
        char *buffer = new char[SIZE];

        // 1. Create fifo pipe in read-only mode
        auto fd = open("fifo", O_RDONLY);
        if (-1 == fd)
            std::cerr << "Open pipe error." << std::endl;
        else
            std::cout << "Open fifo in read-only mode." << std::endl;

        // 2. Read data to pipe
        int i = 0;
        while (true) {
            auto ret = read(fd, buffer, SIZE);
            if (-1 == ret) {
                std::cerr << "Read error." << std::endl;
                break;
            }
        }
        
        // 3. Close pipe
        close(fd);
        delete[] buffer;
        buffer = nullptr;

        return EXIT_SUCCESS;
    }catch(const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}
```

```makefile
all: read write

read: read.cpp
g++ $< -o $@

write: write.cpp
g++ $< -o $@

.PHONY: clean
clean:
    rm -rf read write
```

一个以只读方式打开有名管道的进程会阻塞，直到另一个以只写方式打开有名管道的进程打开该管道，反之亦然。
e.g. Chat room

```cpp
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <cstring>
#include <cstdio>

#define SIZE 256

auto main() -> int {
    // 1. open fifo1 in read-only
    auto fd1 = open("fifo1", O_RDONLY);
    if (-1 == fd1)
        std::cerr << "Open fifo1 failed." << std::endl;
    else
        std::cout << "Open fifo1 in read-only." << std::endl;
    // 2. open fifo2 in write-only
    auto fd2 = open("fifo2", O_WRONLY);
    if (-1 == fd2)
        std::cerr << "Open fifo2 failed." << std::endl;
    else
        std::cout << "Open fifo2 in write-only." << std::endl;

    // 3. loop
    auto buffer = new char[SIZE];
    auto ret = 0;
    while (true) {
        //    3.1 read from fifo1
        std::memset(buffer, 0, SIZE);
        ret = read(fd1, buffer, SIZE);
        if (-1 == ret)
            std::cerr << "Read fifo1 error." << std::endl;
        else
            std::cout << "Receive: " << buffer << std::endl;

        //    3.2 write to fifo2
        std::memset(buffer, 0, SIZE);
        std::fgets(buffer, SIZE, stdin);
        // Trim last newline character
        if ('\n' == buffer[strlen(buffer) - 1])
            buffer[strlen(buffer) - 1] = '\0';

        ret = write(fd2, buffer, std::strlen(buffer));
        if (-1 == ret)
            std::cerr << "Write fifo2 error." << std::endl;
        else
            std::cout << "Send: " << buffer << std::endl;
    }

    // 4. close fifo1 fifo2
    close(fd1);
    close(fd2);
    delete[] buffer;
    buffer = nullptr;

    return EXIT_SUCCESS;
}
```

```cpp
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <cstring>
#include <cstdio>

#define SIZE 256

auto main() -> int {
    // 1. open fifo1 in write-only
    auto fd1 = open("fifo1", O_WRONLY);
    if (-1 == fd1)
        std::cerr << "Open fifo1 failed." << std::endl;
    else
        std::cout << "Open fifo1 in write-only." << std::endl;

    // 2. open fifo2 in read-only
    auto fd2 = open("fifo2", O_RDONLY);
    if (-1 == fd2)
        std::cerr << "Open fifo2 failed." << std::endl;
    else
        std::cout << "Open fifo2 in read-only." << std::endl;

    // 3. loop
    auto buffer = new char[SIZE];
    auto ret = 0;
    while (true) {
        //    3.1 write to fifo1
        std::memset(buffer, 0, SIZE);
        std::fgets(buffer, SIZE, stdin);
        // Trim last newline character
        if ('\n' == buffer[strlen(buffer) - 1])
            buffer[strlen(buffer) - 1] = '\0';

        ret = write(fd1, buffer, std::strlen(buffer));
        if (-1 == ret)
            std::cerr << "Write fifo1 error." << std::endl;
        else
            std::cout << "Send: " << buffer << std::endl;

        //    3.2 read from fifo2
        std::memset(buffer, 0, SIZE);
        ret = read(fd2, buffer, SIZE);
        if (-1 == ret)
            std::cerr << "Read fifo2 error." << std::endl;
        else
            std::cout << "Receive: " << buffer << std::endl;
    }

    // 4. close fifo1 fifo2
    close(fd1);
    close(fd2);
    delete[] buffer;
    buffer = nullptr;

    return EXIT_SUCCESS;
}
```

## Shared memory mapping

| Address | Description |
| --- | --- |
| High | Stack |
|  | File memory-mapping |
|  | Heap |
|  | bbs data |
|  | init data |
| Low | text data |

Shared memory-mapping is the most effictive and fastest way of IPC (Inter-process communication), Using `mmap`.

```cpp
int mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset);
// addr: initial address of memory mapping. Usually NULL, determined by OS.
// length: mapping length.
// prot: protection method of memory mapping.
//       1) read: PROT_READ;
//       2) write: PROTY_WRITE
//       3) read/write: PROT_READ | PROTY_WRITE
// flags:
//       1) MAP_SHARED: data writed into mapping will copy back to mapped file, allowing other process share this file.
//       2) MAP_PRIVATE: generate a duplication when data writes into mapping (copy on write).
// fd: file description returned by open(), that is the mapped file.
// offset: bias offset from file beginning, 4K times, usually 0 (beginning).
//
// return value:
//       Succeed: mapping initial address.
//       Failed:  macro MAP_FAILED
```

```cpp
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <cstring>
#include <sys/mman.h>

auto main() -> int {
    // Open a file on read-write
    auto fd = open("txt", O_RDWR);
    if (-1 == fd)
        std::cerr << "Open failed." << std::endl;

    // Mapping file to memory
    auto addr = mmap(nullptr, 1024, PROT_READ | PROT_WRITE,
            MAP_SHARED, fd, 0);
    if (MAP_FAILED == addr)
        std::cerr << "Mapping error." << std::endl;

    std::cout << "File opened." << std::endl;

    // Close file
    close(fd);

    // Writing to mapping is writing to file
    memcpy(addr, "0987654321", 10);

    // Unmapping
    munmap(addr, 1024);
    
     return EXIT_SUCCESS;
}
```

> Notice: file permission
> Parent and child communicate with shared real file, which defect is that file is easy to be alterred.

```cpp
#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <cstring>
#include <sys/mman.h>

auto main() -> int {
    // Open a file on read-write
    auto fd = open("txt", O_RDWR);
    if (-1 == fd)
        std::cerr << "Open failed." << std::endl;

    // Mapping file to memory
    auto addr = mmap(nullptr, 1024, PROT_READ | PROT_WRITE,
            MAP_SHARED, fd, 0);
    if (MAP_FAILED == addr)
        std::cerr << "Mapping error." << std::endl;

    std::cout << "File opened." << std::endl;

    // Close file
    close(fd);

    auto pid = fork();
    if (-1 == pid)
        std::cerr << "Fork error." << std::endl;
        // Child
    if (0 == pid) {
        memcpy(addr, "Hi father.", 10);

        exit(EXIT_SUCCESS);
    }

    // Parent
    // Writing to mapping is writing to file
    // Wait child completed.
    wait(nullptr);
    std::cout << "Receive from child: "
        << static_cast<char*>(addr) << std::endl;
    memcpy(addr, "Hi son.", 10);

    // Unmapping
    munmap(addr, 1024);;

    return EXIT_SUCCESS;
}
```

Anonymous shared mapping can hide the linked mapping file. But it can only use in parent-child process.

```cpp
#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <cstring>
#include <sys/mman.h>

auto main() -> int {
    // Open a anonymous mapping on read-write
    // Mapping file to memory
    auto addr = mmap(nullptr, 1024, PROT_READ | PROT_WRITE,
            MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if (MAP_FAILED == addr)
        std::cerr << "Mapping error." << std::endl;

    auto pid = fork();
    if (-1 == pid)
        std::cerr << "Fork error." << std::endl;

    // Child
    if (0 == pid) {
        memcpy(addr, "Hi father.", 10);

        exit(EXIT_SUCCESS);
    }
    
    // Parent
    // Writing to mapping is writing to file
    // Wait child completed.
    wait(nullptr);
    std::cout << "Receive from child: "
        << static_cast<char*>(addr) << std::endl;
    memcpy(addr, "Hi son.", 10);

    // Unmapping
    munmap(addr, 1024);;

    return EXIT_SUCCESS;
}
```
