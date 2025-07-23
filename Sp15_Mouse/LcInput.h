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
	BYTE			m_BtnCur[8];		// 현재의 상태
	BYTE			m_BtnOld[8];		// 이전의 상태
	BYTE			m_BtnMap[8];		// 맵

	D3DXVECTOR3		m_vcCur;			// Z is Wheel Mouse
	D3DXVECTOR3		m_vcOld;
	D3DXVECTOR3		m_vcEps;

	HWND			m_hWnd;

public:
	CLcInput();
	~CLcInput();

	INT			Create(HWND	hWnd);
	INT			FrameMove();
	LRESULT		MsgProc(HWND,UINT, WPARAM, LPARAM);

public:
	BOOL		BtnDown	 (INT nBtn);
	BOOL		BtnUp	 (INT nBtn);
	BOOL		BtnPress (INT nBtn);
	INT			BtnState (INT nBtn);

	D3DXVECTOR3 GetMousePos();
	D3DXVECTOR3 GetMouseEps();
};

#endif
