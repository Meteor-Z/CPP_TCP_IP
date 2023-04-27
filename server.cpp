#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

#include <cstring>
#include <iostream>

void error_handing(const std::string& message)
{
    std::cerr << message << std::endl;
    exit(1);
}

int main(int argc, char* argv[])
{
    int server_sock;
    int client_sock;
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;

    socklen_t client_addr_size;

    char message[] = "Hello World!";

    if (argc != 2)
    {
        printf("Usage: %s <port>\n", argv[0]);
        exit(1);
    }

    server_sock = socket(PF_INET, SOCK_STREAM, 0);

    if (server_sock == -1)
    {
        error_handing("socket() error");
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    // htonl(): 32位整数转换成网络字节序
    // htonl htons host to network shrot/long
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(atoi(argv[1]));

    // 绑定监听的端口
    if (bind(server_sock, (struct sockaddr*) &server_addr, sizeof(server_addr) ) ==-1)
    {
        error_handing("bind() error");
    }
    // 进行监听， 最大是5
    if (listen(server_sock, 5) == -1)
    {
        error_handing("listen() error");
    }

    client_addr_size = sizeof(client_addr);
    client_sock = accept(server_sock, (struct sockaddr*) &client_addr, &client_addr_size);

    if (client_sock == -1)
    {
        error_handing("accept() error");
    }
    write(client_sock, message, sizeof(message));
    close(client_sock);
    close(server_sock);
    return 0;
}