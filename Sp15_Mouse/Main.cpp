// Implementation of the CMain class.
//
////////////////////////////////////////////////////////////////////////////////


#include "_StdAfx.h"


CMain::CMain()
{
	m_pInput	= NULL;
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

	m_pInput = new CLcInput;
	m_pInput->Create(m_hWnd);

	return 0;
}

void CMain::Destroy()
{
	SAFE_RELEASE(	m_pD3DXFont	);
	SAFE_DELETE(	m_pInput	);
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
	if(m_pInput)
		m_pInput->FrameMove();

	return 0;
}


INT CMain::Render()
{
	m_pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER, 0xFF006699, 1.0f, 0 );

	if( FAILED( m_pd3dDevice->BeginScene() ) )
		return -1;




	RECT	rt	= { 10, 10, m_dScnX-10, 50};
	TCHAR	sMsg[128];

	sprintf(sMsg, "FPS: %4.f", m_fFps);
	m_pD3DXFont->DrawText(NULL, sMsg, -1, &rt, 0, D3DXCOLOR(1,1,0,1));

	rt.top +=60;
	rt.bottom = rt.top + 30;


	if(m_pInput)
	{
		D3DXVECTOR3	vcP= m_pInput->GetMousePos();
		sprintf(sMsg, "Mouse Position X: %3.f  Y: %3.f  Z: %3.f", vcP.x, vcP.y, vcP.z);

		m_pD3DXFont->DrawText(NULL, sMsg, -1, &rt, 0, D3DXCOLOR(1,1,1,1));
	}


	rt.top +=60;
	rt.bottom = rt.top + 30;

	if(m_pInput->BtnPress(0))
	{
		sprintf(sMsg, "You Pressed L Button");
		m_pD3DXFont->DrawText(NULL, sMsg, -1, &rt, 0, D3DXCOLOR(1,1,0,1));
	}

	if(m_pInput->BtnPress(1))
	{
		sprintf(sMsg, "You Pressed R Button");
		m_pD3DXFont->DrawText(NULL, sMsg, -1, &rt, 0, D3DXCOLOR(1,1,0,1));
	}

	if(m_pInput->BtnPress(2))
	{
		sprintf(sMsg, "You Pressed M Button");
		m_pD3DXFont->DrawText(NULL, sMsg, -1, &rt, 0, D3DXCOLOR(1,1,0,1));
	}





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