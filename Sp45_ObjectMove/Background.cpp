// Background.cpp: implementation of the CBackground class.
//
//////////////////////////////////////////////////////////////////////

#include "_StdAfx.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBackground::CBackground()
{

}

CBackground::~CBackground()
{
	Destroy();
}

INT CBackground::Create(LPDIRECT3DDEVICE9 pDevice, LPD3DXSPRITE pSprite)
{
	m_pDevice = pDevice;
	m_pSprite = pSprite;

	char* TexName[] =						// mario Texture Name
	{
		"Texture/mario_cloud.png"	,
		"Texture/mario_bush2.png"	,
		"Texture/mario_bush1.png"	,
		"Texture/mario_tile1.png"	,
	};

	for(int i=0; i<4; ++i)
	{
		if(FAILED(D3DXCreateTextureFromFileEx(
			m_pDevice
			, TexName[i]
			, D3DX_DEFAULT
			, D3DX_DEFAULT
			, 1
			, 0
			, D3DFMT_UNKNOWN
			, D3DPOOL_MANAGED
			, D3DX_FILTER_NONE
			, D3DX_FILTER_NONE
			, 0x00FFFFFF
			, &m_pImg[i]
			, NULL
			, &m_pTex[i]
			)) )
		{
			return -1;
		}
	}


	m_Cloud1Pos		= D3DXVECTOR3(600, 50, 0);
	m_Cloud1Speed	= .1f;
	m_Cloud1Dir		= D3DXVECTOR3(-1, 0, 0);
	
	m_Cloud2Pos		= D3DXVECTOR3(300, 50, 0);
	m_Cloud2Speed	= .13f;
	m_Cloud2Dir		= D3DXVECTOR3(-1, 0, 0);

	return 0;
}


void CBackground::Destroy()
{
	for(int i=0; i<4; ++i)
	{
		SAFE_RELEASE(	m_pTex[i]	);
	}
}

INT CBackground::FrameMove()
{
	FLOAT	fTime = g_pApp->GetAvgTime();

	m_Cloud1Pos += m_Cloud1Speed * m_Cloud1Dir * fTime;

	if(m_Cloud1Pos.x<-200)
			m_Cloud1Pos.x = 800;


	m_Cloud2Pos += m_Cloud2Speed * m_Cloud2Dir * fTime;

	if(m_Cloud2Pos.x<-200)
			m_Cloud2Pos.x = 800;


	return 0;
}

void CBackground::Render()
{
	// 구름을 그린다.
	RECT	rcCloud1 = {0,0, 136, 128};
	RECT	rcCloud2 = {144,0, 336, 128};

	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);

		m_pSprite->Draw(	m_pTex[0]
							, &rcCloud1
							, NULL
							, &m_Cloud1Pos
							, D3DXCOLOR(1,1,1,1)	);

		m_pSprite->Draw(	m_pTex[0]
							, &rcCloud2
							, NULL
							, &m_Cloud2Pos
							, D3DXCOLOR(1,1,1,1)	);
		

		// 나무2를 그린다.
		RECT	rcBush1 = {0,0, m_pImg[1].Width, m_pImg[1].Height};

		m_pSprite->Draw(	m_pTex[1]
							, &rcBush1
							, NULL
							, &D3DXVECTOR3(100, 286, 0)
							, D3DXCOLOR(1,1,1,1)	);

		m_pSprite->Draw(	m_pTex[1]
							, &rcBush1
							, NULL
							, &D3DXVECTOR3(700, 286, 0)
							, D3DXCOLOR(1,1,1,1)	);

		// 나무1을 그린다.
		RECT	rcBush2 = {0,0, m_pImg[2].Width, m_pImg[2].Height};

		m_pSprite->Draw(	m_pTex[2]
							, &rcBush2
							, NULL
							, &D3DXVECTOR3(-50, 400, 0)
							, D3DXCOLOR(1,1,1,1)	);

		m_pSprite->Draw(	m_pTex[2]
							, &rcBush2
							, NULL
							, &D3DXVECTOR3(300, 400, 0)
							, D3DXCOLOR(1,1,1,1)	);

		m_pSprite->Draw(	m_pTex[2]
							, &rcBush2
							, NULL
							, &D3DXVECTOR3(600, 400, 0)
							, D3DXCOLOR(1,1,1,1)	);


		// 바닥을 그린다.
		RECT	rcTile1= {0,0, m_pImg[3].Width, m_pImg[3].Height};
		RECT	rcTile2= {0,66, m_pImg[3].Width, m_pImg[3].Height};

		for(int i=0; i<7; ++i)
		{
			m_pSprite->Draw(   m_pTex[3]
								, &rcTile1
								, NULL
								, &D3DXVECTOR3(i* m_pImg[3].Width* 1.f, 440.f, 0)
								, D3DXCOLOR(1,1,1,1)	);

			m_pSprite->Draw(   m_pTex[3]
								, &rcTile2
								, NULL
								, &D3DXVECTOR3(i* m_pImg[3].Width* 1.f, 550, 0)
								, D3DXCOLOR(1,1,1,1)	);
		}

	m_pSprite->End();
}