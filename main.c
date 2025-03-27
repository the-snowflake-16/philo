#include <unistd.h>

int main()
{
    write(1, "HELLO\n", 6);
    return(0);
}