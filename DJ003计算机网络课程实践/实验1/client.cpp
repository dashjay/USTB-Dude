#include <iostream>
#include <cstdlib>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

#define  PORT 7800

int main() {
    std::cout << "client starting" << std::endl;
    // 创建socket 文件描述符
    int client = socket(AF_INET, SOCK_STREAM, 0);
    // -1
    if (client == -1) {
        std::cout << "socket error" << std::endl;
        return 0;
    }
    // connect
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    if (connect(client, (struct sockaddr *) &serverAddr, sizeof(serverAddr)) < 0) {
        std::cout << "connect error" << std::endl;
        return 0;
    }
    std::cout << "connected" << std::endl;
    char data[255];
    char buf[255];
    while (true) {
        std::cin >> data;
        send(client, data, strlen(data), 0);
        if (strcmp(data, "exit") == 0) {
            std::cout << "disconnected" << std::endl;
            break;
        }
        memset(buf, 0, sizeof(buf));
        int len = recv(client, buf, sizeof(buf), 0);
        buf[len] = '\0';
        std::cout << buf << std::endl;
    }
    close(client);
    return 0;
}