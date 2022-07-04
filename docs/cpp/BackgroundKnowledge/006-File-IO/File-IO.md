- `ifstream`: Stream class to read from files.
- `ofstream`: Stream class to write to files.
- `fstream`: Stream class to both read and write from/to files.

## Open a file
| Mode | Description |
| --- | --- |
| `std::ios::in` | Open for input opeartions |
| `std::ios::out` | Open for output operations. |
| `std::ios::binary` | Open in binary mode. |
| `std::ios::ate` | Set the initial position at the end of the file. If this flag is not set, the initial position is the beginning of the file. |
| `std::ios::app` | All output operations are performed at the end of the file, appending content. |

### Text file

#### Read

```cpp
std::string line;
std::ifstream infile;
infile.open("README.txt");

if (infile.is_open()) {
    while ( std::getline(infile, line) ) {
    // proceeding code ...
    std::cout << line << std::endl;
    }

    infile.close();
}
```

#### Write

```cpp
std::ofstream outfile;
outfile.open("README.txt", ios::out | ios::app);

if (outfile.is_open()) {
    // proceeding code ...
    outfile << "test ...";

    outfile.close();
}
else {
    std::cerr << "Unable to open file: " << outfile;
}
```

### Binary file

#### Read

```cpp
#include <iostream>
#include <fstream>

auto main(int argc, char **argv) -> int {
    try {
        // Open bin file and put file cursor to file end.
        std::ifstream inFile("example.bin", std::ios::in | std::ios::binary | std::ios::ate);
        if (inFile.is_open()) {
            // get cursor position(file end), which is the file size.
            std::streampos fileSize = inFile.tellg();
            // set receptor array.
            char *memblock = new char[fileSize];
            // Move file cursor to file beginning
            inFile.seekg(0, std::ios::beg);
            // Read binary file.
            inFile.read(memblock, fileSize);
            // Print file content.
            for (std::size_t i = 0; i < fileSize; ++i)
                std::cout << memblock[i];
            std::cout << std::endl;
            // Close file.
            inFile.close();
            delete[] memblock;
        }
        else {
            std::cerr << "Unable to open file." << std::endl;
        }

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

#### Write

```cpp
#include <iostream>
#include <fstream>
#include <cstring>

auto main(int argc, char **argv) -> int {
    try {
        char *memblock = new char[10000];
        std::memset(memblock, 'A', 10000 * sizeof(char));

        std::ofstream outFile("example.bin", std::ios::out | std::ios::binary);
        if (outFile.is_open()) {
            // Write method 1
            //for(std::size_t i = 0; i < 10000; ++i) {
                //outFile << memblock[i];
            //}

            // Write method 2
            outFile.write(memblock, 10000);
            outFile.close();
        }
        else {
            std::cerr << "Unable to open file." << std::endl;
        }

        delete[] memblock;
        
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
