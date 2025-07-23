// Implementation of the CLcInput class.
//
////////////////////////////////////////////////////////////////////////////////


#include "_StdAfx.h"


CLcInput::CLcInput()
{
	memset(m_KeyOld, 0, sizeof(m_KeyOld));
	memset(m_KeyCur, 0, sizeof(m_KeyCur));
	memset(m_KeyMap, 0, sizeof(m_KeyMap));

	SetKeyboardState(m_KeyCur);
}

CLcInput::~CLcInput()
{

}


INT CLcInput::FrameMove()
{
	INT i=0;

	//1. currrent 값을 old 에 복사, 이전 상태를 저장한다.
	memcpy(m_KeyOld, m_KeyCur, sizeof(m_KeyOld));


	//2. Current 와 Map의 값을 0으로 초기화
	memset(m_KeyCur, 0, sizeof(m_KeyCur));
	memset(m_KeyMap, 0, sizeof(m_KeyMap));


	//3. current 이벤트 를 가져옴
	GetKeyboardState(m_KeyCur);


	for(i=0; i<256; ++i)
	{
		BYTE	vKey = m_KeyCur[i] & 0x80;		// 현재의 키보드 상태를 읽어온다.
		m_KeyCur[i] = (vKey)? 1: 0;				// 키보드 상태를 0과 1로 정한다.


		INT nOld = m_KeyOld[i];
		INT nCur = m_KeyCur[i];

		if		(0 == nOld && 1 ==nCur)	m_KeyMap[i] = EINPUT_DOWN;	// Down
		else if	(1 == nOld && 0 ==nCur)	m_KeyMap[i] = EINPUT_UP;	// Up
		else if	(1 == nOld && 1 ==nCur)	m_KeyMap[i] = EINPUT_PRESS;	// Press
		else							m_KeyMap[i] = EINPUT_NONE;	// NONE
	}


	return 0;
}


BOOL CLcInput::KeyDown(INT nKey)
{
	return m_KeyMap[nKey] == EINPUT_DOWN;
}

BOOL CLcInput::KeyUp(INT nKey)
{
	return m_KeyMap[nKey] == EINPUT_UP;
}

BOOL CLcInput::KeyPress(INT nKey)
{
	return m_KeyMap[nKey] == EINPUT_PRESS;
}


INT CLcInput::KeyState(INT nKey)
{
	return m_KeyMap[nKey];
}
