// Interface for the CMain class.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef _MAIN_H_
#define _MAIN_H_


class CMain : public CD3DApp
{
public:
	LPD3DXFONT			m_pD3DXFont;

	D3DXIMAGE_INFO		m_ImgBck;
	LPDIRECT3DTEXTURE9	m_pTxBck;			// 배경 텍스처
	RECT				m_ImgRcB;			// RECT 애니 이미지

	int				m_iCnt		;
	CMcCoin*		m_pCoin		;



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