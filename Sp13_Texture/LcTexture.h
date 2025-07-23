// Interface for the CLcTexture class.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef _LCTEXTURE_H_
#define _LCTEXTURE_H_


class CLcTexture
{
protected:
	LPDIRECT3DDEVICE9	m_pDev;
	
	D3DXIMAGE_INFO		m_Img;
	LPDIRECT3DTEXTURE9	m_pTx;

public:
	CLcTexture();
	virtual ~CLcTexture();

	virtual INT		Create(LPDIRECT3DDEVICE9 pDev, char* sFile);
	virtual void	Destroy();

public:
	INT		GetImageWidth();
	INT		GetImageHeight();
	void	GetImageRect(RECT* pRc);

	LPDIRECT3DTEXTURE9	GetTexture();
};

#endif