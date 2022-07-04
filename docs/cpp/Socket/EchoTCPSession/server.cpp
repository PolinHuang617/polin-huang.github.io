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
    auto serverSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    // Initialize and bind socket with ip and port
    struct sockaddr_in serverAddr;
    // Fill addr with 0
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serverAddr.sin_port = htons(1234);
    bind(serverSock, (struct sockaddr*)&serverAddr, sizeof(serverAddr));

    // Listening request
    listen(serverSock, 20);

    // Accept client request
    struct sockaddr_in clientAddr;
#if defined(__linux__) || defined(__APPLE__) || defined(__POSIX_VERSION__) || defined(__unix__)
    socklen_t clientAddrSize = sizeof(clientAddr);
#elif defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
    int clientAddrSize = sizeof(clientAddr);
#endif
    auto clientSock = accept(serverSock, (struct sockaddr*)&clientAddr, &clientAddrSize);

    // Send to client
    std::string str = "Hello world!";
#if defined(__linux__) || defined(__APPLE__) || defined(__POSIX_VERSION__) || defined(__unix__)
    write(clientSock, str.c_str(), sizeof(str));

    close(clientSock);
    close(serverSock);
#elif defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
    send(clientSock, str.c_str(), sizeof(str), NULL);

    closesocket(clientSock);
    closesocket(serverSock);

    WSACleanup();
#endif

    return EXIT_SUCCESS;
}
