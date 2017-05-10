#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

int     main(int argc, char **argv)
{
    char    *line;

    if (argc != 2)
        return (0);
    FILE *fp = fopen(argv[1], "r");
    while (get_next_line(fileno(fp), &line))
    {
        printf("\nline is --> %s\n", line);
        free(line);
    }
    fclose(fp);
    return (0);
}
