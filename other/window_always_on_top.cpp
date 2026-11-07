#include <windows.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        MessageBoxA(NULL, "No hWnd", "Error", MB_OK | MB_ICONERROR);
        return 1;
    }
    HWND hWnd = (HWND)strtoul(argv[1], NULL, 0);

    int ret = MessageBoxW(
        NULL,
        L"是->置顶；否->不置顶",
        L"请选择",
        MB_YESNO | MB_ICONQUESTION | MB_TOPMOST
    );
    if (ret == IDYES) {
        SetWindowPos(
            hWnd,HWND_TOPMOST,0, 0, 0, 0,
            SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE
        );
    }
    else if (ret == IDNO) {
        SetWindowPos(
            hWnd,HWND_NOTOPMOST,0, 0, 0, 0,
            SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE
        );
    }
    return 0;
}