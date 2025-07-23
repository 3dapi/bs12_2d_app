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

	
	CLcTexture*		m_pTexBack;
	
	CLcTexture*			m_pTexAni;
	LPDIRECT3DTEXTURE9	m_pTexAniS;			// 그림자 텍스처

	DWORD			m_dTimeBgn;			// 시작 타임
	DWORD			m_dTimeEnd;			// 끝 타임
	RECT			m_ImgRc1;			// RECT 애니 이미지

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