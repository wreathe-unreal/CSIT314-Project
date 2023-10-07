#pragma once
#include <windows.h>
#include <tchar.h>


inline LPCWSTR StringToLPCWSTR(const std::string& s)
{
    int slength = (int)s.length() + 1;
    int len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
    wchar_t* buf = new wchar_t[len];
    MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
    return buf;
}