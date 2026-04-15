#define _GNU_SOURCE
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define STACK_SIZE (1024 * 1024)

static char stack[STACK_SIZE];
char cname[50];

int container_main(void *arg) {
    printf("🚀 Container %s started\n", cname);

    char logfile[100];
    sprintf(logfile, "../logs/%s.log", cname);

    freopen(logfile, "w", stdout);
    freopen(logfile, "w", stderr);

    execlp("/bin/sh", "/bin/sh", NULL);
    perror("exec failed");

    return 1;
}

int start_container(const char *name) {
    strcpy(cname, name);

    int pid = clone(container_main,
                    stack + STACK_SIZE,
                    CLONE_NEWPID | CLONE_NEWUTS | CLONE_NEWNS | SIGCHLD,
                    NULL);

    if (pid < 0) {
        perror("clone failed");
        return -1;
    }

    printf("Container %s running with PID %d\n", name, pid);
    return 0;
}

void show_logs(const char *name) {
    char file[100];
    sprintf(file, "../logs/%s.log", name);

    FILE *fp = fopen(file, "r");
    if (!fp) {
        printf("No logs found\n");
        return;
    }

    char ch;
    while ((ch = fgetc(fp)) != EOF)
        putchar(ch);

    fclose(fp);
}