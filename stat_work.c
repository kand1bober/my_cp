#include "header.h"

bool file_exists(const char* pathname)
{
    struct stat info;
    if (stat(pathname, &info) == 0)
        return true;
    else     
        return false;
}


size_t get_file_size(const char* pathname)
{
    struct stat info;
    stat(pathname, &info);
    
    return (size_t)info.st_size; // signed int -> size_t
}


mode_t get_file_mode(const char* pathname)
{
    struct stat info;
    stat(pathname, &info);
    
    return info.st_mode;
}
