
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <arpa/inet.h>

void log_event(const char *message) {
    FILE *fp = fopen("chat.log", "a");
    if (fp != NULL) {
        time_t now = time(NULL);
        char *timestamp = ctime(&now);
        timestamp[strcspn(timestamp, "\n")] = 0;
        fprintf(fp, "[%s] %s\n", timestamp, message);
        fclose(fp);
    }
}

#define MAX_CLIENTS 100
#define BUFFER_SIZE 2048

typedef struct {
    int socket;
    char username[32];
} client_t;

client_t *clients[MAX_CLIENTS];
pthread_mutex_t clients_mutex = PTHREAD_MUTEX_INITIALIZER;

void broadcast(char *message, int exclude_sock) {
    pthread_mutex_lock(&clients_mutex);
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (clients[i]) {
            if (clients[i]->socket != exclude_sock) {
                write(clients[i]->socket, message, strlen(message));
            }
        }
    }
    pthread_mutex_unlock(&clients_mutex);
}

void *handle_client(void *arg) {
    char buffer[BUFFER_SIZE];
    client_t *cli = (client_t *)arg;

    sprintf(buffer, "%s se ha unido al chat.\n", cli->username);
    broadcast(buffer, cli->socket);
    printf("%s", buffer);
    log_event(buffer);

    while (1) {
        int bytes = recv(cli->socket, buffer, sizeof(buffer), 0);
        if (bytes <= 0) break;

        buffer[bytes] = '\0';
        char message[BUFFER_SIZE + 64];
        sprintf(message, "%s: %s", cli->username, buffer);
        broadcast(message, cli->socket);
        log_event(message);
    }

    close(cli->socket);
    sprintf(buffer, "%s ha salido del chat.\n", cli->username);
    broadcast(buffer, cli->socket);
    printf("%s", buffer);
    log_event(buffer);

    pthread_mutex_lock(&clients_mutex);
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (clients[i] == cli) {
            clients[i] = NULL;
            break;
        }
    }
    pthread_mutex_unlock(&clients_mutex);

    free(cli);
    pthread_exit(NULL);
}

int main() {
    int server_sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(12345);

    bind(server_sock, (struct sockaddr *)&server_addr, sizeof(server_addr));
    listen(server_sock, 10);

    printf("Servidor de chat iniciado en el puerto 12345...\n");

    while (1) {
        int client_sock = accept(server_sock, (struct sockaddr *)&client_addr, &addr_len);
        client_t *cli = (client_t *)malloc(sizeof(client_t));
        cli->socket = client_sock;

        // Pide nombre de usuario
        recv(client_sock, cli->username, sizeof(cli->username), 0);

        pthread_mutex_lock(&clients_mutex);
        for (int i = 0; i < MAX_CLIENTS; i++) {
            if (!clients[i]) {
                clients[i] = cli;
                break;
            }
        }
        pthread_mutex_unlock(&clients_mutex);

        pthread_t tid;
        pthread_create(&tid, NULL, &handle_client, (void *)cli);
    }

    return 0;
}
