// DeLuyenWinAPI.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "DeLuyenWinAPI.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
HMENU hMenuPopUp;

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
    LoadStringW(hInstance, IDC_DELUYENWINAPI, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_DELUYENWINAPI));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DELUYENWINAPI));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDR_MENU1);
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
   hMenuPopUp = LoadMenu(hInst, MAKEINTRESOURCE(IDR_MENU1));
   HWND hWnd = CreateWindowW(szWindowClass, TEXT("Nguyễn Hùng Cường - 222611075"), WS_OVERLAPPEDWINDOW,
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
    static POINT pointR, rhom[4];
    static int xLeft, yTop, xRight, yBottom, left, right, top, bottom;
    static HPEN hPen = CreatePen(PS_SOLID, 3, RGB(0, 0, 0));
    static HBRUSH hBrush = (HBRUSH)GetStockObject(WHITE_BRUSH);
    static HDC hdc;
    switch (message)
    {
    case WM_RBUTTONDOWN:
        pointR.x = LOWORD(lParam);
        pointR.y = HIWORD(lParam);
        ClientToScreen(hWnd, &pointR);
        if (hMenuPopUp)
        {
            // Get the handle to the "Màu nền" (Background Color) popup menu
            HMENU hSubMenuBackground = GetSubMenu(hMenuPopUp, 0); // Index 0 for the first POPUP

            // Get the handle to the "Màu viền" (Outline Color) popup menu
            HMENU hSubMenuOutline = GetSubMenu(hMenuPopUp, 1);   // Index 1 for the second POPUP

            // Now, you need to decide which of these popups to show on right-click.
            // Based on your description, it seems like you want a single popup
            // containing "Màu nền" and "Màu viền" as the top-level items.

            // To achieve that, you should create a *new* popup menu and
            // append "Màu nền" and "Màu viền" (as submenus) to it.

            HMENU hContextMenu = CreatePopupMenu();
            if (hContextMenu)
            {
                AppendMenu(hContextMenu, MF_STRING | MF_POPUP, (UINT_PTR)hSubMenuBackground, L"Màu nền");
                AppendMenu(hContextMenu, MF_STRING | MF_POPUP, (UINT_PTR)hSubMenuOutline, L"Màu viền");

                TrackPopupMenu(hContextMenu, TPM_RIGHTBUTTON, pointR.x, pointR.y, 0, hWnd, NULL);

                // Destroy the temporary context menu
                DestroyMenu(hContextMenu);
            }

            // Destroy the loaded menu resource when you are done with it
            DestroyMenu(hMenuPopUp);
        }
        break;
    case WM_LBUTTONDOWN:
        xLeft = LOWORD(lParam);
        yTop = HIWORD(lParam);
        break;
    case WM_LBUTTONUP:
        xRight = LOWORD(lParam);
        yBottom = HIWORD(lParam);

        hdc = GetDC(hWnd);
        SelectObject(hdc, hPen);
        SelectObject(hdc, hBrush);

        //TODO: Draw rhombus
        left = min(xLeft, xRight);
        right = max(xLeft, xRight);
        top = min(yTop, yBottom);
        bottom = max(yTop, yBottom);

        // Calculate the vertices of the rhombus
        rhom[0].x = (left + right) / 2; // Top point
        rhom[0].y = top;

        rhom[1].x = right;             // Right point
        rhom[1].y = (top + bottom) / 2;

        rhom[2].x = (left + right) / 2; // Bottom point
        rhom[2].y = bottom;

        rhom[3].x = left;              // Left point
        rhom[3].y = (top + bottom) / 2;

        // Draw the rhombus
        Polygon(hdc, rhom, 4);

        ReleaseDC(hWnd, hdc);
        break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case ID_MAUNENVANG:
                hBrush = CreateSolidBrush(RGB(0, 255, 255));
                break;
            case ID_MAUNENXANH:
                hBrush = CreateSolidBrush(RGB(0, 0, 255));
                break;
            case ID_MAUVIENDO:
                hPen = CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
                break;
            case ID_MAUVIENTIM:
                hPen = CreatePen(PS_SOLID, 3, RGB(255, 0, 255));
                break;
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
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
