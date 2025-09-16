#include <windows.h>
#include <stdio.h>

int main() {
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    DWORD parentPID = GetCurrentProcessId();

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    printf("Parent PID: %lu starting 'cmd /c dir'\n", parentPID);

    if (!CreateProcess(NULL, "cmd /c dir", NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
        printf("CreateProcess failed (%lu).\n", GetLastError());
        return -1;
    }

    WaitForSingleObject(pi.hProcess, INFINITE);

    DWORD exitCode;
    GetExitCodeProcess(pi.hProcess, &exitCode);

    printf("Replacing parent exit with child exit code: %lu\n", exitCode);

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    return exitCode;
}
