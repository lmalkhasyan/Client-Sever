#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *execute(const char *cmd)
{
    FILE *fp = popen(cmd, "r");
    if (!fp)
    {
        printf("Error executing command");
        return NULL;
    }

    char *line = NULL;
    size_t len = 0;
    ssize_t nread;
    size_t buf_size = 0;
    char *buf = NULL;

    while ((nread = getline(&line, &len, fp)) != -1)
    {
        buf_size += nread;
        buf = realloc(buf, buf_size + 1);
        if (buf == NULL)
        {
            fprintf(stderr, "Realoc Error: out of memory\n");
            return NULL;
        }
        strcat(buf + buf_size - nread, line);
        buf[buf_size] = '\0';
    }
    if (!buf)
    {
        buf = malloc(sizeof("[Command produced no output]\n") + 1);
        if (!buf)
        {
            printf("Error: out of memory\n");
            return NULL;
        }
        strcpy(buf, "[Command produced no output]\n");
    }
    if (line)
    {
        free(line);
    }
    pclose(fp);
    return buf;
}