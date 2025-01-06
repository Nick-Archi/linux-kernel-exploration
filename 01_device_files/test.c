#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
    int dev = open("/dev/chardev", O_RDONLY);
    if(dev == -1)
    {
        printf("Opening unsucessful\n");
        return -1;
    }
    printf("Opening successful\n");
    close(dev);
    return 0;
}
