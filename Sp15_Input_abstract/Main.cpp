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


	if(FAILED(LcDev_InputCreate(0, &m_pInput, m_hWnd)))
		return -1;

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
	{
		m_pInput->FrameMove();

		if(ILcInput::EINPUT_DBCLC == m_pInput->BtnState(0))
		{
			char	sMsg[1024]={0};
			sprintf(sMsg, "L Button Doble Click");
			SetWindowText(m_hWnd, sMsg);
		}

		if(ILcInput::EINPUT_DBCLC == m_pInput->BtnState(1))
		{
			char	sMsg[1024]={0};
			sprintf(sMsg, "R Button Doble Click");
			SetWindowText(m_hWnd, sMsg);
		}

		if(ILcInput::EINPUT_DBCLC == m_pInput->BtnState(2))
		{
			char	sMsg[1024]={0};
			sprintf(sMsg, "M Button Doble Click");
			SetWindowText(m_hWnd, sMsg);
		}
	}




	return 0;
}


INT CMain::Render()
{
	INT		i;

	m_pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER, 0xFF006699, 1.0f, 0 );

	if( FAILED( m_pd3dDevice->BeginScene() ) )
		return -1;


	RECT	rt	= { 10, 10, m_dScnX-10, 50};
	TCHAR	sMsg[128];

	sprintf(sMsg, "FPS: %4.f", m_fFps);
	m_pD3DXFont->DrawText(NULL, sMsg, -1, &rt, 0, D3DXCOLOR(1,1,0,1));

	rt.top +=60;
	rt.bottom = rt.top + 30;


//	if(m_pInput)
//	{
//		int n0	= m_pInput->m_dBtnCnt[0];
//		int n1	= m_pInput->m_dBtnCnt[1];
//		int n2	= m_pInput->m_dBtnCnt[2];
//
//		sprintf(sMsg, "Mouse L: %d  R: %d  M:%d", n0, n1, n2);
//
//		m_pD3DXFont->DrawText(NULL, sMsg, -1, &rt, 0, D3DXCOLOR(1,1,1,1));
//	}



	rt.top +=60;
	rt.bottom = rt.top + 30;

	if(m_pInput)
	{
		D3DXVECTOR3	vcMouse = m_pInput->GetMousePos();
		sprintf(sMsg, "Mouse X: %.f  Y: %.f  Z: %.f", vcMouse.x, vcMouse.y, vcMouse.z);

		m_pD3DXFont->DrawText(NULL, sMsg, -1, &rt, 0, D3DXCOLOR(1,1,1,1));
	}


	rt.top +=60;
	rt.bottom = rt.top + 30;

	if(m_pInput)
	{
		static RECT rc = {0,100,400,130};

		D3DXVECTOR3	vcEps = m_pInput->GetMouseEps();

		rc.top += long(vcEps.z/40);
		rc.bottom =rc.top + 30;
		sprintf(sMsg, "Mouse Epsilon(%.f, %.f, %.f), top: %d", vcEps.x, vcEps.y, vcEps.z, rc.top);

		m_pD3DXFont->DrawText(NULL, sMsg, -1, &rc, 0, D3DXCOLOR(1,0,1,1));
	}


	rt.top +=60;
	rt.bottom = rt.top + 30;

	sprintf(sMsg, "Try to Press L or R or M button");
	m_pD3DXFont->DrawText(NULL, sMsg, -1, &rt, 0, D3DXCOLOR(1,1,1,1));

	rt.top +=30;
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


	rt.top +=60;
	rt.bottom = rt.top + 30;

	sprintf(sMsg, "Keboard Test. Try to Press Ani Key");

	for(i=0; i<256; ++i)
	{
		if( m_pInput->KeyDown(i))
		{
			sprintf(sMsg, "key Downed: ascii(%c: %d)", i, i);
		}
	}

	for(i=0; i<256; ++i)
	{
		if( m_pInput->KeyPress(i))
		{
			sprintf(sMsg, "key Pressed: ascii(%c: %d)", i, i);
		}
	}

	for(i=0; i<256; ++i)
	{
		if( m_pInput->KeyUp(i))
		{
			sprintf(sMsg, "key Up:  ascii(%c: %d)", i, i);
		}
	}


	m_pD3DXFont->DrawText(NULL, sMsg, -1, &rt, 0, D3DXCOLOR(1,1,0,1));


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