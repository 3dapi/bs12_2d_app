// Implementation of the CLcInput class.
//
////////////////////////////////////////////////////////////////////////////////

// 휠마우스를 쓰려면 이 구문은 반드시 필요.
#define _WIN32_WINNT 0x0400

#include "_StdAfx.h"


CLcInput::CLcInput()
{
	m_hWnd	= NULL;
}

CLcInput::~CLcInput()
{

}


INT CLcInput::Create(HWND hWnd)
{
	m_hWnd	= hWnd;

	memset(m_BtnCur, 0, sizeof(m_BtnCur));
	memset(m_BtnOld, 0, sizeof(m_BtnOld));
	memset(m_BtnMap, 0, sizeof(m_BtnMap));

	memset(&m_vcCur, 0, sizeof(m_vcCur));
	memset(&m_vcOld, 0, sizeof(m_vcOld));

	return 0;
}

INT CLcInput::FrameMove()
{
	INT nBtn=0;

	//1. currrent 값을 old 에 복사, 이전 상태를 저장한다.
	memcpy(m_BtnOld, m_BtnCur, sizeof(m_BtnOld));


	//2. Current 와 Map의 값을 0으로 초기화
	memset(m_BtnCur, 0, sizeof(m_BtnCur));
	memset(m_BtnMap, 0, sizeof(m_BtnMap));


	//3. current 이벤트 를 가져옴
	m_BtnCur[0] = (GetAsyncKeyState(VK_LBUTTON) & 0x8000)? 1: 0;	// Left Button
	m_BtnCur[1] = (GetAsyncKeyState(VK_RBUTTON) & 0x8000)? 1: 0;	// Right Button
	m_BtnCur[2] = (GetAsyncKeyState(VK_MBUTTON) & 0x8000)? 1: 0;	// Middle Button


	for(nBtn=0; nBtn<8; ++nBtn)
	{
		INT nOld = m_BtnOld[nBtn];
		INT nCur = m_BtnCur[nBtn];

		if		(0 == nOld && 1 ==nCur)	m_BtnMap[nBtn] = EINPUT_DOWN;	// Down
		else if	(1 == nOld && 0 ==nCur)	m_BtnMap[nBtn] = EINPUT_UP;		// Up
		else if	(1 == nOld && 1 ==nCur)	m_BtnMap[nBtn] = EINPUT_PRESS;	// Press
	}


	// 4. Update Mouse Position
	POINT pt;
	::GetCursorPos(&pt);
	::ScreenToClient(m_hWnd, &pt);

	m_vcOld.x = m_vcCur.x;
	m_vcOld.y = m_vcCur.y;

	m_vcCur.x = FLOAT(pt.x);
	m_vcCur.y = FLOAT(pt.y);

	m_vcEps = m_vcCur - m_vcOld;
	m_vcOld.z = m_vcCur.z;

	return 0;
}


BOOL CLcInput::BtnDown(INT nBtn)
{
	return m_BtnMap[nBtn] == EINPUT_DOWN;
}

BOOL CLcInput::BtnUp(INT nBtn)
{
	return m_BtnMap[nBtn] == EINPUT_UP;
}

BOOL CLcInput::BtnPress(INT nBtn)
{
	return m_BtnMap[nBtn] == EINPUT_PRESS;
}

INT	 CLcInput::BtnState(INT nBtn)
{
	return m_BtnMap[nBtn];
}



D3DXVECTOR3	CLcInput::GetMousePos()
{
	return m_vcCur;
}

// Wheel Mouse 처리
LRESULT CLcInput::MsgProc(HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	switch( msg )
	{
		case WM_MOUSEWHEEL:
		{
			INT c= HIWORD(wParam);
			INT d= LOWORD(wParam);

			c = short( c );
			m_vcCur.z += FLOAT(c);
			break;
		}
	}

	return 0;
}