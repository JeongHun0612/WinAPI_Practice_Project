#pragma once

// �̱��� ����
// ��ü�� ������ 1���� ����
// ��𼭵� ���� ���� ����
//class CCore
//{
//private:
//	static CCore* g_pInst;
//
//public:
//	static CCore* GetInstance()
//	{
//		// ���� ȣ�� �� ���
//		if (nullptr == g_pInst)
//		{
//			g_pInst = new CCore;
//		}
//
//		return g_pInst;
//	}
//
//	static void Release()
//	{
//		if (nullptr != g_pInst)
//		{
//			delete g_pInst;
//			g_pInst = nullptr;
//		}
//	}
//
//private:
//
//	CCore();
//	~CCore();
//};

class CCore
{
SINGLE(CCore);

private:
	HWND		m_hWnd;			 // ���� ������ �ڵ�
	POINT		m_ptResolution;	 // ���� ������ �ػ�
	HDC			m_hDC;			 // ���� ������ DC

	HBITMAP		m_hBit;
	HDC			m_memDC;


public:
	int init(HWND _hWnd, POINT _ptResolution);
	void progress();

private:
	void update();
	void render();

public:
	HWND GetMainHwnd() { return m_hWnd; }

};
