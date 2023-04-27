#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <sys/socket.h>
#include <unistd.h>
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
    int sock = 
}