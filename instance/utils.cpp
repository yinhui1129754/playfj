#include "../stdafx.h"
#include "utils.h"

LPWSTR utils::user_stringToLPWSTR(std::string orig) {

	int lng = orig.length();
	LPWSTR d = (LPWSTR)malloc(sizeof(PWSTR)*lng);
	memset(d, 0, sizeof(PWSTR)*lng);
	MultiByteToWideChar(CP_ACP, 0, orig.c_str(), lng, d, lng * sizeof(PWSTR));
	return d;
}
string utils::user_LPWSTRTostring(LPWSTR lpw) {
	int lng = lstrlenW(lpw);

	LPSTR d = (LPSTR)malloc(sizeof(PSTR)*lng);
	memset(d, 0, sizeof(PSTR)*lng);
	WideCharToMultiByte(CP_OEMCP, NULL, lpw, -1, d, sizeof(PSTR)*lng, NULL, FALSE);
	string q = d;
	return q;
}
LPCSTR utils::user_LPWSTRToLPCSTR(LPWSTR lpw) {
	string s1 = utils::user_LPWSTRTostring(lpw);
	return (s1.c_str());
}
LPWSTR utils::user_LPCSTRToLPWSTR(LPCSTR lpc) {
	string s1 = lpc;
	return utils::user_stringToLPWSTR(s1);
}
VOID utils::DebugOut(LPCTSTR str, int code) {
	wchar_t buffer[1024];
	wsprintf(buffer, str, code);
	::OutputDebugString(buffer);
};
VOID utils::AlertOut(LPCTSTR str, int code) {
	wchar_t buffer[1024];
	wsprintf(buffer, str, code);
	MessageBox(NULL, buffer, L"title", MB_OK);
};
int utils::GetId() {
	static int i = 0;
	i++;
	return i;
}
