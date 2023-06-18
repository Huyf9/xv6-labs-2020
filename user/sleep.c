#include "kernel/types.h"
#include "user/user.h"
#include "kernel/fcntl.h"

int
main(int argc, char* argv[])
{
    if(argc < 2) {
        fprintf(2, "Usage: expect one argument but got zero.\n");
        exit(1);
    }
    int time = atoi(argv[1]);
    sleep(time);
    exit(0);
}