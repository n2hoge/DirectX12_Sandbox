#include <Windows.h>
#ifdef _DEBUG
#include <iostream>
#endif

//	@brief	�R���\�[����ʂɃt�H�[�}�b�g�t���������\��
//	@param	format �t�H�[�}�b�g�i%d �� %f�j
//	@param	�ϒ�����
//	@remarks	���̊֐��̓f�o�b�O�p�ł���A�f�o�b�O���ɂ������삵�Ȃ�
void DebugOutputFormatString(const char* format, ...)
{
#ifdef _DEBUG
	va_list valist;
	va_start(valist, format);
	vprintf(format, valist);
	va_end(valist);
#endif
}

//	�E�B���h�E�v���V�[�W���̌Ăяo��
LRESULT WindowProcedure(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	//	�E�B���h�E���j�����ꂽ��Ă΂��
	if (msg == WM_DESTROY)
	{
		PostQuitMessage(0);		//	OS�ɑ΂��ăA�v���̏I����`����
		return 0;
	}
	return DefWindowProc(hwnd, msg, wparam, lparam);		//	����̏������s��
}

// �E�B���h�E�T�C�Y
const unsigned int	window_width = 1280;	//	�E�B���h�E�T�C�Y��
const unsigned int	window_height = 720;	//	�E�B���h�E�T�C�Y����


#ifdef _DEBUG
int main()
{
#else
int WINAPI WinMain(HINSTAJCE, HINSTANCE, LPSTR, int)
{
#endif
	DebugOutputFormatString("Show window test.");

	//	�E�B���h�E�N���X�̐������o�^
	WNDCLASSEX w = {};

	w.cbSize = sizeof(WNDCLASSEX);
	w.lpfnWndProc = (WNDPROC)WindowProcedure;		//	�R�[���o�b�N�֐��̎w��
	//w.lpszClassName = _T("DX12_Sandbox");			//	�A�v���P�[�V�����N���X��
	w.lpszClassName = L"DX12_Sandbox";			//	�A�v���P�[�V�����N���X��
	w.hInstance = GetModuleHandle(nullptr);			//	�n���h���̎擾

	RegisterClassEx(&w);		//	�A�v���P�[�V�����N���X�i�E�B���h�E�N���X�̎w���OS�ɓ`����j

	RECT wrc = { 0, 0, window_width, window_height };	// �E�B���h�E�T�C�Y�����߂�
	AdjustWindowRect(&wrc, WS_OVERLAPPEDWINDOW, false);	// �E�B���h�E�T�C�Y��␳

	// �E�B���h�E�N���X�̐���
	HWND hwnd = CreateWindow(
		w.lpszClassName,		//	�N���X���w�� 
		//_T("DX12_Sandbox")		//	�^�C�g���o�[�\���e�L�X�g
		L"DX12_Sandbox",
		WS_OVERLAPPEDWINDOW,		//	�^�C�g���o�[�Ƌ��E��������E�B���h�E���w��
		CW_USEDEFAULT,			//	�\��x���W��OS�ɔC����
		CW_USEDEFAULT,			//	�\��y���W��OS�ɔC����
		wrc.right - wrc.left,	//	�E�B���h�E��
		wrc.bottom - wrc.top,	//	�E�B���h�E����
		nullptr,				//	�e�E�B���h�E�n���h��
		nullptr,				//	���j���[�n���h��
		w.hInstance,			//	�Ăяo���A�v���P�[�V�����n���h��
		nullptr					//	�ǉ��p�����[�^�[
	);

	// �E�B���h�E�\��
	ShowWindow(hwnd, SW_SHOW);	

	getchar();
	return 0;
}
