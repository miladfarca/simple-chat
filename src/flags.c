#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "flags.h"

int flag__print_help = 0;

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
        else if (!valid_flag)
        {
            printf("Unknown flag: %s\n", argv[i]);
        }
    }
}
