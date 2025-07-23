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
	m_pTex1	= new CLcTexture;
	if( FAILED(m_pTex1->Create(m_pd3dDevice, "Texture/dx5_logo.bmp")))
		return -1;

	return 0;
}

void CMain::Destroy()
{
	SAFE_DELETE(	m_pTex1	);
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


	RECT				rc1;
	D3DXMATRIX			mtW;
	LPDIRECT3DTEXTURE9	pTex1 = m_pTex1->GetTexture();

	m_pTex1->GetImageRect(&rc1);
	
	
	m_pd3dSprite->Begin(D3DXSPRITE_ALPHABLEND);

	//가장 일반적인 방법
	D3DXMatrixIdentity(&mtW);
	m_pd3dSprite->SetTransform(&mtW);

	m_pd3dSprite->Draw(pTex1
						, &rc1
						, NULL
						, &D3DXVECTOR3(50, 50, 0)
						, D3DXCOLOR(1,1,1,1));


	// 행렬을 이용한 방법
	D3DXMatrixIdentity(&mtW);
	mtW._11 =  0.5f;
	mtW._22 =  0.5f;
	mtW._41	=  100 + (rc1.right - rc1.left) * 1.f;
	mtW._42	=   50 + (rc1.bottom - rc1.top) * 1.f;
	m_pd3dSprite->SetTransform(&mtW);

	m_pd3dSprite->Draw(pTex1
						, &rc1
						, NULL
						, NULL
						, D3DXCOLOR(1,1,1,1));



	D3DXMatrixIdentity(&mtW);
	mtW._11 = -0.5f;
	mtW._22 =  0.5f;
	mtW._41 = 100 + (rc1.right - rc1.left) * 2.f;
	mtW._42	=  50 + (rc1.bottom - rc1.top) * 1.f;
	m_pd3dSprite->SetTransform(&mtW);

	m_pd3dSprite->Draw(pTex1
						, &rc1
						, NULL
						, NULL
						, D3DXCOLOR(1,1,1,1));



	D3DXMatrixIdentity(&mtW);
	mtW._11 =  0.5f;
	mtW._22 = -0.5f;
	mtW._41	= 100 + (rc1.right - rc1.left) * 1.f;
	mtW._42	=  50 + (rc1.bottom - rc1.top) * 2.f;
	m_pd3dSprite->SetTransform(&mtW);

	m_pd3dSprite->Draw(pTex1
						, &rc1
						, NULL
						, NULL
						, D3DXCOLOR(1,1,1,1));



	D3DXMatrixIdentity(&mtW);
	mtW._11 = -.5f;
	mtW._22 = -.5f;
	mtW._41	= 100 + (rc1.right - rc1.left) * 2.f;
	mtW._42	=  50 + (rc1.bottom - rc1.top) * 2.f;
	m_pd3dSprite->SetTransform(&mtW);

	m_pd3dSprite->Draw(pTex1
						, &rc1
						, NULL
						, NULL
						, D3DXCOLOR(1,1,1,1));
	

	D3DXMatrixIdentity(&mtW);
	m_pd3dSprite->SetTransform(&mtW);
	m_pd3dSprite->End();


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