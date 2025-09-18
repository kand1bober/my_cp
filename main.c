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
        int fd_to = safe_open(argv[argc - 1], O_WRONLY | O_DIRECTORY); //open dir

        // int fd_from = 0;
        // for (int i = 1; i < argc )
        // {
        //     fd_from = safe_open(argv[i], O_RDONLY); 

        //     //создать файл с именем dir/староеимя и transfer

        //     //copy(fd_from, fd_to);



        //     fd_from = 0;
        // }
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
    int fd_to = safe_open(path_to, O_WRONLY);

    copy(fd_from, fd_to);

    safe_close(fd_from);
    safe_close(fd_to);
}
