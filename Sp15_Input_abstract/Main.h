// Interface for the CMain class.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef _MAIN_H_
#define _MAIN_H_

class CMain : public CD3DApp
{
public:
	LPD3DXFONT			m_pD3DXFont;
	ILcInput*			m_pInput;


public:
	CMain();

	virtual INT		Init();
	virtual void	Destroy();

	virtual INT		Restore();
	virtual void	Invalidate();

	virtual INT		FrameMove();
	virtual INT		Render();

	virtual LRESULT MsgProc(HWND, UINT, WPARAM, LPARAM);
};


extern CMain*	g_pApp;

#endif