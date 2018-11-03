// Implementation of the CMcSprite class.
//
////////////////////////////////////////////////////////////////////////////////


#include "_StdAfx.h"


CMcSprite::CMcSprite()
{
	m_pDev	= NULL;

	for(int i=0; i<8; ++i)
		m_pTx[i]	= NULL;
}



CMcSprite::~CMcSprite()
{
	Destroy();
}



INT CMcSprite::Create(LPDIRECT3DDEVICE9 pDev)
{
	HRESULT hr=-1;

	m_pDev = pDev;

	m_pVtx[0] = CMcSprite::VtxRHWUV1(  0,   0,  0,  0);
	m_pVtx[1] = CMcSprite::VtxRHWUV1(800,   0,  1,  0);
	m_pVtx[2] = CMcSprite::VtxRHWUV1(  0, 600,  0,  1);
	m_pVtx[3] = CMcSprite::VtxRHWUV1(800, 600,  1,  1);

	return 0;
}



void CMcSprite::Destroy()
{
}



void CMcSprite::Render()
{
	INT		i = 0;

	if(!m_pTx[0])
		return;

	for(i=0; i<8; ++i)
	{
		m_pDev->SetTexture(i, m_pTx[i]);
		m_pDev->SetTextureStageState( i, D3DTSS_TEXCOORDINDEX, 0);
	}


	m_pDev->SetFVF( CMcSprite::VtxRHWUV1::FVF );


	m_pDev->SetSamplerState( 0, D3DSAMP_MINFILTER, D3DTEXF_NONE);
	m_pDev->SetSamplerState( 0, D3DSAMP_MAGFILTER, D3DTEXF_NONE);


	// Set up the textures
	m_pDev->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
	m_pDev->SetTextureStageState( 0, D3DTSS_COLOROP,   D3DTOP_SELECTARG1);

	m_pDev->SetTextureStageState( 0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE );
	m_pDev->SetTextureStageState( 0, D3DTSS_ALPHAOP,   D3DTOP_SELECTARG1);


	if(NULL == m_pTx[1])
	{
		m_pDev->DrawPrimitiveUP( D3DPT_TRIANGLESTRIP, 2, m_pVtx, sizeof(CMcSprite::VtxRHWUV1) );
		m_pDev->SetSamplerState( 0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
		m_pDev->SetSamplerState( 0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);

		return;
	}


	m_pDev->SetSamplerState( 1, D3DSAMP_MINFILTER, D3DTEXF_NONE);
	m_pDev->SetSamplerState( 1, D3DSAMP_MAGFILTER, D3DTEXF_NONE);

	m_pDev->SetTextureStageState( 1, D3DTSS_COLORARG1, D3DTA_CURRENT );
	m_pDev->SetTextureStageState( 1, D3DTSS_COLOROP,   D3DTOP_SELECTARG1);

	m_pDev->SetTextureStageState( 1, D3DTSS_ALPHAARG1, D3DTA_CURRENT );
	m_pDev->SetTextureStageState( 1, D3DTSS_ALPHAARG2, D3DTA_TEXTURE );
	m_pDev->SetTextureStageState( 1, D3DTSS_ALPHAOP,   D3DTOP_SELECTARG2);


	m_pDev->SetRenderState( D3DRS_DITHERENABLE,   FALSE );
	m_pDev->SetRenderState( D3DRS_SPECULARENABLE, FALSE );
	m_pDev->SetRenderState( D3DRS_ZENABLE,        TRUE );

	m_pDev->SetRenderState( D3DRS_ALPHABLENDENABLE,   TRUE);
	m_pDev->SetRenderState( D3DRS_SRCBLEND,  D3DBLEND_SRCALPHA );
	m_pDev->SetRenderState( D3DRS_DESTBLEND,  D3DBLEND_INVSRCALPHA );

	m_pDev->DrawPrimitiveUP( D3DPT_TRIANGLESTRIP, 2, m_pVtx, sizeof(CMcSprite::VtxRHWUV1) );









	m_pDev->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	m_pDev->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
	m_pDev->SetTextureStageState( 0, D3DTSS_COLOROP,   D3DTOP_MODULATE);

	m_pDev->SetTextureStageState( 0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	m_pDev->SetTextureStageState( 0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
	m_pDev->SetTextureStageState( 0, D3DTSS_ALPHAOP,   D3DTOP_MODULATE);

	for(i=0; i<8; ++i)
	{
		m_pDev->SetTextureStageState( i, D3DTSS_COLORARG1, D3DTA_CURRENT);
		m_pDev->SetTextureStageState( i, D3DTSS_COLORARG2, D3DTA_TEXTURE);
		m_pDev->SetTextureStageState( i, D3DTSS_COLOROP,   D3DTOP_MODULATE);

		m_pDev->SetTextureStageState( i, D3DTSS_ALPHAARG1, D3DTA_CURRENT);
		m_pDev->SetTextureStageState( i, D3DTSS_ALPHAARG2, D3DTA_TEXTURE);
		m_pDev->SetTextureStageState( i, D3DTSS_ALPHAOP,   D3DTOP_MODULATE);

		m_pDev->SetSamplerState( i, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
		m_pDev->SetSamplerState( i, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	}


	m_pDev->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	m_pDev->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
	m_pDev->SetTextureStageState( 0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	m_pDev->SetTextureStageState( 0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);

	m_pDev->SetRenderState( D3DRS_ALPHABLENDENABLE, FALSE);
}



void CMcSprite::SetTexture(INT nStage, LPDIRECT3DTEXTURE9 pTx)
{
	m_pTx[nStage] = pTx;
}

