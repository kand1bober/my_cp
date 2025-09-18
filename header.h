#ifndef DATA_WORK_HEADER
#define DETA_WORK_HEADER 

#include <fcntl.h>
#include <unistd.h>
#include <stddef.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>

int safe_open(const char* pathname, int flags);
void safe_close(int fd);
ssize_t safe_read(int fd, char* buf, size_t buf_sz);
ssize_t safe_write(int fd, const char* buf, size_t size);

ssize_t copy(int fd_from, int fd_to);
void transfer(const char* path_from, const char* path_to);

#endif
