#include <Windows.h>
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE preHinst, PSTR cmdLine, int cmdShow) {
	//Dinh nghia cau truc lop cua so
	WNDCLASS wndClass;
	static TCHAR appName[] = TEXT("Application");

	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.lpfnWndProc = WndProc;

	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hInstance = hInst;
	wndClass.hIcon = LoadIcon(hInst, appName);
	wndClass.hCursor = LoadCursor(NULL, IDC_HAND);
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndClass.lpszMenuName = NULL;
	wndClass.lpszClassName = appName;

	//Dang ky lop cua so
	if (!RegisterClass(&wndClass)) {
		MessageBox(NULL, TEXT("Error"), TEXT("Messager"), MB_OK | MB_ICONERROR);
		return 0;
	}

	//Tao cua so
	HWND hwnd = CreateWindow(appName, TEXT("Cua so dau tien"), WS_OVERLAPPEDWINDOW, 
		50, 50, 800, 800, NULL, NULL, hInst, NULL);
	ShowWindow(hwnd, cmdShow);
	UpdateWindow(hwnd);

	//Tao vong lap thong diep
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}

//Dinh nghia thu tuc cua so
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg)
	{
	case WM_CLOSE:
		if (MessageBox(NULL, TEXT("Do you want to exit?"), TEXT("Question"), MB_YESNO | MB_ICONQUESTION) == IDYES)
			PostQuitMessage(0);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	default:
		break;
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}
