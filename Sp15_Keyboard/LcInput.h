// Interface for the CLcInput class.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef _LcInput_H_
#define _LcInput_H_

class CLcInput
{
public:
	enum EInputState
	{
		EINPUT_NONE	=	0,
		EINPUT_DOWN	=	1,
		EINPUT_UP	=	2,
		EINPUT_PRESS=	3,
	};

protected:
	BYTE	m_KeyCur[256];						// 현재의 상태
	BYTE	m_KeyOld[256];						// 이전의 상태
	BYTE	m_KeyMap[256];						// 맵

public:
	CLcInput();
	virtual ~CLcInput();

	INT		FrameMove();

	BOOL	KeyDown	(INT nKey);
	BOOL	KeyUp	(INT nKey);
	BOOL	KeyPress(INT nKey);
	INT		KeyState(INT nKey);
};

#endif