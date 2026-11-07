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

    CHOOSECOLOR cc = {};
    COLORREF custom[16] = {};

    cc.lStructSize  = sizeof(cc);
    cc.lpCustColors = custom;
    
    if (ChooseColor(&cc)) {
        COLORREF c = cc.rgbResult;
        DwmSetWindowAttribute(hwnd, DWMWA_CAPTION_COLOR, &c, sizeof(c));
        // 用 GetRValue(c) / GetGValue(c) / GetBValue(c) 取分量
    }
    return 0;
}