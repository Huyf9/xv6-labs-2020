#include "kernel/types.h"
#include "user/user.h"
#include "kernel/fcntl.h"

int
main(int argc, char* argv[])
{
    int p[2];
    pipe(p);
    int pid = fork();
    if(pid == 0) {
        char c;
        if (read(p[0], &c, 1) < 0) {
            fprintf(2, "Usage: read error in process %d.\n", getpid());
            exit(1);
        } else{
            printf("%d: received ping\n", getpid());
        }
        close(0);
        write(p[1], "p", 1);
        exit(0);
    } else {
        char c;
        close(0);
        write(p[1], "p", 1);
        wait(0);

        if (read(p[0], &c, 1) < 0) {
            fprintf(2, "Usage: read error in process %d.\n", getpid());
            exit(1);
        } else {
            printf("%d: received pong\n", getpid());
        }
    }
    exit(0);
}

