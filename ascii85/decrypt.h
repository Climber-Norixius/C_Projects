#ifndef DECRYPT_H
#define DECRYPT_H

#include <stdint.h>     /* uint8_t */
#include <sys/stat.h>   /* fstat */

int decrypt(int in_fd, int out_fd);

#endif DECRYPT_H
