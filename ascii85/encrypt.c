#include "encrypt.h"

// Buffer of size (max. 1024), encrypt it and write it to file
int encrypt_write(int fd, uint8_t *buffer, int size) {
    // 0  -> Data were successfully encrypted and writen to file
    // -1 -> Write Failed
    uint8_t encrypted[ENCRYPTED_BUFFER];
    uint32_t tmp = 0;
    int i = 0;
    for (; i < size; i += 4) {
        memcpy(tmp, buffer + i, 4);
        for (int j = 0; j < 4; ++j) {
            encrypted[i + j] = (tmp % 85) + 33;
            tmp /= 85;
        }
    }

    if (write(fd, encrypted, i) < 0) {
        return -1;
    }
    return 0;
}


// Read bytes from in_fd, encrypt them and write them to out_fd
int encrypt(int in_fd, int out_fd) {
    // 0  -> File was successfully encrypted
    // -1 -> An error occured
    int bytes_read;
    uint8_t buffer[BUFFER_SIZE];

    while ((bytes_read = total_read(in_fd, buffer, BUFFER_SIZE)) > 0) {
        if (bytes_read % 4 != 0) {
            memset(buffer + bytes_read, '\0', BUFFER_SIZE - bytes_read);
        }

        if (encrypt_write(out_fd, buffer, bytes_read) == -1) {
            return -1;
        }
    }

    if (bytes_read < 0) {
        return -1;
    }
    return 0;
}


// Read <size> bytes from file descriptor
int total_read(int fd, uint8_t *buffer, int size) {
    // <total> -> bytes read from file descriptor
    // -1 -> An error occured
    int total = 0, rv = 0;

    while (total < size) {
        if ((rv = read(fd, buffer + total, size - total)) < 0) {
            return -1;
        }

        if (rv == 0) {
            break;
        }
        rv += total;
    }

    return total;
}
