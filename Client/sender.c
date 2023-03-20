#include "client.h"

int sender(int socket, char *packet, size_t length) {
    uint32_t prefix = htonl(length);
    ssize_t status;

    char* buffer = malloc(sizeof(prefix) + length);
    memcpy(buffer, &prefix, sizeof(prefix));
    memcpy(buffer + sizeof(prefix), packet, length);

    size_t totalSent = 0;
    while (totalSent < sizeof(prefix) + length) {
        status = send(socket, buffer + totalSent, sizeof(prefix) + length - totalSent, 0);
        if (status < 0) {
            if (errno == ECONNRESET || errno == EPIPE) {
                close(socket);
                free(buffer);
                return 1;
            }
            perror("Error sending message [try again]");
            free(buffer);
            return -1;
        }
        totalSent += status;
    }

    free(buffer);
    return 0;
}
