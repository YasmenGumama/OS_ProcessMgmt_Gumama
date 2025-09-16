#include <windows.h>
#include <stdio.h>

int main() {
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    DWORD parentPID = GetCurrentProcessId();

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    printf("Parent PID: %lu\n", parentPID);

    char cmd[100];
    sprintf(cmd, "child_echo.exe %lu", parentPID);

    if (!CreateProcess(
            NULL,   // application name
            cmd,    // command line
            NULL, NULL, FALSE, 0,
            NULL, NULL,
            &si, &pi)) {
        printf("CreateProcess failed (%lu).\n", GetLastError());
        return -1;
    }

    WaitForSingleObject(pi.hProcess, INFINITE);

    DWORD exitCode;
    GetExitCodeProcess(pi.hProcess, &exitCode);
    printf("Child exited with code: %lu\n", exitCode);

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    return 0;
}
