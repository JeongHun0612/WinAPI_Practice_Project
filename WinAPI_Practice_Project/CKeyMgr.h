#pragma once

// 1. 프레임 동기화
// 동일 프레임 내에서 같은 키에 대해, 동일한 이벤트를 가진다.

// 2. 키 입력 이벤트 처리
// tap, hold, away


enum class KEY_STATE
{
	TAP,		// 이전에 눌리지 않았고, 이번에 눌려진 상태		(막 누른 시점)
	HOLD,		// 이전에 눌려져 있었고, 이번에도 눌려진 상태		(꾹 누르는 시점)
	AWAY,		// 이전에 눌려져 있었고, 이번에 떼어진 상태		(눌렀다 뗀 시점)
	NONE		// 이전에 눌리지 않았고, 이전에도 눌리지 않은 상태
};

enum class KEY
{
	LEFT,
	RIGHT,
	UP,
	DOWN,

	Q, W, E, R, T, Y, U, I, O, P,
	A, S, D, F, G, Z, X, C, V, B,

	ALT,
	CTRL,
	LSHIFT,
	SPACE,
	ENTER,
	ESC,

	LAST
};

struct tKeyInfo
{
	KEY_STATE		eState;	// 키의 상태값
	bool			bPrevPush;	// 이전 프레임에서 눌렸는 지에 대한 여부
};

class CKeyMgr
{
	SINGLE(CKeyMgr);

private:
	vector<tKeyInfo> m_vecKey;

public:
	void init();
	void update();

public:
	KEY_STATE GetKeyState(KEY _eKey) { return m_vecKey[(int)_eKey].eState; } 
};

