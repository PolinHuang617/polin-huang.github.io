#include <iostream>
#include <string>
#include <cstdlib>
#include <cstring>

#if defined(__linux__) || defined(__APPLE__) || defined(__POSIX_VERSION__) || defined(__unix__)
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#elif defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#include <winsock2.h>
#pragma comment (lib, "ws2_32.lib")
#endif

auto main() -> int {

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
    // Initial DLL
    WSADATA wasData;
    WSAStartup(MAKEWORD(2, 2), &wasData);
#endif

    // Create socket
    // socket(int __domain, int __type, int __protocol)
    // __domain:
    //   IPv4: AF_INET  or PF_INET
    //   IPV6: AF_INET6 or PF_INET6
    // __type:
    //   SOCK_STREAM: TCP, HTTP
    //   SOCK_DGRAM:  UDP
    auto clientSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    // Initialize and bind socket with ip and port
    struct sockaddr_in clientAddr;
    // Fill addr with 0
    memset(&clientAddr, 0, sizeof(clientAddr));
    clientAddr.sin_family = AF_INET;
    clientAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    clientAddr.sin_port = htons(1234);
    connect(clientSock, (struct sockaddr*)&clientAddr, sizeof(clientAddr));

    // Read from server
    char buffer[40];
#if defined(__linux__) || defined(__APPLE__) || defined(__POSIX_VERSION__) || defined(__unix__)
    read(clientSock, buffer, sizeof(buffer) - 1);
#elif defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
    recv(clientSock, buffer, 40, NULL);
#endif

    std::cout << "Message from server: " << buffer << std::endl;

#if defined(__linux__) || defined(__APPLE__) || defined(__POSIX_VERSION__) || defined(__unix__)
    close(clientSock);
#elif defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
    closesocket(clientSock);

    WSACleanup();
#endif

    return EXIT_SUCCESS;
}
