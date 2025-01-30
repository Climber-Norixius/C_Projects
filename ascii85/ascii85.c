#include <stdlib.h>     /* EXIT_* */
#include <fcntl.h>      /* open */
#include "encrypt.h"
#include "decrypt.h"


void help(void) {
    printf("Usage: ./ascii85 -e/-d/'' in_file.txt out_file.txt\n"
           "-h      - prints help"
           "-e/''   - encode file"
           "-d      - decode file");
}


void close_or_warn(int fd) {
    if (close(fd) == -1) {
        warn("Closing fd %d", fd);
    }
}


int main(int argc, char *argv[]) {
    // usage ./ascii85 -e/-d/'' in_file.txt out_file.txt
    int rv = 0;

    // help
    if (argc == 2 && strcmp(argv[1], "-h") == 0) {
        help();
        return EXIT_SUCCESS;
    }
    // encrypt
    if (argc == 3 || (argc == 4 && strcmp(argv[1], "-e") == 0)) {
        int in_fd = open(argv[2], O_RDONLY);
        if (in_fd == -1) {
            return EXIT_FAILURE;
        }
        int out_fd = open(argv[2], O_WRONLY);
        if (out_fd == -1) {
            close_or_warn(in_fd);
            return EXIT_FAILURE;
        }
        rv = encrypt(in_fd, out_fd); // INSERT FD
        close_or_warn(in_fd);
        close_or_warn(out_fd);
    }
    // decrypt
    if (argc == 4 && strcmp(argv[1], "-d") == 0) {
        rv = decrypt(-1); // INSERT FD
    }
    else {
        return EXIT_FAILURE;
    }

    if (rv != 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

