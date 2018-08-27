// Win32С��Ŀ.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Win32С��Ŀ.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
HWND g_hWnd;						

int  g_nCmdShow;
bool IsBeginPro = false;   //�Ƿ�ʼ����
bool flag = true;
// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK Regin(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
	g_nCmdShow = nCmdShow;
    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WIN32, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:

    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }
	  
    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WIN32));

    MSG msg;
	HDC hdc = GetDC(g_hWnd);
    // Main message loop:

	DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), NULL, Regin);
	while (IsBeginPro == FALSE);

	
	ZeroMemory(&msg, sizeof(msg));	//�ڴ�����		
	Welcome(hdc);
	
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
	}

	ReleaseDC(g_hWnd, hdc);
    return (int) msg.wParam;
}

INT_PTR CALLBACK Regin(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
		{
			char account[100] = {};
			char password[100] = {};
			GetDlgItemTextA(hDlg, 5001, account, 100);
			GetDlgItemTextA(hDlg, 5002, password, 100);
			if (strcmp(account, password) == 0 && (strlen(account) !=0 && strlen(password) != 0))
			{
				IsBeginPro = TRUE;
				EndDialog(hDlg, LOWORD(wParam));
				ShowWindow(g_hWnd, g_nCmdShow);
				UpdateWindow(g_hWnd);
			}
			else if(strlen(account) == 0)
			{
				MessageBoxA(hDlg, "�������˺�", "����", MB_OK); 
			}
			else if (strlen(password) == 0)
			{
				MessageBoxA(hDlg, "����������", "����", MB_OK);
			}
			else
			{
				MessageBoxA(hDlg, "�˺Ż��������", "����", MB_OK);
			}
		}
		break;
		case IDM_EXIT:
			IsBeginPro = TRUE;
			DestroyWindow(g_hWnd);
			EndDialog(hDlg, LOWORD(wParam));
			break;
		}
		if (LOWORD(wParam) == IDCANCEL)
		{
			IsBeginPro = TRUE;
			DestroyWindow(g_hWnd);
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}

	}
	return (INT_PTR)FALSE;
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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON2));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+5);
	wcex.lpszMenuName = NULL;
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ICON2));

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
   srand((size_t)time(NULL));
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_DLGFRAME | WS_SYSMENU,
      10, 10, 1200, 700, nullptr, nullptr, hInstance, nullptr);
   g_hWnd = hWnd;
   if (!hWnd)
   {
      return FALSE;
   }

  // ShowWindow(hWnd, nCmdShow);
   //UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
	case WM_LBUTTONDOWN:
		if (IsBeginPro == TRUE && flag == TRUE)
		{
			PlaySound(_T("С����.wav"), GetModuleHandle(NULL), SND_ASYNC | SND_FILENAME | SND_LOOP);
			Sleep(2000);
			SetTimer(hWnd, 10001, 1, NULL);
			SetTimer(hWnd, 10003, 40000, NULL);
			SetTimer(hWnd, 10002, rand() % 2200 + 1000, NULL);
			flag = FALSE;
		}
		break;
	case WM_TIMER:
		switch (wParam)
		{
		case 10001:
		{
			HDC hdc = GetDC(hWnd);
			CManage * MyProc = new CManage;
			MyProc->upProc(hdc);
			ReleaseDC(hWnd, hdc);
		}
		break;
		case 10002:
		{
			HDC hdc = GetDC(hWnd);
			CManage * MyProc = new CManage;
			MyProc->InitProc( hdc);
			MyProc->RenderProc(hdc ,hInst, rand()%4+1);
			ReleaseDC(hWnd, hdc);
			KillTimer(hWnd, 10002);
			SetTimer(hWnd, 10002, rand() % 2200 +800, NULL);
		}
			break;
		case 10003:
		{
			KillTimer(hWnd, 10002);

			MyPoint pos;
			pos.row = 25;
			pos.col = 275;
			

			HDC hdc = GetDC(hWnd);
			CManage * MyProc = new CManage;
			MyProc->InitProc(hdc);
			MyProc->Change(650, pos, 110);
			MyProc->RenderProc(hdc, hInst, rand()%4 + 1);
			ReleaseDC(hWnd, hdc);

			MyProc->upProc(hdc);
			MyProc->upProc(hdc);


			Sleep(2000);
			SetTimer(hWnd, 10002, rand() % 1500 + 500, NULL);
		}
			break;
		}

		break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
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
