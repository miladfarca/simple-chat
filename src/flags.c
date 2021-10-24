#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "flags.h"

int flag__print_help = 0;
int flag__print_version = 0;
int flag__process_only = 0; // no gui, no commands.
int flag__silent = 0;       // no ouput form listener.

void parse_args(int argc, char **argv)
{
    for (int i = 1; i < argc; ++i)
    {
        int valid_flag = 0;
        if (strcmp(argv[i], "--help") == 0)
        {
            flag__print_help = 1;
            valid_flag = 1;
        }
        if (strcmp(argv[i], "--version") == 0)
        {
            flag__print_version = 1;
            valid_flag = 1;
        }
        if (strcmp(argv[i], "-p") == 0)
        {
            flag__process_only = 1;
            valid_flag = 1;
        }
        if (strcmp(argv[i], "-s") == 0)
        {
            flag__silent = 1;
            valid_flag = 1;
        }
        else if (!valid_flag)
        {
            printf("Unknown flag: %s\n", argv[i]);
        }
    }
}
