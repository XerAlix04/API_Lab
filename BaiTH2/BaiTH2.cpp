// BaiTH2.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "BaiTH2.h"

#define MAX_LOADSTRING 100

// Define IDs for your controls (good practice)
#define ID_GROUPBOX1 1001
#define ID_GROUPBOX2 1002
#define ID_GROUPBOX3 1003

// Button IDs (start with a base and add an offset)
#define ID_HINH_BASE 2001
#define ID_MNCOLOR_BASE 3001
#define ID_DVCOLOR_BASE 4001

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
HWND btnHinh[2], btnMNColor[5], btnDVColor[5];  // Button arrays
COLORREF color[5] = { RGB(255,0,0), RGB(0,255,0), RGB(0,0,255), RGB(255,255,0), RGB(255,165,0) }; // Color array
int selectedShape = 0; // 1: Circle, 2: Square

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_BAITH2, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_BAITH2));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_BAITH2));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_BAITH2);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static int selectedShape = 0; // 1: Circle, 2: Square
    static POINT ptStart, ptEnd;
    static COLORREF bgColor = RGB(255, 255, 255);
    static COLORREF borderColor = RGB(0, 0, 0);
    static COLORREF colorOptions[5] = { RGB(255,0,0), RGB(0,255,0), RGB(0,0,255), RGB(255,255,0), RGB(255,0,255) };

    switch (message)
    {
    case WM_CREATE:
        CreateWindowW(L"BUTTON", L"Hình", WS_VISIBLE | WS_CHILD | BS_GROUPBOX, 10, 10, 150, 100, hWnd, NULL, hInst, NULL);
        CreateWindowW(L"BUTTON", L"Chọn màu nền", WS_VISIBLE | WS_CHILD | BS_GROUPBOX, 180, 10, 170, 100, hWnd, NULL, hInst, NULL);
        CreateWindowW(L"BUTTON", L"Chọn màu đường viền", WS_VISIBLE | WS_CHILD | BS_GROUPBOX, 400, 10, 170, 100, hWnd, NULL, hInst, NULL);

        btnHinh[0] = CreateWindowW(L"BUTTON", L"", WS_VISIBLE | WS_CHILD | BS_OWNERDRAW, 20, 40, 50, 50, hWnd, (HMENU)1, hInst, NULL);
        btnHinh[1] = CreateWindowW(L"BUTTON", L"", WS_VISIBLE | WS_CHILD | BS_OWNERDRAW, 80, 40, 50, 50, hWnd, (HMENU)2, hInst, NULL);


        for (int i = 0; i < 5; i++) {
            btnMNColor[i] = CreateWindowW(L"BUTTON", L"", WS_VISIBLE | WS_CHILD | BS_OWNERDRAW, 190 + (i * 30), 40, 25, 25, hWnd, (HMENU)(10 + i), hInst, NULL);
            btnDVColor[i] = CreateWindowW(L"BUTTON", L"", WS_VISIBLE | WS_CHILD | BS_OWNERDRAW, 410 + (i * 30), 40, 25, 25, hWnd, (HMENU)(20 + i), hInst, NULL);
        }
        break;
    case WM_DRAWITEM: {
        LPDRAWITEMSTRUCT pDIS = (LPDRAWITEMSTRUCT)lParam;
        HBRUSH hBrush = NULL;
        HPEN hPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
        SelectObject(pDIS->hDC, hPen);

        int left = pDIS->rcItem.left + 5;
        int top = pDIS->rcItem.top + 5;
        int right = pDIS->rcItem.right - 5;
        int bottom = pDIS->rcItem.bottom - 5;

        // Xử lý vẽ hình trên button
        if (pDIS->CtlID == 1) { // Button Oval
            Ellipse(pDIS->hDC, left, top, right, bottom);
        }
        else if (pDIS->CtlID == 2) { // Button Rectangle
            Rectangle(pDIS->hDC, left, top, right, bottom);
        }
        else if (pDIS->CtlID >= 10 && pDIS->CtlID < 15) { // Giữ nguyên phần chọn màu nền
            hBrush = CreateSolidBrush(colorOptions[pDIS->CtlID - 10]);
        }
        else if (pDIS->CtlID >= 20 && pDIS->CtlID < 25) { // Giữ nguyên phần chọn màu đường viền
            hBrush = CreateSolidBrush(colorOptions[pDIS->CtlID - 20]);
        }

        if (hBrush) {
            FillRect(pDIS->hDC, &pDIS->rcItem, hBrush);
            DeleteObject(hBrush);
        }

        DeleteObject(hPen);
        break;
    }
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        if (wmId >= 10 && wmId < 15) {
            bgColor = colorOptions[wmId - 10];
        }
        else if (wmId >= 20 && wmId < 25) {
            borderColor = colorOptions[wmId - 20];
        }
        else {
            switch (wmId)
            {
            case 1:
                selectedShape = 1;
                break;
            case 2:
                selectedShape = 2;
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    }
    case WM_LBUTTONDOWN:
    {
        ptStart.x = LOWORD(lParam);
        ptStart.y = HIWORD(lParam);
        break;
    }
    case WM_LBUTTONUP:
    {
        ptEnd.x = LOWORD(lParam);
        ptEnd.y = HIWORD(lParam);

        HDC hdc = GetDC(hWnd);
        HBRUSH hBrush = CreateSolidBrush(bgColor);
        HPEN hPen = CreatePen(PS_SOLID, 2, borderColor);
        SelectObject(hdc, hBrush);
        SelectObject(hdc, hPen);

        if (selectedShape == 1) {
            Ellipse(hdc, ptStart.x, ptStart.y, ptEnd.x, ptEnd.y);
        }
        else if (selectedShape == 2) {
            Rectangle(hdc, ptStart.x, ptStart.y, ptEnd.x, ptEnd.y);
        }

        DeleteObject(hBrush);
        DeleteObject(hPen);
        ReleaseDC(hWnd, hdc);
        break;
    }
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
