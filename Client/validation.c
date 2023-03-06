#include "client.h"

char is_valid_port(const char *str) 
{
    if(!str)
        return 0;

    char *endptr;
    unsigned long port = strtoul(str, &endptr, 10);
    if (endptr == str || *endptr != '\0') {
        printf("Client>> [%s] is not a valid Port.\n", str);
        return 0;
    }
    if(!(port >= 1 && port <= 65535))
    {
        printf("Client>> [%s] is not a valid Port.\n", str);
        return 0;
    }
    return 1;
}

char is_valid_ip(const char *str)
{
    if(!str)
        return 0;
        
    struct in_addr addr;
    if (inet_pton(AF_INET, str, &addr) != 1) 
    {
        printf("Client>> [%s] is not a valid IPv4 address.\n", str);
        return 0;
    }
    return 1;
}