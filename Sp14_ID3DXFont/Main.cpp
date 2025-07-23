// Implementation of the CMain class.
//
////////////////////////////////////////////////////////////////////////////////


#include "_StdAfx.h"


CMain::CMain()
{
	m_pDXFont1	= NULL;
	m_pDXFont2	= NULL;
}


INT CMain::Init()
{
	if( FAILED(D3DXCreateFont( m_pd3dDevice
							, 20
							, 0
							, FW_BOLD
							, 1
							, FALSE
							, HANGUL_CHARSET
							, OUT_DEFAULT_PRECIS
							, ANTIALIASED_QUALITY
							, FF_DONTCARE
							, "궁서체"
							, &m_pDXFont1 )))
		return -1;



	D3DXFONT_DESC hFont =
	{
		28, 0
		, FW_BOLD, 1, FALSE
		, HANGUL_CHARSET
		, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FF_DONTCARE
		, "굴림체"
	};

	if(FAILED(D3DXCreateFontIndirect(GDEVICE, &hFont, &m_pDXFont2)))
		return -1;

	return 0;
}

void CMain::Destroy()
{
	SAFE_RELEASE(	m_pDXFont1	);
	SAFE_RELEASE(	m_pDXFont2	);
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


	RECT	rc;
	::SetRect(&rc, 100, 50, 500, 50 + 30);

	m_pDXFont1->DrawText(NULL
						, "Hello world"
						, -1
						, &rc
						, 0
						, D3DXCOLOR(1,1,0,1)
						);

	::SetRect(&rc, 100, 90, 800, 90 + 30);

	m_pDXFont2->DrawText(NULL
						, "안녕하세요. ID3DXFont 예제입니다."
						, -1
						, &rc
						, 0
						, D3DXCOLOR(0,1,1,1)
						);



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