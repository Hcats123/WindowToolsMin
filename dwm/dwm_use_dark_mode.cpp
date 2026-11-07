#include <windows.h>
#include <commdlg.h>
#pragma comment(lib, "comdlg32.lib")
#include <dwmapi.h>
#pragma comment(lib, "dwmapi.lib")


int main(int argc, char* argv[]) {
    if (argc < 2) {
        MessageBoxA(NULL, "No hWnd", "Error", MB_OK | MB_ICONERROR);
        return 1;
    }
    HWND hwnd = (HWND)strtoul(argv[1], NULL, 10);

    int ret = MessageBoxW(
        NULL,
        L"是->深色；否->浅色",
        L"请选择",
        MB_YESNO | MB_ICONQUESTION | MB_TOPMOST
    );
    
    if (ret == IDYES) {
        BOOL darkMode = TRUE;
        DwmSetWindowAttribute(hwnd, DWMWA_USE_IMMERSIVE_DARK_MODE, &darkMode, sizeof(darkMode));
    }
    else if (ret == IDNO) {
        BOOL darkMode = FALSE;
        DwmSetWindowAttribute(hwnd, DWMWA_USE_IMMERSIVE_DARK_MODE, &darkMode, sizeof(darkMode));
    }
    return 0;
}