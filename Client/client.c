#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 3000

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[1000] = {0};

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }

    printf("Connected to server. Start chatting! Type 'exit' to end the chat.\n");

    while (1) 
    {
        printf("Client: ");
        fgets(buffer, sizeof(buffer), stdin);
        buffer[strcspn(buffer, "\n")] = '\0';

        send(sock, buffer, strlen(buffer), 0);

        if (strcmp(buffer, "exit") == 0) {
            printf("You have exited the chat.\n");
            break;
        }

        int valread = read(sock, buffer, sizeof(buffer));
        if (valread > 0) {
            printf("Server: %s\n", buffer);
        }

        if (strcmp(buffer, "exit") == 0) {
            printf("Server has exited the chat.\n");
            break;
        }
    }

    close(sock);
    return 0;
}
