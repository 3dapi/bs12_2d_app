// Implementation of the CMain class.
//
////////////////////////////////////////////////////////////////////////////////


#include "_StdAfx.h"


CMain::CMain()
{
}


INT CMain::Init()
{
	if( FAILED( m_TexBack.Create( m_pd3dDevice, "Texture/dx5_logo.bmp")))
		return -1;

	return 0;
}

void CMain::Destroy()
{
	m_TexBack.Destroy();
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


	RECT				rt1;
	LPDIRECT3DTEXTURE9	pTx;

	m_TexBack.GetImageRect(&rt1);
	pTx = m_TexBack.GetTexture();

	m_pd3dSprite->Begin(D3DXSPRITE_ALPHABLEND);
	m_pd3dSprite->Draw(pTx, &rt1, NULL, NULL, D3DXCOLOR(1,1,1,1));
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