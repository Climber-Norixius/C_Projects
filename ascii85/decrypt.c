#include "decrypt.h"

// Decrypt and write
int decrypt_write(int fd, uint8_t *buffer, int size) {

}

// Read and decrypt
int decrypt(int in_fd, int out_fd) {
    struct stat file_stat;
    if (fstat(in_fd, &file_stat) == -1) {
        return -1;
    }

    if (file_stat.st_size % 5 != 0) {
        return -1; // -2 Maybe 
    }
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