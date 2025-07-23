// Interface for the CMain class.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef _MAIN_H_
#define _MAIN_H_

class CMain : public CD3DApp
{
public:
	ID3DXFont*	m_pDXFont1;

	LPD3DXFONT	m_pDXFont2; 	//LPD3DXFONT = ID3DXFont*

public:
	CMain();

	virtual INT		Init();
	virtual void	Destroy();

	virtual INT		FrameMove();
	virtual INT		Render();

	virtual LRESULT MsgProc(HWND, UINT, WPARAM, LPARAM);
};


extern CMain*	g_pApp;

#endif