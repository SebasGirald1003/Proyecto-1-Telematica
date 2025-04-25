#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 2048

int sockfd;
char username[32];

void *send_messages(void *arg) {
    char buffer[BUFFER_SIZE];
    while (1) {
        fgets(buffer, BUFFER_SIZE, stdin);
        if (strncmp(buffer, "exit", 4) == 0) {
            break;
        }
        send(sockfd, buffer, strlen(buffer), 0);
    }
    close(sockfd);
    exit(0);
}

void *receive_messages(void *arg) {
    char buffer[BUFFER_SIZE];
    while (1) {
        int bytes = recv(sockfd, buffer, sizeof(buffer) - 1, 0);
        if (bytes <= 0) break;
        buffer[bytes] = '\0';
        printf("%s", buffer);
        fflush(stdout);
    }
    return NULL;
}

int main() {
    struct sockaddr_in server_addr;
    pthread_t send_thread, recv_thread;

    printf("Ingrese su nombre de usuario: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = 0; // quitar salto de línea

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(12345);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // localhost

    if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("No se pudo conectar al servidor");
        return 1;
    }

    send(sockfd, username, strlen(username), 0);

    pthread_create(&send_thread, NULL, send_messages, NULL);
    pthread_create(&recv_thread, NULL, receive_messages, NULL);

    pthread_join(send_thread, NULL);
    pthread_join(recv_thread, NULL);

    return 0;
}
