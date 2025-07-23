// Implementation of the CMain class.
//
////////////////////////////////////////////////////////////////////////////////


#include "_StdAfx.h"


CMain::CMain()
{
	m_pTxBck	= NULL;
	m_pTxAni	= NULL;
}


INT CMain::Init()
{
	D3DXFONT_DESC hFont =
	{
		14, 0
		, FW_BOLD, 1, FALSE
		, HANGUL_CHARSET
		, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FF_DONTCARE
		, "굴림체"
	};

	D3DXCreateFontIndirect(GDEVICE, &hFont, &m_pD3DXFont);

	m_pTxBck = new CLcTexture;
	if( FAILED( m_pTxBck->Create(m_pd3dDevice, "Texture/mario_back.png", 0x0000000)))
		return -1;


	m_pTxBck->GetImageRect(&m_ImgRcB);

	m_pTxAni = new CLcTexture;
	if( FAILED( m_pTxAni->Create(m_pd3dDevice, "Texture/mario_all.png", 0x00FFFFFF)))
		return -1;
	

	SetRect(&m_ImgRc1,   0,							   0,  25, m_pTxAni->GetImageHeight()/2);
	SetRect(&m_ImgRc2, 125, m_pTxAni->GetImageHeight()/2, 150, m_pTxAni->GetImageHeight());
	m_dTimeBgn	=timeGetTime();

	return 0;
}

void CMain::Destroy()
{
	SAFE_RELEASE(	m_pD3DXFont	);

	SAFE_DELETE(	m_pTxBck	);
	SAFE_DELETE(	m_pTxAni	);
}


INT CMain::FrameMove()
{
	m_dTimeEnd	= timeGetTime();

	if( (m_dTimeEnd-m_dTimeBgn)>140)
	{
		m_ImgRc1.left +=25;
		m_ImgRc2.left +=25;

		if(m_ImgRc1.left +25 >=450)
			m_ImgRc1.left = 0;

		if(m_ImgRc2.left +25 >=450)
			m_ImgRc2.left = 0;

		m_ImgRc1.right =m_ImgRc1.left +25;
		m_ImgRc2.right =m_ImgRc2.left +25;

		m_dTimeBgn = m_dTimeEnd;
	}

	return 0;
}


INT CMain::Render()
{
	m_pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER, 0xFF006699, 1.0f, 0 );

	if( FAILED( m_pd3dDevice->BeginScene() ) )
		return -1;


	m_pd3dSprite->Begin(D3DXSPRITE_ALPHABLEND);


	m_pd3dSprite->Draw(m_pTxBck->GetTexture()
						, &m_ImgRcB
						, NULL
						, NULL
						, D3DXCOLOR(1,1,1,1));



	D3DXMATRIX			mtW;
	D3DXMatrixIdentity(&mtW);
	mtW._11 =  3.f;
	mtW._22 =  3.f;
	mtW._41	=  200;
	mtW._42	=  308;
	m_pd3dSprite->SetTransform(&mtW);

	m_pd3dSprite->Draw(m_pTxAni->GetTexture()
						, &m_ImgRc1
						, NULL
						, NULL
						, D3DXCOLOR(1,1,1,1));


	D3DXMatrixIdentity(&mtW);
	mtW._11 = -2.f;
	mtW._22 =  2.f;
	mtW._41	=  750;
	mtW._42	=  335;
	m_pd3dSprite->SetTransform(&mtW);

	m_pd3dSprite->Draw(m_pTxAni->GetTexture()
						, &m_ImgRc1
						, NULL
						, NULL
						, D3DXCOLOR(1,1,1,1));

	D3DXMatrixIdentity(&mtW);
	m_pd3dSprite->SetTransform(&mtW);

	m_pd3dSprite->End();




	RECT	rt	= { 10, 10, m_dScnX-10, 50};
	m_pD3DXFont->DrawText(NULL, "Animation Texture..", -1, &rt, 0, D3DXCOLOR(1,1,0,1));


	// EndScene
	m_pd3dDevice->EndScene();

	return 0;
}


LRESULT CMain::MsgProc(HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	switch( msg )
	{
		case WM_PAINT:
		{
			break;
		}
	}

	return CD3DApp::MsgProc( hWnd, msg, wParam, lParam );
}