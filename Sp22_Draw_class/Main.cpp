// Implementation of the CMain class.
//
////////////////////////////////////////////////////////////////////////////////


#include "_StdAfx.h"


CMain::CMain()
{
	m_pTex1	= NULL;
}


INT CMain::Init()
{
	m_pLcSprite = new CLcSprite;
	if(FAILED(m_pLcSprite->Create(m_pd3dSprite)))
		return -1;


	m_pTex1	= new CLcTexture;
	if( FAILED(m_pTex1->Create(m_pd3dDevice, "Texture/dx5_logo.bmp")))
		return -1;


	return 0;
}

void CMain::Destroy()
{
	SAFE_DELETE(	m_pTex1		);
	SAFE_DELETE(	m_pLcSprite	);
}


INT CMain::FrameMove()
{
	return 0;
}


INT CMain::Render()
{
	m_pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0,120,160), 1.0f, 0 );

	if( FAILED( m_pd3dDevice->BeginScene() ) )
		return -1;


	D3DXVECTOR2			vcPos;
	RECT				rc1;
	LPDIRECT3DTEXTURE9	pTex1 = m_pTex1->GetTexture();

	m_pTex1->GetImageRect(&rc1);

	m_pLcSprite->Draw(pTex1, &rc1, NULL, NULL, 0, &D3DXVECTOR2(50, 50), D3DXCOLOR(1,1,1,1));


	vcPos.x = 100 + (rc1.right - rc1.left) * 1.f;
	vcPos.y =  50 + (rc1.bottom - rc1.top) * 1.f;

	m_pLcSprite->Draw(pTex1
						, &rc1
						, &D3DXVECTOR2(0.5f, 0.5f)
						, NULL
						, 0
						, &vcPos
						, D3DXCOLOR(1,1,1,1));



	vcPos.x = 100 + (rc1.right - rc1.left) * 2.f;
	vcPos.y =  50 + (rc1.bottom - rc1.top) * 1.f;

	m_pLcSprite->Draw(pTex1
						, &rc1
						, &D3DXVECTOR2(-0.5f, 0.5f)
						, NULL
						, 0
						, &vcPos
						, D3DXCOLOR(1,1,1,1));


	
	vcPos.x = 100 + (rc1.right - rc1.left) * 1.f;
	vcPos.y =  50 + (rc1.bottom - rc1.top) * 2.f;

	m_pLcSprite->Draw(pTex1
						, &rc1
						, &D3DXVECTOR2(0.5f, -0.5f)
						, NULL
						, 0
						, &vcPos
						, D3DXCOLOR(1,1,1,1));



	vcPos.x = 100 + (rc1.right - rc1.left) * 2.f;
	vcPos.y =  50 + (rc1.bottom - rc1.top) * 2.f;

	m_pLcSprite->Draw(pTex1
						, &rc1
						, &D3DXVECTOR2(-0.5f, -0.5f)
						, NULL
						, 0
						, &vcPos
						, D3DXCOLOR(1,1,1,1));
	
	
	m_pLcSprite->Draw(pTex1
						, &rc1
						, &D3DXVECTOR2(.7f,.7f)
						, &D3DXVECTOR2(120,250)
						, 35
						, &D3DXVECTOR2(500,50)
						, D3DXCOLOR(0,1,1,1));


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