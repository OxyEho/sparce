#include <unistd.h>
#include <getopt.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define ERROR_ARG_MSG "Error: Enter output filename"

int main(int argc, char *argv[]) {
    int buf_size = 4096;
    int i;
    while((i = getopt(argc, argv, "b:")) != -1) {
        if (i == 'b') {
            buf_size = atoi(optarg);
        }
    }

    if (argv[optind] == NULL) {
        printf(ERROR_ARG_MSG);
        return 1;
    }

    char* to_write = argv[optind];
    int to_read_f = STDIN_FILENO;
    if (argv[optind+1] != NULL) {
        char* to_read = argv[optind];
        to_write = argv[optind+1];
        to_read_f = open(to_read, O_RDONLY);
    }
    
    int to_write_f = open(to_write, O_WRONLY | O_CREAT, 0640);
    char read_buf[buf_size];

    while (1) {
        int readed = read(to_read_f, read_buf, buf_size);
        if (!readed) {
            break;
        }
        bool is_zero = true;
        int i;
        for (i = 0; i < buf_size; i++) {
            if (read_buf[i] != 0) {
                is_zero = false;
                break;
            }
        }

        if (!is_zero) {
            write(to_write_f, read_buf, readed);
        } else {
            lseek(to_write_f, readed, SEEK_CUR);
        }
    }
    return close(to_write_f);
}