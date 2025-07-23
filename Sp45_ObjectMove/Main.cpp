// Implementation of the CMain class.
//
////////////////////////////////////////////////////////////////////////////////


#include "_StdAfx.h"


CMain::CMain()
{
	m_pInput	= NULL;
	m_pBack		= NULL;

	m_pMario	= NULL;
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




	//1. Input 생성
	m_pInput = new CLcInput;

	m_pInput->Create(m_hWnd);

	//2. 시간
	m_dTimeBgn = GetTickCount();
	m_dTimeCur = m_dTimeBgn;
	m_dTimeAvg = 4.f;
	m_dTimeCnt = 0;



	//3. 게임 데이터 생성
	m_pBack = new CBackground;

	if(FAILED(m_pBack->Create(m_pd3dDevice, m_pd3dSprite)))
	{
		delete m_pBack;
		return -1;
	}


	m_pMario = new CGameObj;

	if(FAILED(m_pMario->Create(m_pd3dDevice, m_pd3dSprite)))
	{
		delete m_pMario;
		return -1;
	}



	return 0;
}

void CMain::Destroy()
{
	SAFE_RELEASE(	m_pD3DXFont	);
	SAFE_DELETE(	m_pInput	);

	SAFE_DELETE(	m_pBack		);
	SAFE_DELETE(	m_pMario	);
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
	//1. Input Update
	m_pInput->FrameMove();

	++m_dTimeCnt;

	//2. system time update
	if(m_dTimeCnt>=10)
	{
		m_dTimeCur = GetTickCount();
		m_dTimeAvg = FLOAT(m_dTimeCur - m_dTimeBgn)/m_dTimeCnt;
		m_dTimeBgn = m_dTimeCur;
		m_dTimeCnt = 0;
	}


	//3.1 game data update
	m_pBack->FrameMove();


	// 3.2 Mario Update
	m_pMario->m_nDir = 0;

	if(m_pInput->KeyPress(VK_RIGHT))
	{
		m_pMario->m_nDir = 1;

		if(m_pInput->KeyPress(VK_UP))
			m_pMario->m_nDir = 2;

		if(m_pInput->KeyPress(VK_DOWN))
			m_pMario->m_nDir = 8;

	}

	if(m_pInput->KeyPress(VK_LEFT))
	{
		m_pMario->m_nDir = 5;

		if(m_pInput->KeyPress(VK_UP))
			m_pMario->m_nDir = 4;

		if(m_pInput->KeyPress(VK_DOWN))
			m_pMario->m_nDir = 6;
	}

	if(m_pInput->KeyPress(VK_UP))
	{
		m_pMario->m_nDir = 3;

		if(m_pInput->KeyPress(VK_RIGHT))
			m_pMario->m_nDir = 2;

		if(m_pInput->KeyPress(VK_LEFT))
			m_pMario->m_nDir = 4;

	}

	if(m_pInput->KeyPress(VK_DOWN))
	{
		m_pMario->m_nDir = 7;

		if(m_pInput->KeyPress(VK_RIGHT))
			m_pMario->m_nDir = 8;

		if(m_pInput->KeyPress(VK_LEFT))
			m_pMario->m_nDir = 6;
	}

	m_pMario->FrameMove();


	return 0;
}


INT CMain::Render()
{
	m_pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER, 0xFF006699, 1.0f, 0 );

	if( FAILED( m_pd3dDevice->BeginScene() ) )
		return -1;


	m_pBack->Render();

	m_pMario->Render();

	RECT	rt	= { 10, 10, m_dScnX-10, 50};
	TCHAR	sMsg[128];

	FLOAT fFPS = GetAvgTime();
	sprintf(sMsg, "Average Frame Time: %f", fFPS);
	m_pD3DXFont->DrawText(NULL, sMsg, -1, &rt, 0, D3DXCOLOR(1,1,0,1));

	rt.top +=60;
	rt.bottom = rt.top + 30;

	// EndScene
	m_pd3dDevice->EndScene();

	return 0;
}



FLOAT CMain::GetAvgTime()
{
	return m_dTimeAvg;
}


FLOAT CMain::GetAvgFrame()
{
	return 1000.f/m_dTimeAvg;
}











LRESULT CMain::MsgProc(HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	switch( msg )
	{
		case WM_PAINT:
		{
			break;
		}

		case WM_MOUSEWHEEL:
		{
			INT c= HIWORD(wParam);
			INT d= LOWORD(wParam);

			m_pInput->AddZ( short( HIWORD(wParam) ) );

			break;
		}


	}

	return CD3DApp::MsgProc( hWnd, msg, wParam, lParam );
}