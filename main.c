#include "header.h"

int main(int argc, char* argv[])
{
    char opts = parse(argc, argv);
    extern int optind;

    if (MASK_F == (opts & MASK_F))
        opts = 0; // delete all options

    if ((argc - optind) < 2)
    {
        perror("Wrong using of cp");
        exit(0);
    }   

    if ((argc - optind) == 2) // copy file to fie
    {
        configure_and_transfer(argv[optind], argv[optind + 1], opts);
    }
    else // copy files to directory 
    {
        char pathname[MAX_PATH_LEN];
        for (int i = optind; i < argc - 1; i++)
        {
            snprintf(pathname, MAX_PATH_LEN, "%s/%s", argv[argc - 1], argv[i]);  
            configure_and_transfer(argv[i], pathname, opts);
        }
    }

    return 0;
}


ssize_t copy(int fd_from, int fd_to)
{
    if (fd_from < 0 || fd_to < 0)
    {
        perror("Error in opening descriptors");
        exit(1);
    }

    size_t buf_sz = 4096;
    char buf[buf_sz] = {};

    ssize_t read_bytes = safe_read(fd_from, buf, buf_sz);
    ssize_t written = safe_write(fd_to, buf, read_bytes);

    return written;
}


void configure_and_transfer(const char* path_from, const char* path_to, char opts)
{
    if (MASK_I == (opts & MASK_I) && file_exists(path_to)) 
    {
        printf("my_cp: overwrite: '%s' ? y\\n\n", path_to);

        char ans = 0;
        ans = getchar(); getchar(); // to skip '\n' 
        if (ans == 'y' || ans == '\n')
        {
            transfer(path_from, path_to, opts);
        }
    }
    else 
    {
        transfer(path_from, path_to, opts);
    }
}


bool file_exists(const char* pathname)
{
    struct stat info;
    if (stat(pathname, &info) == 0)
        return true;
    else     
        return false;
}


void transfer(const char* path_from, const char* path_to, char opts)
{

    int fd_from = safe_open(path_from, O_RDONLY);
    int fd_to = safe_open(path_to, O_WRONLY | O_TRUNC | O_CREAT);

    copy(fd_from, fd_to);

    safe_close(fd_from);
    safe_close(fd_to);

    if (MASK_V == (opts & MASK_V) )
        printf("'%s' --> '%s'\n", path_from, path_to);
}
