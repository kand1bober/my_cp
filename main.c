#include "header.h"

int main(int argc, char* argv[])
{
    char opts = parse(argc, argv);
    extern int optind;

    if (MASK_F == (opts & MASK_F))
        opts = 0; // delete all options

    if ((argc - optind) < 2)
    {
        perror("Wrong using of cp\n");
        exit(0);
    }   

    char* lines[argc - optind] = {}; // --verbous lines 
    int lines_count = 0;

    if ((argc - optind) == 2) // copy file to fie
    {
        configure_and_transfer(argv[optind], argv[optind + 1], opts, lines, &lines_count);
    }
    else // copy files to directory 
    {
        char pathname[MAX_PATH_LEN];
        for (int i = optind; i < argc - 1; i++)
        {
            snprintf(pathname, MAX_PATH_LEN, "%s/%s", argv[argc - 1], argv[i]);  
            configure_and_transfer(argv[i], pathname, opts, lines, &lines_count);
        }
    }

    if (MASK_V == (opts & MASK_V))
    {
        show_verbose(lines, &lines_count);
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


void configure_and_transfer(const char* path_from, const char* path_to, char opts, char** lines, int* lines_count)
{
    //how to check if such file already exists ?
    if (MASK_I == (opts & MASK_I)) // add checking for already existing files
    {
        printf("my_cp: overwrite: '%s' ? y\\n\n", path_to);

        char ans = 0;
        ans = getchar(); getchar(); // to skip '\n' 
        if (ans == 'y' || ans == '\n')
        {
            transfer(path_from, path_to, opts, lines, lines_count);
        }
    }
    else 
    {
        transfer(path_from, path_to, opts, lines, lines_count);
    }
}


void transfer(const char* path_from, const char* path_to, char opts, char** lines, int* lines_count)
{

    int fd_from = safe_open(path_from, O_RDONLY);
    int fd_to = safe_open(path_to, O_WRONLY | O_TRUNC);

    copy(fd_from, fd_to);

    safe_close(fd_from);
    safe_close(fd_to);

    if (MASK_V == (opts & MASK_V) )
    {
        size_t len = snprintf(NULL, 0, "'%s' --> '%s'", path_from, path_to) + 1;

        lines[*lines_count] = (char*)malloc(len); 
        if (lines[*lines_count] == NULL)
        {
            perror("Error in allocating memory\n");
            exit(1);
        }

        snprintf(lines[*lines_count], len, "'%s' --> '%s'", path_from, path_to);
        (*lines_count)++;
    }
}


void show_verbose(char** lines, int* lines_count)
{    
    for (int i = 0; i < *lines_count; i++)
    {
        printf("%s\n", lines[i]);
        free(lines[i]);
    }
}
