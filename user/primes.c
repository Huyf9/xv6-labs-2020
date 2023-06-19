#include "kernel/types.h"
#include "user/user.h"
#include "kernel/fcntl.h"

void 
primes(int p[]) {
    int prime;
    if(read(p[0], &prime, 4)) {
        printf("prime %d\n", prime);
    } else {
        exit(0);
    } 

    int np[2];
    pipe(np);
    int num;
    while (read(p[0], &num, 4)) {
        if (num % prime != 0) 
            write(np[1], &num, 4);

    }
    close(np[1]);
    int pid = fork();
    if(pid == 0) {
        
        primes(np);
        exit(0);
    } else {
        wait(0);
    }
    exit(0);
}

int
main(int argc, char* argv[]) {
    int p[2];
    pipe(p);
    for(int i = 2; i <= 35; i++) 
        write(p[1], &i, 4);

    close(p[1]);
    primes(p);
    exit(0);
}