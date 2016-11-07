#include <stdio.h>

extern void missing_function();

int main(int argc, const char* argv[])
{
    if (argc > 1) {
        printf("Attempting to call missing_function...\n");
        missing_function();
    }
    printf("Done!\n");
    return 0;
}
