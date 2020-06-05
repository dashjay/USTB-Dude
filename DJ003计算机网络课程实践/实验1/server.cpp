#include <iostream>
#include <cstdlib>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

#define  PORT 7800

int main() {
    std::cout << "server starting" << std::endl;
    // socket文件描述符
    int listenFD = socket(AF_INET, SOCK_STREAM, 0);
    if (listenFD == -1) {
        std::cout << "create fd error" << std::endl;
        return 0;
    }
    // 绑定本地地址
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = INADDR_ANY; // INADDR_ANY 表示是任意地址，也就是0.0.0.0
    if (bind(listenFD, (struct sockaddr *) &addr, sizeof(addr)) == -1) {
        std::cout << "bind error, port occupied" << std::endl;
        return 0;
    }
    // 监听
    if (listen(listenFD, 5) == -1) {
        std::cout << "listen error" << std::endl;
        return 0;
    }
    // accept
    int conn;
    char clientIP[INET_ADDRSTRLEN] = "";
    struct sockaddr_in clientAddr;
    socklen_t clientAddrLen = sizeof(clientAddr);
    while (true) {
        std::cout << "listen starting" << std::endl;
        conn = accept(listenFD, (struct sockaddr *) &clientAddr, &clientAddrLen);
        if (conn < 0) {
            std::cout << "accept error" << std::endl;
            continue;
        }
        inet_ntop(AF_INET, &clientAddr.sin_addr, clientIP, INET_ADDRSTRLEN);
        std::cout << "client connected " << clientIP << ":" << ntohs(clientAddr.sin_port) << std::endl;

        char buf[255];
        while (true) {
            memset(buf, 0, sizeof(buf));
            int len = recv(conn, buf, sizeof(buf), 0);
            // 设置终止符
            buf[len] = '\0';
            if (strcmp(buf, "exit") == 0) {
                std::cout << "client disconnect " << clientIP << ":" << ntohs(clientAddr.sin_port) << std::endl;
                break;
            }
            std::cout << buf << std::endl;
            send(conn, buf, len, 0);
        }
        close(conn);
    }
    close(listenFD);
    return 0;
}