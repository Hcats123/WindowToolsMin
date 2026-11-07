#include <Windows.h>
#include <string>
#include <vector>
#include <stdlib.h>
#include <shellapi.h>

void OpenInExplorer(const std::wstring& filePath) {
    if (filePath.empty()) return;
    // 构造 /select 完整路径参数，用双引号包裹路径
    std::wstring params = L"/select,\"" + filePath + L"\"";
    ShellExecuteW(NULL, L"open", L"explorer.exe", params.c_str(), NULL, SW_SHOWNORMAL);
}
std::wstring GetProcessPathFromHwnd(HWND hwnd) {
    if (!IsWindow(hwnd)) return L"";

    DWORD pid = 0;
    GetWindowThreadProcessId(hwnd, &pid);
    if (pid == 0) return L"";

    // 以最小权限打开进程，获取查询信息的权限
    HANDLE hProcess = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, FALSE, pid);
    if (!hProcess) return L"";

    WCHAR path[MAX_PATH] = { 0 };
    DWORD size = MAX_PATH;
    // 获取完整路径
    BOOL ok = QueryFullProcessImageNameW(hProcess, 0, path, &size);
    CloseHandle(hProcess);
    return ok ? std::wstring(path) : L"";
}


int main(int argc, char* argv[]) {
    if (argc < 2) {
        MessageBoxA(NULL, "No hWnd", "Error", MB_OK | MB_ICONERROR);
        return 1;
    }
    HWND hwnd = (HWND)strtoul(argv[1], NULL, 0);

    std::wstring path = GetProcessPathFromHwnd(hwnd);
    if (path.empty()) {
        MessageBoxA(NULL, "Failed to get process path", "Error", MB_OK | MB_ICONERROR);
        return 1;
    }
    else {
        OpenInExplorer(path);
    }
    return 0;
}