// GameObj.h: interface for the CGameObj class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GAMEOBJ_H__8827F176_24AB_4078_B003_47118684883F__INCLUDED_)
#define AFX_GAMEOBJ_H__8827F176_24AB_4078_B003_47118684883F__INCLUDED_


class CGameObj  
{
protected:
	LPDIRECT3DDEVICE9	m_pDevice;
	LPD3DXSPRITE		m_pSprite;
	
	LPDIRECT3DTEXTURE9	m_pTex;
	D3DXIMAGE_INFO		m_pImg;

protected:
	D3DXVECTOR3			m_vcPos;
	FLOAT				m_fSpeed;

	D3DXVECTOR3			m_vcDir;
public:
	INT					m_nDir;

protected:
	DWORD	m_dBgn ;
	DWORD	m_dCur ;
	DWORD	m_dIntr;
	int		m_nBgnX ;
	int		m_nBgnY ;

	int		m_nCur	 ;
	int		m_nTot	 ;
	

public:
	CGameObj();
	virtual ~CGameObj();

	INT		Create(LPDIRECT3DDEVICE9 pDevice, LPD3DXSPRITE pSprite);
	void	Destroy();

	INT		FrameMove();
	void	Render();

};

#endif // !defined(AFX_GAMEOBJ_H__8827F176_24AB_4078_B003_47118684883F__INCLUDED_)

