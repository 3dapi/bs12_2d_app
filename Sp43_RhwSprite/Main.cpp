// Implementation of the CMain class.
//
////////////////////////////////////////////////////////////////////////////////


#include "_StdAfx.h"


CMain::CMain()
{
	m_pD3DXFont	= NULL;
	m_pSprite	= NULL;
	m_pTx0		= NULL;
	m_pTx1		= NULL;
}


INT CMain::Init()
{
	INT hr=-1;
	D3DXFONT_DESC hFont =
	{
		14, 0
		, FW_BOLD, 1, FALSE
		, HANGUL_CHARSET
		, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FF_DONTCARE
		, "굴림체"
	};

	D3DXCreateFontIndirect(GDEVICE, &hFont, &m_pD3DXFont);


	m_pSprite = new CMcSprite;
	m_pSprite->Create(m_pd3dDevice);

	
	hr = D3DXCreateTextureFromFileEx(	m_pd3dDevice
									, "Texture/tile.png"
									, D3DX_DEFAULT
									, D3DX_DEFAULT
									, 1
									, 0
									, D3DFMT_UNKNOWN
									, D3DPOOL_MANAGED
									, D3DX_DEFAULT
									, D3DX_DEFAULT
									, 0x00FFFFFF
									, NULL
									, NULL
									, &m_pTx1);

	hr = D3DXCreateTextureFromFileEx(	m_pd3dDevice
									, "Texture/tank_gril.jpg"
									, D3DX_DEFAULT
									, D3DX_DEFAULT
									, 1
									, 0
									, D3DFMT_UNKNOWN
									, D3DPOOL_MANAGED
									, D3DX_FILTER_NONE
									, D3DX_FILTER_NONE
									, 0x00000000
									, NULL
									, NULL
									, &m_pTx0);

	return 0;
}


void CMain::Destroy()
{
	SAFE_RELEASE(	m_pD3DXFont	);

	SAFE_RELEASE(	m_pTx0		);
	SAFE_RELEASE(	m_pTx1		);

	SAFE_DELETE(	m_pSprite	);
}




INT CMain::Restore()
{
	m_pD3DXFont->OnResetDevice();

	return 0;
}


void CMain::Invalidate()
{
	m_pD3DXFont->OnLostDevice();
}


INT CMain::FrameMove()
{
	return 0;
}


INT CMain::Render()
{
	m_pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER, 0xFF006699, 1.0f, 0 );

	if( FAILED( m_pd3dDevice->BeginScene() ) )
		return -1;


	// Set up the textures
	m_pSprite->SetTexture(0, m_pTx0);
	m_pSprite->SetTexture(1, m_pTx1);
	m_pSprite->Render();


	RECT	rt	= { 10, 10, m_dScnX-10, 50};
	m_pD3DXFont->DrawText(NULL, "Change Window: ALT + Enter", -1, &rt, 0, D3DXCOLOR(1,1,0,1));


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