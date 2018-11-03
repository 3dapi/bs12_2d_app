// Implementation of the CD3DApp class.
//
//////////////////////////////////////////////////////////////////////


#include "_StdAfx.h"


static CD3DApp*	g_pD3DApp;


CD3DApp::CD3DApp()
{
	g_pD3DApp	= this;

	strcpy(m_sCls, "2D Game App");

	m_hInst			= NULL;
	m_hWnd			= NULL;
	m_dWinStyle		= WS_OVERLAPPED| WS_CAPTION| WS_SYSMENU| WS_VISIBLE;
	m_dScnX			= 800;
	m_dScnY			= 600;

	m_bWindow		= TRUE;		// Window mode
	m_bDeviceLost	= FALSE;
	m_bShowCusor	= TRUE;

	m_pD3D			= NULL;			// D3D
	m_pd3dDevice	= NULL;			// Device
	m_pd3dSprite	= NULL;			// 2D Sprite
	m_pBackBuffer	= NULL;
}


INT CD3DApp::Create( HINSTANCE hInst)
{
	m_hInst	= hInst;

	WNDCLASS wc =								// Register the window class
	{
		CS_CLASSDC
		, WndProc
		, 0L
		, 0L
		, m_hInst
		, NULL
		, LoadCursor(NULL,IDC_ARROW)
		, (HBRUSH)GetStockObject(WHITE_BRUSH)
		, NULL
		, m_sCls
	};

	RegisterClass( &wc );

	RECT rc;									//Create the application's window

	SetRect( &rc, 0, 0, m_dScnX, m_dScnY);
	AdjustWindowRect( &rc, m_dWinStyle, FALSE );

	int iScnSysW = ::GetSystemMetrics(SM_CXSCREEN);
	int iScnSysH = ::GetSystemMetrics(SM_CYSCREEN);

	m_hWnd = CreateWindow( m_sCls
		, m_sCls
		, m_dWinStyle
		, (iScnSysW - (rc.right-rc.left))/2
		, (iScnSysH - (rc.bottom-rc.top))/2
		, (rc.right  - rc.left)
		, (rc.bottom - rc.top)
		, NULL
		, NULL
		, m_hInst
		, NULL );


	GetWindowRect( m_hWnd, &m_rcWin );

	// D3D생성
	if( NULL == ( m_pD3D = Direct3DCreate9( D3D_SDK_VERSION ) ) )
		return -1;


	// D3D를 통해서 화면 모드를 찾는다.
	D3DDISPLAYMODE d3ddm;
    if( FAILED( m_pD3D->GetAdapterDisplayMode( D3DADAPTER_DEFAULT, &d3ddm ) ) )
        return -1;


	// 디바이스를 생성하기 위해서는 프리젠트 파라메터 구조체가 필요
	// 전부 0으로 셋팅한다음 일부만 변수세팅


	memset(&m_d3dpp, 0, sizeof(m_d3dpp));
	m_d3dpp.Windowed				= m_bWindow;
	m_d3dpp.SwapEffect				= D3DSWAPEFFECT_DISCARD;
	m_d3dpp.BackBufferFormat		= d3ddm.Format;
	m_d3dpp.BackBufferCount			= 2;
	m_d3dpp.BackBufferWidth			= m_dScnX;
	m_d3dpp.BackBufferHeight		= m_dScnY;
	m_d3dpp.EnableAutoDepthStencil	= TRUE;
	m_d3dpp.AutoDepthStencilFormat	= D3DFMT_D24S8;
	m_d3dpp.FullScreen_RefreshRateInHz = m_bWindow? 0 : d3ddm.RefreshRate;
	m_d3dpp.Flags					= D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;		// Back Buffer를 이용하려면..


	// D3DADAPTER_DEFAULT: 대부분의 그래픽카드는 모노 듀얼일 경우 이부분을 수정
	// D3DDEVTYPE_HAL : 하드웨어 가속(가장 큰 속도)을 받을 것인가.. 하드웨어 지
	// 원이 없을 경우 D3D는 소프트웨어로 이를 대체 할 수 있다.

	if( FAILED( m_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, m_hWnd,
		D3DCREATE_MIXED_VERTEXPROCESSING, &m_d3dpp, &m_pd3dDevice ) ) )
	{
		if( FAILED( m_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, m_hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING, &m_d3dpp, &m_pd3dDevice ) ) )
		{
			SAFE_RELEASE(	m_pd3dDevice	);
			SAFE_RELEASE(	m_pD3D			);
			return -1;
		}
	}

	// DX의 스프라이트는 디바이스가 생성된 후에 만들어야 한다.
	if(FAILED(D3DXCreateSprite(m_pd3dDevice, &m_pd3dSprite)))
	{
		SAFE_RELEASE(	m_pd3dDevice	);
		SAFE_RELEASE(	m_pD3D			);
		return -1;
	}


	// DC를 이용하려면 Backbuffer를 가져와야
	if(FAILED(m_pd3dDevice->GetBackBuffer(
		0, 0, D3DBACKBUFFER_TYPE_MONO, &m_pBackBuffer )))
	{
		SAFE_RELEASE(	m_pd3dSprite	);
		SAFE_RELEASE(	m_pd3dDevice	);
		SAFE_RELEASE(	m_pD3D			);
		return -1;
	}


	ShowWindow( m_hWnd, SW_SHOW );
	UpdateWindow( m_hWnd );
	::ShowCursor(m_bShowCusor);

	if(FAILED(Init()))
		return -1;

	if(FAILED(Restore()))
		return -1;

	return 0;
}


void CD3DApp::Cleanup()
{
	Destroy();
	// 디바이스를 릴리즈하기전에 먼저 스프라이트를 해제해야 한다.
	SAFE_RELEASE(	m_pBackBuffer	);
	SAFE_RELEASE(	m_pd3dSprite	);
	SAFE_RELEASE(	m_pd3dDevice	);
	SAFE_RELEASE(	m_pD3D			);

}


INT CD3DApp::Run()
{

	// Load keyboard accelerators
	HACCEL hAccel = LoadAccelerators( NULL, MAKEINTRESOURCE(IDR_MAIN_ACCEL) );

	MSG msg;
	memset( &msg, 0, sizeof(msg) );

	while( msg.message!=WM_QUIT )
	{
		if( PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ) )
		{
			if( hAccel == NULL || m_hWnd == NULL || 0 == TranslateAccelerator( m_hWnd, hAccel, &msg ) )
			{
				TranslateMessage( &msg );
				DispatchMessage( &msg );
			}
		}
		else
		{

			if( m_bDeviceLost )
			{
				Sleep( 100 ); // Yield some CPU time to other processes
			}


			if( m_bDeviceLost )
			{
				HRESULT hr;

				// 디바이스를 계속해서 활용 할 수 있는지 테스트.
				if( FAILED( hr = m_pd3dDevice->TestCooperativeLevel() ) )
				{
					// 디바이스를 리셋한다.
					// 디바이스를 리셋하려면 디바이스와 관련된 모든 객체들의
					// 상태를 로스트(lost) 상태로 만들어야 한다.
					if( D3DERR_DEVICENOTRESET == hr )
					{
						Reset3D();
					}

					// 디바이스는 여전히 로스트 상태.
					// 이상태에서는 리셋을 호출하면 안된다.
					else if( D3DERR_DEVICELOST == hr )
					{

					}

				}

				else
					m_bDeviceLost = FALSE;
			}



			if(FALSE == m_bDeviceLost)
			{
				if(FAILED(Render3D()))
					break;
			}


			// 후면버퍼 전면버퍼 교체( flipping)
			HRESULT hr= m_pd3dDevice->Present( NULL, NULL, NULL, NULL);

			// 이 경우는 전체화면상태에서 다른 윈도우가 활성화 될 때(예를들어
			// ALT+TAB키, CTRL+ESC키 동작시) 필요하다.
			// 이 과정을 거쳐야만 계속해서 디바이스를 사용할 수 있다.
			// 일단 로스트 상태로 둔다.
			if( D3DERR_DEVICELOST == hr )
				m_bDeviceLost = TRUE;

		}
	}

	UnregisterClass( m_sCls, m_hInst);

	return 0;
}



LRESULT WINAPI CD3DApp::WndProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
	return g_pD3DApp->MsgProc(hWnd, msg, wParam, lParam);
}



LRESULT CD3DApp::MsgProc(HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	switch( msg )
	{
		case WM_COMMAND:
		{
			switch( LOWORD(wParam) )
			{
				case IDM_TOGGLEFULLSCREEN:
				{
					Reset3D();

					return 0;
				}



			}

			break;
		}

		case WM_KEYDOWN:
		{

			switch(wParam)
			{
				case VK_ESCAPE:
				{
					SendMessage(hWnd, WM_DESTROY, 0,0);
					break;
				}
			}

			break;

		}

		case WM_DESTROY:
		{
			Cleanup();
			PostQuitMessage( 0 );
			break;
		}
	}

	return DefWindowProc( hWnd, msg, wParam, lParam );
}



INT CD3DApp::Render3D()
{
	if( NULL == m_pd3dDevice )
		return -1;

	if(FAILED(FrameMove()))
		return -1;

	if(FAILED(Render()))
		return -1;

	return 0;
}


INT CD3DApp::Reset3D()
{
	Invalidate();

	m_bWindow ^=1;

	SAFE_RELEASE(	m_pBackBuffer	);

	if(	m_pd3dSprite	)
		m_pd3dSprite->OnLostDevice();

	m_d3dpp.Windowed				= m_bWindow;
	m_d3dpp.FullScreen_RefreshRateInHz = m_bWindow? 0 : 60;

	if(FAILED(m_pd3dDevice->Reset(&m_d3dpp)))
		return -1;

	if(	m_pd3dSprite	)
		m_pd3dSprite->OnResetDevice();

	if(FAILED(m_pd3dDevice->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &m_pBackBuffer )))
	{
		return -1;
	}

	if(m_bWindow)
	{
		SetWindowLong(m_hWnd, GWL_STYLE, m_dWinStyle);
		SetWindowPos(m_hWnd, HWND_NOTOPMOST
			, m_rcWin.left
			, m_rcWin.top
			, m_rcWin.right	- m_rcWin.left
			, m_rcWin.bottom	- m_rcWin.top
			, SWP_SHOWWINDOW);
	}
	else
	{
		SetWindowLong( m_hWnd, GWL_STYLE, WS_POPUP|WS_SYSMENU|WS_VISIBLE );
	}

	Sleep(100);

	Restore();

	return 0;
}