#include "pch.h"
#include "CCore.h"

#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CSceneMgr.h"

#include "CObject.h"

CObject g_obj;

CCore::CCore()
	: m_hWnd(0)
	, m_ptResolution{}
	, m_hDC(0)
	, m_hBit(0)
	, m_memDC(0)
{
}

CCore::~CCore()
{
	ReleaseDC(m_hWnd, m_hDC);

	DeleteDC(m_memDC);
	DeleteObject(m_hBit);
}

int CCore::init(HWND _hWnd, POINT _ptResolution)
{
	m_hWnd = _hWnd;
	m_ptResolution = _ptResolution;

	// 해상도에 맞게 윈도우 크기 조정
	RECT rt = { 0, 0, m_ptResolution.x, m_ptResolution.y };
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, true);
	SetWindowPos(m_hWnd, nullptr, 100, 100, rt.right - rt.left, rt.bottom - rt.top, 0);

	m_hDC = GetDC(m_hWnd);

	// 더블 버퍼링 용도의 비트맵과 DC를 만든다.
	m_hBit = CreateCompatibleBitmap(m_hDC, m_ptResolution.x, m_ptResolution.y);
	m_memDC = CreateCompatibleDC(m_hDC);

	// WinAPI에서 처음 재공해주는 default Bitmap은 1px 짜리 비트맵 / 따라서 바로 삭제
	HBITMAP hOldBit = (HBITMAP)SelectObject(m_memDC, m_hBit);
	DeleteObject(hOldBit);

	// Manager 초기화
	CTimeMgr::GetInst()->init();
	CKeyMgr::GetInst()->init();
	CSceneMgr::GetInst()->init();

	g_obj.SetPos(Vec2(m_ptResolution.x / 2, m_ptResolution.y / 2));
	g_obj.setScale(Vec2(100, 100));

	return S_OK;
}

void CCore::progress()
{
	// Manager Update
	CTimeMgr::GetInst()->update();
	CKeyMgr::GetInst()->update();

	update();

	render();
}

void CCore::update()
{
	Vec2 vPos = g_obj.GetPos();

	if (CKeyMgr::GetInst()->GetKeyState(KEY::LEFT) == KEY_STATE::AWAY)
	{
		vPos.x -= 100.f;
	}
	if (CKeyMgr::GetInst()->GetKeyState(KEY::RIGHT) == KEY_STATE::TAP)
	{
		vPos.x += 100.f;
	}

	g_obj.SetPos(vPos);
}

void CCore::render()
{
	// 화면 Clear
	Rectangle(m_memDC, -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1);

	// 그리기
	Vec2 vPos = g_obj.GetPos();
	Vec2 vScale = g_obj.GetScale();

	Rectangle(m_memDC, int(vPos.x - vScale.x / 2.f)
					,int(vPos.y - vScale.y / 2.f)
					,int(vPos.x + vScale.x / 2.f)
					,int(vPos.y + vScale.y / 2.f));
	 
	BitBlt(m_hDC, 0, 0, m_ptResolution.x, m_ptResolution.y, // 복살 될 위치
		m_memDC, 0, 0, SRCCOPY);							// 복사할 영역
}
