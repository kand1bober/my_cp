#include "header.h"

int main(int argc, char* argv[])
{
    char opts = parse(argc, argv);
    extern int optind;

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


#define BUF_SZ 4096
void copy(int fd_from, int fd_to, size_t file_sz)
{
    if (fd_from < 0 || fd_to < 0)
    {
        perror("Error in opening descriptors");
        exit(1);
    }

    char buf[BUF_SZ] = {};

    size_t bytes_sum = 0, n = 0;
    while (bytes_sum != file_sz)
    {
        n = safe_read(fd_from, buf, BUF_SZ);
        safe_write(fd_to, buf, n);

        bytes_sum += n;
    }
}
#undef BUF_SZ


void configure_and_transfer(const char* path_from, const char* path_to, char opts)
{    
    if (file_exists(path_to))
    {
        if (MASK_I == (opts & MASK_I))
        {
            printf("my_cp: overwrite: '%s'? [y\\n]\n", path_to);

            char ans[101];
            fgets(ans, 100, stdin);
            if (ans[0] == 'y')
            {
                chmod(path_to, get_file_mode(path_to) | 0666);
                transfer(path_from, path_to, opts, 0);
            }
        }
        else if (MASK_F == (opts & MASK_F))
        {
            chmod(path_to, get_file_mode(path_to) | 0666);
            transfer(path_from, path_to, opts, 0);
        }
        else 
        {
            printf("to overwrite file, specify flag -i or -f\n");
            return; 
        }
    }
    else 
        transfer(path_from, path_to, opts, 0666); //create a file
}


void transfer(const char* path_from, const char* path_to, char opts, int mode)
{
    int fd_from = safe_open(path_from, O_RDONLY, 0);
    int fd_to = safe_open(path_to, O_WRONLY | O_TRUNC | O_CREAT, mode);

    copy(fd_from, fd_to, get_file_size(path_from));

    safe_close(fd_from);
    safe_close(fd_to);

    if (MASK_V == (opts & MASK_V) )
        printf("'%s' --> '%s'\n", path_from, path_to);
}
