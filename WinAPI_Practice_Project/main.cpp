// WinAPI_Practice_Project.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "pch.h"
#include "framework.h"
#include "WinAPI_Practice_Project.h"

#include "CCore.h"

#define MAX_LOADSTRING 100
#define WINNAME				(LPTSTR)(TEXT("WindowsAPI"))

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
HWND      g_hWnd;                               // 메인 윈도우 핸들

LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,         // 실행 된 프로세스의 시작 주소
	_In_opt_ HINSTANCE hPrevInstance,  // 이전에 실행 된 프로세스의 시작 주소
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	// 인스턴스 핸들을 전역 변수에 저장합니다.
	hInst = hInstance;

	// 윈도우 정보 등록
	WNDCLASS wndClass;

	wndClass.cbClsExtra = 0;                                            // 클래스 여분 메모리
	wndClass.cbWndExtra = 0;                                            // 윈도우 여분 메모리
	wndClass.hbrBackground = (HBRUSH)(GetStockObject(WHITE_BRUSH));     // 백그라운드
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);                     // 마우스 커서
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);                   // 아이콘
	wndClass.hInstance = hInstance;                                     // 윈도우를 소요할 프로그램의 식별자 정보
	wndClass.lpfnWndProc = (WNDPROC)WndProc;                            // 윈도우 프로시저
	wndClass.lpszClassName = WINNAME;									// 클래스 이름 (식별자 정보)
	wndClass.lpszMenuName = NULL;                                       // 메뉴 이름
	wndClass.style = CS_HREDRAW | CS_VREDRAW;                           // 윈도우 스타일 (다시 그리기 정보)

	RegisterClass(&wndClass);


	g_hWnd = CreateWindow(WINNAME, WINNAME, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

	ShowWindow(g_hWnd, nCmdShow);
	UpdateWindow(g_hWnd);

	// Core 초기화
	if (FAILED(CCore::GetInst()->init(g_hWnd, POINT{ 1280, 768 })))
	{
		MessageBox(nullptr, L"Core 객체 초기화 실패", L"ERROR", MB_OK);
		return FALSE;
	}

	// 단축키
	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINAPIPRACTICEPROJECT));

	MSG msg;

	//SetTimer(g_hWnd, 0, 0, NULL);

	// GetMessage
	// 메세지큐에서 메세지가 확인 될 때까지 대기
	// msg.message == WM_QUIT인 경우 false를 반환 -> 프로그램 종료

	// PeekMessage
	// 메세지 유무와 관계없이 반환
	// 메세지 큐에서 메세지를 확인한 경우 true, 메세지 큐에 메세지가 없는 경우 false를 반환한다.

	while (true)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (WM_QUIT == msg.message) break;

			if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			// Game 코드 수행
			// 디자인 패턴
			CCore::GetInst()->progress();
		}
	}

	//KillTimer(g_hWnd, 0);

	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_PAINT: // 무효화 영역(invalidate)이 발생한 경우
	{
		PAINTSTRUCT ps;

		// Device Context 만들어서 ID를 반환
		HDC hdc = BeginPaint(hWnd, &ps);

		// 그리기 종료
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_KEYDOWN:
		break;
	case WM_MOUSEMOVE:
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
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
