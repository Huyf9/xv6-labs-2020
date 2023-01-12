#include "kernel/types.h"
#include "user/user.h"

void
main(int argc, char *argv[])
{
    int p[2];
    pipe(p);
    char buf;

    if(fork() == 0) {
        close(p[1]);
        if(read(p[0], &buf, 1) < 1) {
            fprintf("child: read error...\n");
            exit(1);
        }

        printf("pong\n");

        close(p[0]);
        write(p[1], &buf, 1);
        exit(0);
    } else {
        buf = 'a';
        close(p[0]);
        write(p[1], &buf, 1);

        close(p[1]);
        if(read(p[0], &buf, 1) < 1) {
            fprintf(2, "parent: read error...\n");
            exit(1);
        }
        printf("ping\n");
        exit(0);
    }
}
