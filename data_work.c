#include "header.h"

int safe_open(const char* pathname, int flags)
{   
    int fd = open(pathname, flags, 0666);

    if (fd < 0)
    {
        perror("Error in opening of file\n");
        exit(1);
    }

    return fd;
}


void safe_close(int fd)
{
    if (close(fd) < 0)
    {
        perror("Error in cloing file\n");
        exit(1);
    }
}

ssize_t safe_read(int fd, char* buf, size_t buf_sz)
{
    ssize_t n = 1, read_bytes = 0;
    while (n > 0)
    {   
        n = read(fd, buf + read_bytes, buf_sz - read_bytes); //read from file
        if (n < 0)
        {
            perror("Error in reading of file\n");
            exit(1);
        }

        read_bytes += n;

        if (fd == 0 && *(buf + read_bytes - 1) == '\n')
            return read_bytes;

    }

    return read_bytes;
}


ssize_t safe_write(int fd, const char* buf, size_t size)
{
    ssize_t n = 1, written = 0;  
    while (n > 0)
    {
        n = write(fd, buf + written, size - written);
        written += n;

        if (n < 0)
        {
            perror("Error in write syscall\n");
            exit(1);
        }
    }

    return written;
}