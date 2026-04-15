#include <stdio.h>
#include <string.h>

int start_container(const char *name);
void show_logs(const char *name);

int main(int argc, char *argv[]) {

    if (argc < 2) {
        printf("Usage:\n");
        printf("./engine start <name>\n");
        printf("./engine logs <name>\n");
        return 1;
    }

    if (strcmp(argv[1], "start") == 0 && argc >= 3) {
        start_container(argv[2]);
    }
    else if (strcmp(argv[1], "logs") == 0 && argc >= 3) {
        show_logs(argv[2]);
    }
    else {
        printf("Invalid command\n");
    }

    return 0;
}