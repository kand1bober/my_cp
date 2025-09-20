#include "header.h"

char parse(int argc, char* argv[])
{
    const char* optstring = "vif";
    extern int optind;

    char opts = 0;  
    int opt = 0;

    while (1)
    {        
        opt = getopt(argc, argv, optstring);
        if (opt < 0)
            break;

        switch (opt)
        {
            case 'v':
            {
                opts |= MASK_V; 
                break;
            }
            case 'i':
            {
                opts |= MASK_I;
                break;
            }
            case 'f':
            {
                opts |= MASK_F;
                break;
            }
            default:
            {
                printf("Wrong argument passed\n");
                break;
            }
        }
    }
    
    return opts;
}
