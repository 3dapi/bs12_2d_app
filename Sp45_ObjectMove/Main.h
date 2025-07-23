// Interface for the CMain class.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef _MAIN_H_
#define _MAIN_H_

class CMain : public CD3DApp
{
public:
	LPD3DXFONT			m_pD3DXFont;
	CLcInput*			m_pInput;

	DWORD				m_dTimeBgn;
	DWORD				m_dTimeCur;
	DWORD				m_dTimeCnt;
	FLOAT				m_dTimeAvg;

	CBackground*		m_pBack;
	CGameObj*			m_pMario;


public:
	CMain();

	virtual INT		Init();
	virtual void	Destroy();

	virtual INT		Restore();
	virtual void	Invalidate();

	virtual INT		FrameMove();
	virtual INT		Render();

	virtual LRESULT MsgProc(HWND, UINT, WPARAM, LPARAM);

public:
	FLOAT	GetAvgTime();
	FLOAT	GetAvgFrame();
};


extern CMain*	g_pApp;

#endif


