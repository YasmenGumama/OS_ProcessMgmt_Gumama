#include <windows.h>
#include <stdio.h>

int main() {
    STARTUPINFO si[2];
    PROCESS_INFORMATION pi[2];
    DWORD parentPID = GetCurrentProcessId();

    printf("Parent PID: %lu\n", parentPID);

    for (int i = 0; i < 2; i++) {
        ZeroMemory(&si[i], sizeof(si[i]));
        si[i].cb = sizeof(si[i]);
        ZeroMemory(&pi[i], sizeof(pi[i]));

        char cmd[100];
        sprintf(cmd, "child_echo.exe %lu", parentPID);

        if (!CreateProcess(NULL, cmd, NULL, NULL, FALSE, 0, NULL, NULL, &si[i], &pi[i])) {
            printf("Failed to create child %d (%lu).\n", i+1, GetLastError());
            return -1;
        }
    }

    // Wait for both
    HANDLE handles[2] = { pi[0].hProcess, pi[1].hProcess };
    WaitForMultipleObjects(2, handles, TRUE, INFINITE);

    for (int i = 0; i < 2; i++) {
        DWORD exitCode;
        GetExitCodeProcess(pi[i].hProcess, &exitCode);
        printf("Child %d exited with %lu\n", i+1, exitCode);

        CloseHandle(pi[i].hProcess);
        CloseHandle(pi[i].hThread);
    }

    return 0;
}
