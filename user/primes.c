#include "kernel/types.h"
#include "user/user.h"

void
sieve(int left_fd)
{
    int p;
    int n;

    while (read(left_fd, &p, sizeof(p)) == sizeof(p)) {
        printf("prime %d\n", p);

        int right_fd[2];
        pipe(right_fd);

        int pid = fork();

        if (pid == 0) {
            close(right_fd[1]);
            close(left_fd);
            left_fd = right_fd[0];
            continue;
        }

        close(right_fd[0]);

        while (read(left_fd, &n, sizeof(n)) == sizeof(n)) {
            if (n % p != 0) {
                write(right_fd[1], &n, sizeof(n));
            }
        }

        close(left_fd);
        close(right_fd[1]);
        wait(0);
        exit(0);
    }

    close(left_fd);
    exit(0);
}

int
main(int argc, char *argv[])
{
    if (argc < 2) {
        printf("Usage: primes [num]\n");
        exit(1);
    }

    int num = atoi(argv[1]);

    if (num < 2)
        exit(0);

    int fd[2];
    pipe(fd);

    int pid = fork();

    if (pid == 0) {
        close(fd[1]);
        sieve(fd[0]);
        exit(0);
    }

    close(fd[0]);

    for (int i = 2; i <= num; i++) {
        write(fd[1], &i, sizeof(i));
    }

    close(fd[1]);
    wait(0);
    exit(0);
}
