#include<windows.h>
#include<stdio.h>
#include<opencv2/opencv.hpp> 
#include<string>
typedef char  (__cdecl *recog_model_init)(char const*, int, int, bool);
typedef char* (__cdecl* ocr_recognize_line)(cv::Mat&, bool);
typedef char  (__cdecl* switch_to_language)(int);
/*
0:zh
1:jp
2:latin
3:hindi	
*/ 
#define WINAPIV    __cdecl
#pragma comment (lib,"zlib.lib") 
#pragma comment (lib,"ippicvmt.lib") 
#pragma comment (lib,"ippiw.lib") 
#pragma comment (lib,"ittnotify.lib") 
#pragma comment (lib,"libtiff.lib") 
#pragma comment (lib,"libpng.lib") 
#pragma comment (lib,"libwebp.lib") 
#pragma comment (lib,"libopenjp2.lib") 
#pragma comment (lib,"libjpeg-turbo.lib") 
#pragma comment (lib,"opencv_core460.lib") 
#pragma comment (lib,"opencv_ts460.lib")  
#pragma comment (lib,"opencv_stitching460.lib")  
#pragma comment (lib,"opencv_photo460.lib")  
#pragma comment (lib,"opencv_ts460.lib")  
#pragma comment (lib,"opencv_highgui460.lib")  
#pragma comment (lib,"opencv_imgproc460.lib")  
#pragma comment (lib,"opencv_imgcodecs460.lib")  
std::wstring StrToWStr(std::string& strString, UINT uCodePage)
{
	int lenWStr = 0;
	std::wstring result;

	lenWStr = MultiByteToWideChar(uCodePage, NULL, strString.c_str(), strString.size(), NULL, NULL);
	wchar_t* buffer = new wchar_t[lenWStr + 1];
	MultiByteToWideChar(uCodePage, NULL, strString.c_str(), strString.size(), buffer, lenWStr);
	buffer[lenWStr] = '\0';

	result.append(buffer);
	delete[] buffer;
	return result;
}
std::string WStrToStr(std::wstring& wstrString, UINT uCodePage)
{
	int lenStr = 0;
	std::string result;

	lenStr = WideCharToMultiByte(uCodePage, NULL, wstrString.c_str(), wstrString.size(), NULL, NULL, NULL, NULL);
	char* buffer = new char[lenStr + 1];
	WideCharToMultiByte(uCodePage, NULL, wstrString.c_str(), wstrString.size(), buffer, lenStr, NULL, NULL);
	buffer[lenStr] = '\0';

	result.append(buffer);
	delete[] buffer;
	return result;
}
int main() {
	SetCurrentDirectory(L"C:\\Users\\11737\\AppData\\Local\\youdao\\dict\\Application\\9.1.5.0");
	auto dll = LoadLibrary(L"yocr.dll"); 
	auto _recog_model_init = (recog_model_init)GetProcAddress(dll,  "?recog_model_init@YoudaoOCR@@YA_NPBDHH_N@Z");
	auto _ocr_recognize_line = (ocr_recognize_line)GetProcAddress(dll, "?ocr_recognize_line@YoudaoOCR@@YAPADABVMat@cv@@_N@Z");
	auto _switch_to_language = (switch_to_language)GetProcAddress(dll, "?switch_to_language@YoudaoOCR@@YA_NH@Z"); 

	int lang = 1;
	_switch_to_language(lang);
	_recog_model_init("C:\\Users\\11737\\AppData\\Local\\youdao\\dict\\Application\\9.1.5.0\\recognition", 1, lang,0); 
	auto mat=cv::imread("C:\\Users\\11737\\source\\repos\\yocr_test\\Release\\1.jpg");
	auto res=_ocr_recognize_line(mat, 0);
	 
	std::string s = res;
	auto ws = StrToWStr(s, 0xFDE9u);
	s = WStrToStr(ws, 936);
	printf("%s\n", s.c_str());
	 
	Sleep(100000000000);
}