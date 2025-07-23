// Interface for the CMain class.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef _MAIN_H_
#define _MAIN_H_


class CMain : public CD3DApp
{
public:
	CLcSprite*		m_pLcSprite;
	CLcInput*		m_pInput;

	D3DXVECTOR2		m_pLine1[3];		// Line 1
	D3DXVECTOR2		m_pLine2[3];		// Line 2

	ID3DXLine*		m_pLine;


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