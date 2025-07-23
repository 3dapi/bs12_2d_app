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

	CLcTexture*		m_pTex1;
	CLcTexture*		m_pTex2;

	D3DXVECTOR2		m_ObjPos1;			// Object 1 Position
	D3DXVECTOR2		m_ObjPos2;			// Object 2 Position

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