#include <Windows.h>
#include <stdio.h>
#include <string.h>


int main() {
char *input = (char *)malloc(256 * sizeof(char));
while(1) {
printf("Shell>> ");
if (fgets(input, 256, stdin) != NULL) {

    input[strcspn(input, "\n")] = 0;
    if (strcmp(input, "exit") == 0) {
        printf("Goodbye!");
        break;
    }

    char *args = input;
    char commandLine[256]; // Adjust size as needed
    snprintf(commandLine, sizeof(commandLine), "cmd /c %s", input); // Copy input safely
    STARTUPINFOA si = { sizeof(STARTUPINFO) };
    PROCESS_INFORMATION pi;    

    if (!CreateProcessA(NULL, commandLine, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
        printf("Error: Unable to execute command. Error code: %lu\n", GetLastError());
    } else {
        WaitForSingleObject(pi.hProcess, INFINITE);
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);

    }

}
} 
free(input);
return 1;
}
