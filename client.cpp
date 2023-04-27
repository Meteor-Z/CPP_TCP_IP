#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

#include <cstring>
#include <iostream>
void error_handling(const std::string& message)
{
    std::cerr << message << std::endl;
    exit(1);
}

int main(int argc, char* argv[])
{
    struct sockaddr_in server_addr;
    char message[30];
    int str_len;
    if (argc != 3)
    {
        printf("Usage: %s <IP> <port> \n", argv[0]);
        exit(1);
    }
    int sock = socket(PF_INET, SOCK_STREAM, 0);
    if (sock == -1)
    {
        error_handling("socket() error");
    }
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(argv[1]);
    server_addr.sin_port = htons(atoi(argv[2]));

    if (connect(sock, (struct sockaddr*) &server_addr, sizeof(server_addr)) == -1)
    {
        error_handling("connect() error");
    }
    str_len = read(sock, message, sizeof(message) - 1);
    if(str_len ==-1)
    {
        error_handling("read() error");
    }
    std::cout<<"信息是: "<<message<<std::endl;
    close(sock);
    return 0;
}