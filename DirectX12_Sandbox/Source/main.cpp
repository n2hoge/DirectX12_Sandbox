#include <Windows.h>
#ifdef _DEBUG
#include <iostream>
#endif

//	@brief	コンソール画面にフォーマット付き文字列を表示
//	@param	format フォーマット（%d や %f）
//	@param	可変長引数
//	@remarks	この関数はデバッグ用であり、デバッグ時にしか動作しない
void DebugOutputFormatString(const char* format, ...)
{
#ifdef _DEBUG
	va_list valist;
	va_start(valist, format);
	vprintf(format, valist);
	va_end(valist);
#endif
}

//	ウィンドウプロシージャの呼び出し
LRESULT WindowProcedure(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	//	ウィンドウが破棄されたら呼ばれる
	if (msg == WM_DESTROY)
	{
		PostQuitMessage(0);		//	OSに対してアプリの終わりを伝える
		return 0;
	}
	return DefWindowProc(hwnd, msg, wparam, lparam);		//	既定の処理を行う
}

// ウィンドウサイズ
const unsigned int	window_width = 1280;	//	ウィンドウサイズ幅
const unsigned int	window_height = 720;	//	ウィンドウサイズ高さ


#ifdef _DEBUG
int main()
{
#else
int WINAPI WinMain(HINSTAJCE, HINSTANCE, LPSTR, int)
{
#endif
	DebugOutputFormatString("Show window test.");

	//	ウィンドウクラスの生成＆登録
	WNDCLASSEX w = {};

	w.cbSize = sizeof(WNDCLASSEX);
	w.lpfnWndProc = (WNDPROC)WindowProcedure;		//	コールバック関数の指定
	//w.lpszClassName = _T("DX12_Sandbox");			//	アプリケーションクラス名
	w.lpszClassName = L"DX12_Sandbox";			//	アプリケーションクラス名
	w.hInstance = GetModuleHandle(nullptr);			//	ハンドルの取得

	RegisterClassEx(&w);		//	アプリケーションクラス（ウィンドウクラスの指定をOSに伝える）

	RECT wrc = { 0, 0, window_width, window_height };	// ウィンドウサイズを決める
	AdjustWindowRect(&wrc, WS_OVERLAPPEDWINDOW, false);	// ウィンドウサイズを補正

	// ウィンドウクラスの生成
	HWND hwnd = CreateWindow(
		w.lpszClassName,		//	クラス名指定 
		//_T("DX12_Sandbox")		//	タイトルバー表示テキスト
		L"DX12_Sandbox",
		WS_OVERLAPPEDWINDOW,		//	タイトルバーと境界線があるウィンドウを指定
		CW_USEDEFAULT,			//	表示x座標をOSに任せる
		CW_USEDEFAULT,			//	表示y座標をOSに任せる
		wrc.right - wrc.left,	//	ウィンドウ幅
		wrc.bottom - wrc.top,	//	ウィンドウ高さ
		nullptr,				//	親ウィンドウハンドル
		nullptr,				//	メニューハンドル
		w.hInstance,			//	呼び出しアプリケーションハンドル
		nullptr					//	追加パラメーター
	);

	// ウィンドウ表示
	ShowWindow(hwnd, SW_SHOW);	

	getchar();
	return 0;
}
