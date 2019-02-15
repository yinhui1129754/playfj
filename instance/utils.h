#pragma once
namespace utils {
	struct usePoint
	{
		float x;
		float y;
	};
	template<class T>
	bool vecRemove(vector<T *> & vc, T * sp) {
		vector<T *>::iterator s = find(vc.begin(),vc.end(),sp);
		if (s == vc.end()) {
			return false;
		}
		vc.erase(s);
		return true;
	}
	extern LPWSTR user_stringToLPWSTR(string orig);
	extern string user_LPWSTRTostring(LPWSTR lpw);
	extern LPCSTR user_LPWSTRToLPCSTR(LPWSTR lpw);
	extern LPWSTR user_LPCSTRToLPWSTR(LPCSTR lpc);
	extern VOID DebugOut(LPCTSTR str, int code);
	extern VOID AlertOut(LPCTSTR str, int code);
	template <typename T>
	string user_coutTostring(T a) {
		stringstream  ostring;
		ostring << a;
		return ostring.str();
	};
	extern int GetId();
	/*template<typename t>
void log(const t &v1) {
	stringstream ss;
	ss << v1;
	LPWSTR a = g_chartowchar2(ss.str().c_str());
	OutputDebugString(a);
}*/
	struct useSpSt {
		float x; 
		float y;
		int width; 
		int height; 
		float angle;
		float pivotX; 
		float pivotY;
	};
}