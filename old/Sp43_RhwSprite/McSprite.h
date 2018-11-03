// Interface for the CMcSprite class.
//
////////////////////////////////////////////////////////////////////////////////


#ifndef _McSprite_H_
#define _McSprite_H_


class CMcSprite
{
public:
	struct VtxRHWUV1
	{
		D3DXVECTOR4 p;
		FLOAT		u0,v0;
		
		VtxRHWUV1(){}
		VtxRHWUV1(FLOAT X, FLOAT Y, FLOAT U0, FLOAT V0)
		{
			p.x = X;
			p.y = Y;
			p.z = 0;
			p.w = 1;
			u0	= U0;
			v0	= V0;
		}
		
		enum {	FVF =(D3DFVF_XYZRHW|D3DFVF_TEX1)	};
	};


protected:
	LPDIRECT3DDEVICE9		m_pDev;

	CMcSprite::VtxRHWUV1	m_pVtx[4];
	LPDIRECT3DTEXTURE9		m_pTx[8];
	
	
public:
	CMcSprite();
	virtual ~CMcSprite();

	INT		Create(LPDIRECT3DDEVICE9 pDev);
	void	Destroy();
	void	Render();

	void	SetTexture(INT nStage, LPDIRECT3DTEXTURE9 pTx);
};


#endif


