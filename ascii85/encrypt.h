#ifndef ENCRYPT_H
#define ENCRYPT_H

#include <stdint.h>     /* uint8_t, uint32_t */
#include <unistd.h>     /* write, read, close */
#include <string.h>     /* memcpy, memset */
#define BUFFER_SIZE 1024
#define ENCRYPTED_BUFFER 1280

int encrypt(int in_fd, int out_fd);

#endif ENCRYPT_H
