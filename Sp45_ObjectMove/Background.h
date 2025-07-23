// Background.h: interface for the CBackground class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BACKGROUND_H__5F35A22D_7DBB_41CB_9C96_8F7879E53DBF__INCLUDED_)
#define AFX_BACKGROUND_H__5F35A22D_7DBB_41CB_9C96_8F7879E53DBF__INCLUDED_

class CBackground  
{
protected:
	LPDIRECT3DDEVICE9	m_pDevice;
	LPD3DXSPRITE		m_pSprite;
	
	LPDIRECT3DTEXTURE9	m_pTex[4];
	D3DXIMAGE_INFO		m_pImg[4];
	
	D3DXVECTOR3			m_Cloud1Pos;
	FLOAT				m_Cloud1Speed;
	D3DXVECTOR3			m_Cloud1Dir;

	D3DXVECTOR3			m_Cloud2Pos;
	FLOAT				m_Cloud2Speed;
	D3DXVECTOR3			m_Cloud2Dir;

public:
	CBackground();
	virtual ~CBackground();

	INT		Create(LPDIRECT3DDEVICE9 pDevice, LPD3DXSPRITE pSprite);
	void	Destroy();

	INT		FrameMove();
	void	Render();

};

#endif // !defined(AFX_BACKGROUND_H__5F35A22D_7DBB_41CB_9C96_8F7879E53DBF__INCLUDED_)
