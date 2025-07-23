// Implementation of the CMain class.
//
////////////////////////////////////////////////////////////////////////////////


#include "_StdAfx.h"

void McColor_TransColorMono(DWORD* pOut, DWORD* pIn, INT iImgW, INT iImgH)
{
	for(int y=0; y<iImgH; ++y)
	{
		for(int x=0; x<iImgW; ++x)
		{
			int nIdx = y*iImgW + x;

			D3DXCOLOR xclr = pIn[nIdx];

			//I = 0.30R + 0.59G + 0.11B
			float fclr =0.f;

//			fclr = xclr.r * 0.3f + xclr.g * 0.59f + xclr.b * 0.11f;
			fclr = 0.f;

			pOut[nIdx] = D3DXCOLOR(fclr, fclr, fclr, xclr.a);
		}
	}
}


CMain::CMain()
{
	m_pLcSprite	= NULL;
	m_pInput	= NULL;
	

	m_pTexBack	= NULL;
	m_pTexAni	= NULL;
	m_pTexAniS	= NULL;
}


INT CMain::Init()
{
	m_pLcSprite = new CLcSprite;
	if(FAILED(m_pLcSprite->Create(m_pd3dSprite)))
		return -1;

	m_pInput = new CLcInput;
	if( FAILED(m_pInput->Create(m_hWnd)))
		return -1;



	
	m_pTexBack	= new CLcTexture;
	if( FAILED(m_pTexBack->Create(m_pd3dDevice, "Texture/mario_back.png")))
		return -1;

	m_pTexAni	= new CLcTexture;
	if( FAILED(m_pTexAni->Create(m_pd3dDevice, "Texture/mario_all.png")))
		return -1;	



	// 그림자 이미지 만들기.
	D3DSURFACE_DESC dsc;
	D3DLOCKED_RECT	drc;
	DWORD*	pColorSrc= NULL;
	DWORD*	pColorDst= NULL;

	LPDIRECT3DTEXTURE9	pTexAni = m_pTexAni->GetTexture();

	pTexAni->GetLevelDesc(0, &dsc);

	INT ImgW	= dsc.Width;
	INT	ImgH	= dsc.Height;
	m_pTexAniS	= NULL;

	pColorSrc	= new DWORD[ImgW * ImgH];


	// 임시 버퍼에 칼라 값들을 복사한다.
	pTexAni->LockRect(0, &drc, NULL, 0);
	{
		memcpy(pColorSrc, drc.pBits, ImgW * ImgH * sizeof(DWORD));
	}
	pTexAni->UnlockRect(0);


	//Image Processing할 이미지 텍스처를 만든다.
	D3DXCreateTexture(m_pd3dDevice, ImgW, ImgH, 1, 0, dsc.Format, D3DPOOL_MANAGED, &m_pTexAniS);


	//Image Processing...
	m_pTexAniS->LockRect(0, &drc, NULL, 0);
	{
		pColorDst = (DWORD*)drc.pBits;
		McColor_TransColorMono(pColorDst, pColorSrc, ImgW, ImgH);
	}
	m_pTexAniS->UnlockRect(0);


	delete [] pColorSrc;



	SetRect(&m_ImgRc1,   0, 0,  25, m_pTexAni->GetImageHeight()/2);

	m_dTimeBgn	=timeGetTime();


	return 0;
}

void CMain::Destroy()
{
	SAFE_DELETE(	m_pLcSprite	);
	SAFE_DELETE(	m_pInput	);

	SAFE_DELETE(	m_pTexBack	);
	SAFE_DELETE(	m_pTexAni	);
	SAFE_RELEASE(	m_pTexAniS	);
}


INT CMain::FrameMove()
{
	if(m_pInput)
		m_pInput->FrameMove();


	m_dTimeEnd	= timeGetTime();

	if( (m_dTimeEnd-m_dTimeBgn)>140)
	{
		m_ImgRc1.left +=25;


		if(m_ImgRc1.left +25 >=450)
			m_ImgRc1.left = 0;

		m_ImgRc1.right =m_ImgRc1.left +25;

		m_dTimeBgn = m_dTimeEnd;
	}
	
	return 0;
}


INT CMain::Render()
{
	m_pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0,120,160), 1.0f, 0 );

	if( FAILED( m_pd3dDevice->BeginScene() ) )
		return -1;


	RECT	rc;
	m_pTexBack->GetImageRect(&rc);

	m_pLcSprite->Draw(
					m_pTexBack->GetTexture()
					, &rc
					, NULL
					, NULL
					, 0
					, NULL
					, D3DXCOLOR(1,1,1,1));


	m_pLcSprite->Draw(
					m_pTexAni->GetTexture()
				,	&m_ImgRc1
				,	&D3DXVECTOR2(3,3)
				,	NULL
				,	0
				,	&D3DXVECTOR2(200,308)
				,	D3DXCOLOR(1,1,1,1));


	m_pLcSprite->Draw(
					m_pTexAniS
				,	&m_ImgRc1
				,	&D3DXVECTOR2(3.f,-1.5f)
				,	NULL
				,	0
				,	&D3DXVECTOR2(200,308 + m_pTexAni->GetImageHeight() * 2.2f)
				,	D3DXCOLOR(1,1,1,0.5f));

	
	// EndScene
	m_pd3dDevice->EndScene();

	return 0;
}


LRESULT CMain::MsgProc(HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	if(m_pInput)
		m_pInput->MsgProc(hWnd, msg, wParam, lParam);
	
	switch( msg )
	{
		case WM_PAINT:
		{
			break;
		}
	}

	return CD3DApp::MsgProc( hWnd, msg, wParam, lParam );
}