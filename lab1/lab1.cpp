// lab8.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "lab1.h"

#define MAX_LOADSTRING 100
#define CLEAR 1
#define DRAW 2

bool isVisible = false;
// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

// Отправить объявления функций, включенных в этот модуль кода:
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

    // TODO: Разместите код здесь.

    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_LAB8, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB8));

    MSG msg;

    // Цикл основного сообщения:
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
//  ФУНКЦИЯ: MyRegisterClass()
//
//  ЦЕЛЬ: Регистрирует класс окна.
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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAB8));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_LAB8);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   ЦЕЛЬ: Сохраняет маркер экземпляра и создает главное окно
//
//   КОММЕНТАРИИ:
//
//        В этой функции маркер экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   HWND hButtonDraw = CreateWindow(L"BUTTON", NULL, 
       WS_VISIBLE | WS_CHILD | BS_OWNERDRAW | BS_PUSHBUTTON,
       15, 15, 150, 65, hWnd, (HMENU)DRAW, NULL, NULL);

   HWND hButtonClear = CreateWindow(L"BUTTON", NULL, 
       WS_VISIBLE | WS_CHILD | BS_OWNERDRAW | BS_PUSHBUTTON,
       180, 15, 150, 65, hWnd, (HMENU)CLEAR, NULL, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ЦЕЛЬ: Обрабатывает сообщения в главном окне.
//
//  WM_COMMAND  - обработать меню приложения
//  WM_PAINT    - Отрисовка главного окна
//  WM_DESTROY  - отправить сообщение о выходе и вернуться
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Разобрать выбор в меню:
            switch (wmId)
            {
            case DRAW:
                isVisible = true;
                InvalidateRect(hWnd, NULL, true);
                break;
            case CLEAR:
                isVisible = false;
                InvalidateRect(hWnd, NULL, true);
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
    case WM_DRAWITEM:
    {
        DRAWITEMSTRUCT* draw = (DRAWITEMSTRUCT*)lParam;
        HBRUSH brush;
        HPEN pen;
        switch (draw->CtlID) {
        case DRAW:
        {
            HDC hdc = draw->hDC;
            if (draw->itemAction == ODA_SELECT) {
                brush = CreateSolidBrush(RGB(140, 30, 95));
            }
            else {
                brush = CreateSolidBrush(RGB(246, 12, 145));
            }
            pen = CreatePen(BS_SOLID, 2, RGB(0, 0, 0));
            SelectObject(hdc, brush);
            SelectObject(hdc, pen);

            Rectangle(hdc, 0, 0, 150, 65);
            SetTextColor(hdc, RGB(0, 0, 255));   // blue text
            SetBkMode(hdc, TRANSPARENT);
            SetBkColor(hdc, RGB(246, 12, 145));
            TextOut(hdc, 45, 20, L"DRAW", 4);
           
        }
        break;
        case CLEAR:
        {
            HDC hdc = draw->hDC;

            if (draw->itemAction == ODA_SELECT) {
                brush = CreateSolidBrush(RGB(230, 105, 10));
            }
            else {
                brush = CreateSolidBrush(RGB(255, 180, 0));
            }
            pen = CreatePen(BS_SOLID, 2, RGB(0, 0, 0));

            SelectObject(hdc, brush);
            SelectObject(hdc, pen);

            Rectangle(hdc, 0, 0, 150, 65);
            SetTextColor(hdc, RGB(1, 118, 12)); 
            SetBkMode(hdc, TRANSPARENT);
            SetBkColor(hdc, RGB(255, 180, 0));
            Rectangle(hdc, 0, 0, 150, 65);
            TextOut(hdc, 45, 20, L"CLEAR", 5);
        }
        break;
        default:
            break;
        }
    }
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            if (isVisible)
            {
                HBRUSH brush;
                HPEN pen;

                brush = CreateSolidBrush(RGB(70,65,100));
                SelectObject(hdc, brush);
                Rectangle(hdc, 0, 0, 2000, 1000);

                brush = CreateSolidBrush(RGB(28, 80, 24));
                SelectObject(hdc, brush);
                pen = CreatePen(BS_SOLID, 2, RGB(12, 64, 8));
                SelectObject(hdc, pen);
                Rectangle(hdc, 0, 400, 2000, 1000);

                brush = CreateSolidBrush(RGB(150, 40, 40));
                SelectObject(hdc, brush);
                pen = CreatePen(BS_SOLID, 3, RGB(30, 14, 14));
                SelectObject(hdc, pen);
                Rectangle(hdc, 200, 200, 500, 350);
                DeleteObject(brush);
                DeleteObject(pen);

                POINT poly[3] = { {200,200 },{ 250 , 130 },{300, 200} };
                brush = CreateSolidBrush(RGB(130, 30, 155));
                SelectObject(hdc, brush);
                Polygon(hdc, poly, 3);

                POINT poly2[4] = { {300,200 },{250,130 },{450,130}, {500,200 } };
                brush = CreateSolidBrush(RGB(130, 30, 155));
                SelectObject(hdc, brush);
                Polygon(hdc, poly2, 4);

                brush = CreateSolidBrush(RGB(30, 14, 14));
                SelectObject(hdc, brush);
                MoveToEx(hdc, 300, 200,0);
                LineTo(hdc, 300, 350);

                pen = CreatePen(BS_SOLID, 3, RGB(242, 13, 112));
                SelectObject(hdc, pen);
                MoveToEx(hdc, 250, 350, 0);
                LineTo(hdc, 250, 450);

                MoveToEx(hdc, 420, 350, 0);
                LineTo(hdc, 420, 450);

                MoveToEx(hdc, 250, 450, 0);
                LineTo(hdc, 230, 470);

                MoveToEx(hdc, 250, 450, 0);
                LineTo(hdc, 240, 480);

                MoveToEx(hdc, 250, 450, 0);
                LineTo(hdc, 270, 470);

                MoveToEx(hdc, 420, 450, 0);
                LineTo(hdc, 390, 470);

                MoveToEx(hdc, 420, 450, 0);
                LineTo(hdc, 410, 480);

                MoveToEx(hdc, 420, 450, 0);
                LineTo(hdc, 440, 470);

                brush = CreateSolidBrush(RGB(166, 242, 13));
                SelectObject(hdc, brush);
                pen = CreatePen(BS_SOLID, 3, RGB(30, 14, 14));
                SelectObject(hdc, pen);
                Rectangle(hdc, 220, 250, 260, 350);

                brush = CreateSolidBrush(RGB(13, 242, 242));
                SelectObject(hdc, brush);
                pen = CreatePen(BS_SOLID, 3, RGB(180, 14, 241));
                SelectObject(hdc, pen);
                Ellipse(hdc, 320, 220, 370, 270);
                Ellipse(hdc, 420, 220, 470, 270);

                Arc(hdc, 350, 280, 450, 380, 450, 350,350,350);

                brush = CreateSolidBrush(RGB(242, 44, 13));
                SelectObject(hdc, brush);
                Ellipse(hdc, 235, 290, 245, 310);

                brush = CreateSolidBrush(RGB(125, 151, 40));
                SelectObject(hdc, brush);
                pen = CreatePen(BS_SOLID, 4, RGB(74, 92, 14));
                SelectObject(hdc, pen);
                Ellipse(hdc, 620, 350, 910, 450);

                brush = CreateSolidBrush(RGB(243, 221, 19));
                SelectObject(hdc, brush);
                Ellipse(hdc, 680, 420, 730, 470);

                Ellipse(hdc, 800, 420, 850, 470);

                Arc(hdc, 680,300,855,450,750,300,700,360);

            }
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

// Обработчик сообщений для окна "О программе".
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
