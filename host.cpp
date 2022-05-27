#include <boost/format.hpp>
#include <string>
#include <cstdio>
#include <tchar.h>
#include <Windows.h>

using namespace std;
using boost::format;
using boost::io::group;

TCHAR* StringToTChar(string& s) {
    size_t ori_s = 0, conv_s = 0;
    wchar_t* t = NULL;

    ori_s = strlen(s.c_str()) + 1;
    t = new wchar_t[ori_s];
    mbstowcs_s(&conv_s, t, ori_s, s.c_str(), _TRUNCATE);
    
    return (TCHAR*)t;
}

int _tmain(int argc, TCHAR* argv[]) {
    string key_s = "cell fender";
    string thres = "0.80";
    string class_id = "1";

    string wc_p = "C:/darknet_c";
    string dn_p = "C:/darknet";
    string pc_p = "C:/darknet_p";

    string wc_cb = str(format("%1%/test.exe %2%") % wc_p % key_s);
    string dn_cb = str(format("cmd.exe /c cd %1% && darknet.exe detector test data/obj.data cfg/yolo-obj.cfg backup/yolo-obj_4000.weights -ext_output -dont_show -out result.json < data/img.txt") % dn_p);
    string pc_cb = str(format("%1%/judge.exe %2% %3%") % pc_p % thres % class_id);

    STARTUPINFO wc = { 0, };
    STARTUPINFO dn = { 0, };
    STARTUPINFO pc = { 0, };

    PROCESS_INFORMATION wc_pr;
    PROCESS_INFORMATION dn_pr;
    PROCESS_INFORMATION pc_pr;

    DWORD wc_r = NULL;
    DWORD dn_r = NULL;
    DWORD pc_r = NULL;

    TCHAR* wc_c = StringToTChar(wc_cb);
    TCHAR* dn_c = StringToTChar(dn_cb);
    TCHAR* pc_c = StringToTChar(pc_cb);

    wc.cb = sizeof(wc);
    dn.cb = sizeof(dn);
    pc.cb = sizeof(pc);

    CreateProcess(NULL, wc_c, NULL, NULL, TRUE, 0, NULL, NULL, &wc, &wc_pr);
    WaitForSingleObject(wc_pr.hProcess, INFINITE);
    CloseHandle(wc_pr.hThread);
    
    CreateProcess(L"c:/windows/system32/cmd.exe", dn_c, NULL, NULL, TRUE, 0, NULL, NULL, &dn, &dn_pr);
    WaitForSingleObject(dn_pr.hProcess, INFINITE);
    CloseHandle(dn_pr.hThread);

    CreateProcess(NULL, pc_c, NULL, NULL, TRUE, 0, NULL, NULL, &pc, &pc_pr);
    WaitForSingleObject(pc_pr.hProcess, INFINITE);
    CloseHandle(pc_pr.hThread);


    GetExitCodeProcess(wc_pr.hProcess, &wc_r);
    GetExitCodeProcess(dn_pr.hProcess, &dn_r);
    GetExitCodeProcess(pc_pr.hProcess, &pc_r);

    if (wc_r == -1 || dn_r == -1 || pc_r == -1)
        return -1;

    CloseHandle(wc_pr.hProcess);
    CloseHandle(dn_pr.hProcess);
    CloseHandle(pc_pr.hProcess);

    return 0;
}