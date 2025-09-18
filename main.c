#include "header.h"

int main(int argc, char* argv[])
{
    if (argc < 3)
    {
        perror("Wrong using of cp\n");
        exit(0);
    }   
    
    if (argc == 3) // copy file to fie
    {
        transfer(argv[1], argv[2]);
    }
    else // copy files to directory 
    {
        char pathname[128];
        for (int i = 1; i < argc - 1; i++)
        {
            snprintf(pathname, 128, "%s/%s", argv[argc - 1], argv[i]);  
            transfer(argv[i], pathname);
        }
    }
    return 0;
}


ssize_t copy(int fd_from, int fd_to)
{
    if (fd_from < 0 || fd_to < 0)
    {
        perror("Error in opening descriptors\n");
        exit(1);
    }

    size_t buf_sz = 4096;
    char buf[buf_sz] = {};

    ssize_t read_bytes = safe_read(fd_from, buf, buf_sz);
    ssize_t written = safe_write(fd_to, buf, read_bytes);

    return written;
}


void transfer(const char* path_from, const char* path_to)
{
    int fd_from = safe_open(path_from, O_RDONLY);
    int fd_to = safe_open(path_to, O_WRONLY | O_CREAT);

    copy(fd_from, fd_to);

    safe_close(fd_from);
    safe_close(fd_to);
}
