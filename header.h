#include <fcntl.h>
#include <unistd.h>
#include <stddef.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>

#ifndef DATA_WORK_HEADER
#define DETA_WORK_HEADER 

#define MASK_V 4
#define MASK_I 2
#define MASK_F 1

#define MAX_PATH_LEN 128

int safe_open(const char* pathname, int flags);
void safe_close(int fd);
ssize_t safe_read(int fd, char* buf, size_t buf_sz);
ssize_t safe_write(int fd, const char* buf, size_t size);

ssize_t copy(int fd_from, int fd_to);
void transfer(const char* path_from, const char* path_to, char opts, char** lines, int* lines_count);
void configure_and_transfer(const char* path_from, const char* path_to, char opts, char** lines, int* lines_count);

char parse(int argc, char* argv[]);

void show_verbose(char** lines, int* lines_count);

#endif
