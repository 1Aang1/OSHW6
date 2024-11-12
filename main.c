#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
int main(int argc, char **argv) {
    int c, n, id, id2;

    while ((c = getopt(argc, argv, "f:")) != -1) {
        switch (c) {
            case 'f':
                n = atoi(optarg);
                break;
            default:
                fprintf(stderr, "Usage: %s -f <number_of_processes>\n", argv[0]);
                return 1;
        }
    }

    for (int i = 0; i < n; i++) {
        id = fork();
        if (id < 0) {
            perror("ERROR");
            return 1;
        } else if (id == 0) {
            printf("PID: %d, PPID: %d\n", getpid(), getppid());

            for (int j = 0; j < i; j++) {
                id2 = fork();
                if (id2 < 0) {
                    perror("ERROR");
                    return 1;
                } else if (id2 == 0) {
                    printf("PID: %d, PPID: %d\n", getpid(), getppid());
                    exit(0);
                }
                wait(NULL);
            }
            exit(0);
        }
        wait(NULL);
    }

    return 0;
}