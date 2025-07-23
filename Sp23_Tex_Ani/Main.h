// Interface for the CMain class.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef _MAIN_H_
#define _MAIN_H_

class CMain : public CD3DApp
{
public:
	LPD3DXFONT		m_pD3DXFont;

	CLcTexture*		m_pTxBck;			// 배경 텍스처
	RECT			m_ImgRcB;			// RECT 애니 이미지

	CLcTexture*		m_pTxAni;			// 애니 텍스처

	DWORD			m_dTimeBgn;			// 시작 타임
	DWORD			m_dTimeEnd;			// 끝 타임

	RECT			m_ImgRc1;			// RECT 애니 이미지
	RECT			m_ImgRc2;			// RECT 애니 이미지


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
