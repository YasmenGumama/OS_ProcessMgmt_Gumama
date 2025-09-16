#include <windows.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
    DWORD pid = GetCurrentProcessId();

    if (argc < 2) {
        printf("Child PID: %lu | No parent PID passed.\n", pid);
    } else {
        printf("Child PID: %lu | Parent PID: %s\n", pid, argv[1]);
    }
Sleep(20000);  // 20000 ms = 20 seconds

    printf("Child process %lu exiting now.\n", pid);

    return 0;
}
