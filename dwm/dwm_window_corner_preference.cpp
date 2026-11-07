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
        L"是->圆角；否->直角",
        L"请选择",
        MB_YESNO | MB_ICONQUESTION | MB_TOPMOST
    );
    
    if (ret == IDYES) {
        DWM_WINDOW_CORNER_PREFERENCE cornerPreference = DWMWCP_ROUND;
        DwmSetWindowAttribute(hwnd, DWMWA_WINDOW_CORNER_PREFERENCE, &cornerPreference, sizeof(cornerPreference));
    }
    else if (ret == IDNO) {
        DWM_WINDOW_CORNER_PREFERENCE cornerPreference = DWMWCP_DONOTROUND;
        DwmSetWindowAttribute(hwnd, DWMWA_WINDOW_CORNER_PREFERENCE, &cornerPreference, sizeof(cornerPreference));
    }
    return 0;
}