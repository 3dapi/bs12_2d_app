// D3D Tutorial
//
////////////////////////////////////////////////////////////////////////////////


#pragma warning( disable : 4996)


#define SAFE_DELETE(p)       { if(p) { delete (p);     (p)=NULL; } }
#define SAFE_DELETE_ARRAY(p) { if(p) { delete[] (p);   (p)=NULL; } }
#define SAFE_RELEASE(p)      { if(p) { (p)->Release(); (p)=NULL; } }

#pragma comment(lib, "legacy_stdio_definitions.lib")
#pragma comment(lib, "d3d9.lib")

#include <windows.h>

#include <d3d9.h>


TCHAR				m_sCls[128]		;
HINSTANCE			m_hInst		= NULL;
HWND				m_hWnd		= NULL;
DWORD				m_dWinStyle	= WS_OVERLAPPEDWINDOW| WS_VISIBLE;
DWORD				m_dScnX		= 800;			// Screen Width
DWORD				m_dScnY		= 600;			// Screen Height

												// 항상 포인터들은 NULL로 초기화
LPDIRECT3D9				m_pD3D		= NULL;		// D3D
LPDIRECT3DDEVICE9		m_pd3dDevice= NULL;		// Device
D3DPRESENT_PARAMETERS	m_d3dpp;



BOOL				m_bWindow		= FALSE;	// Window mode
BOOL				m_bDeviceLost	= FALSE;


BOOL				m_bShowCusor= TRUE;			// Show Cusor


//Window+Device관련 함수들
INT		Create(HINSTANCE hInst);
INT		Run();
void	Cleanup();
INT		Reset();

//게임 실행 관련 함수들
INT		Init();
void	Destroy();
INT		FrameMove();
INT		Render();

LRESULT MsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );
LRESULT WINAPI WndProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );



INT Create( HINSTANCE hInst)
{
	m_hInst	= hInst;
	strcpy(m_sCls, "2D Game App");

	WNDCLASS wc =								// Register the window class
	{
		CS_CLASSDC
		, WndProc
		, 0L
		, 0L
		, m_hInst
		, NULL
		, LoadCursor(NULL,IDC_ARROW)
		, (HBRUSH)GetStockObject(LTGRAY_BRUSH)
		, NULL
		, m_sCls
	};

	RegisterClass( &wc );

	RECT rc;									//Create the application's window

	SetRect( &rc, 0, 0, m_dScnX, m_dScnY);
	AdjustWindowRect( &rc, m_dWinStyle, FALSE);

	int iScnSysW = ::GetSystemMetrics(SM_CXSCREEN);
	int iScnSysH = ::GetSystemMetrics(SM_CYSCREEN);

	m_hWnd = CreateWindow( m_sCls
		, m_sCls
		, m_dWinStyle
		,	(iScnSysW - (rc.right-rc.left))/2
		,	(iScnSysH - (rc.bottom-rc.top))/2
		,	(rc.right-rc.left)
		,	(rc.bottom-rc.top)
		, GetDesktopWindow()
		, NULL
		, m_hInst
		, NULL );


	// D3D생성
	if( NULL == ( m_pD3D = Direct3DCreate9( D3D_SDK_VERSION ) ) )
		return -1;

	// D3D를 통해서 화면 모드를 찾는다.
	D3DDISPLAYMODE d3ddm;
    if( FAILED( m_pD3D->GetAdapterDisplayMode( D3DADAPTER_DEFAULT, &d3ddm ) ) )
        return -1;

	// 디바이스를 생성하기 위해서는 프리젠트 파라메터 구조체가 필요
	// 전부 0으로 셋팅한다음 일부만 변수세팅


	memset(&m_d3dpp, 0, sizeof m_d3dpp);
	m_d3dpp.Windowed = m_bWindow;
	m_d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	m_d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	m_d3dpp.BackBufferWidth = m_dScnX;
	m_d3dpp.BackBufferHeight = m_dScnY;
	m_d3dpp.EnableAutoDepthStencil = TRUE;
	m_d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	m_d3dpp.FullScreen_RefreshRateInHz = m_bWindow? 0 : d3ddm.RefreshRate;


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


	Init();

	ShowWindow( m_hWnd, SW_SHOW );
	UpdateWindow( m_hWnd );
	::ShowCursor(m_bShowCusor);

	return 0;
}


INT Reset()
{
	HRESULT hr;

	// D3D를 통해서 화면 모드를 찾는다.
	D3DDISPLAYMODE d3ddm;
	if( FAILED( m_pD3D->GetAdapterDisplayMode( D3DADAPTER_DEFAULT, &d3ddm ) ) )
		return -1;

	m_bWindow ^= 1;

	memset(&m_d3dpp, 0, sizeof m_d3dpp);
	m_d3dpp.Windowed = m_bWindow;
	m_d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	m_d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	m_d3dpp.BackBufferWidth = m_dScnX;
	m_d3dpp.BackBufferHeight = m_dScnY;
	m_d3dpp.EnableAutoDepthStencil = TRUE;
	m_d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	m_d3dpp.FullScreen_RefreshRateInHz = m_bWindow? 0 : d3ddm.RefreshRate;

	hr = m_pd3dDevice->Reset(&m_d3dpp);

	return 0;
}


void Cleanup()
{
	Destroy();

	// 디바이스를 릴리즈하기전에 먼저 스프라이트를 해제해야 한다.
	SAFE_RELEASE(	m_pd3dDevice	);
	SAFE_RELEASE(	m_pD3D			);

}


LRESULT MsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
	switch( msg )
	{
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

			return 0;

		}

		case WM_SYSCOMMAND:
			switch( wParam )
			{
			case SC_MOVE:
				break;
			case SC_SIZE:
				break;
			case SC_MAXIMIZE:
				Reset();
				break;
			case SC_KEYMENU:
				break;
			case SC_MONITORPOWER:
//				if( FALSE == m_bWindowed )
//					return 0;
				break;
			}
			break;

		case WM_DESTROY:
		{
			Cleanup();
			PostQuitMessage( 0 );
			return 0;
		}
	}

	return DefWindowProc( hWnd, msg, wParam, lParam );
}



INT Run()
{
	// Enter the message loop
	MSG msg;
	memset( &msg, 0, sizeof(msg) );

	while( msg.message!=WM_QUIT )
	{
		if( PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ) )
		{
			TranslateMessage( &msg );
			DispatchMessage( &msg );
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
						Reset();
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
				if(FAILED(FrameMove()))
					SendMessage(m_hWnd, WM_QUIT,0,0);

				if(FAILED(Render()))
					SendMessage(m_hWnd, WM_QUIT,0,0);
			}
		}
	}

	UnregisterClass( m_sCls, m_hInst);

	return 0;
}



INT Init()
{
	////////////////////////////////////////////////////////////////////////////
	//

	// 게임 데이터 생성

	//
	////////////////////////////////////////////////////////////////////////////

	return 0;
}

void Destroy()
{
	////////////////////////////////////////////////////////////////////////////
	//

	// 게임 데이터 해제

	//
	////////////////////////////////////////////////////////////////////////////
}

INT FrameMove()
{
	return 0;
}


INT Render()
{
	if( NULL == m_pd3dDevice )
		return -1;

	// 실질적으로는 버퍼(백버퍼: 색상, 깊이, 스텐실)를 지우는 것이 아니라 채우는 것이다.
	// D3DCLEAR_TARGET: 색상 버퍼를 지운다.
	// D3DCLEAR_ZBUFFER: 깊이 버퍼를 지운다.
	// Clear에서 D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER 설정은 가장 흔한 방법이다.
	m_pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0,120,160), 1.0f, 0 );


	// BeginScene과 EndScene에 렌더링을 걸어주어야 된다.
	if( FAILED( m_pd3dDevice->BeginScene() ) )
		return -1;

	////////////////////////////////////////////////////////////////////////////
	//

	// 렌더링

	//
	////////////////////////////////////////////////////////////////////////////


	// EndScene
	m_pd3dDevice->EndScene();

	// 후면버퍼 전면버퍼 교체( flipping)
	HRESULT hr= m_pd3dDevice->Present( NULL, NULL, NULL, NULL);


	// 이 경우는 전체화면상태에서 다른 윈도우가 활성화 될 때(예를들어
	// ALT+TAB키, CTRL+ESC키 동작시) 필요하다.
	// 이 과정을 거쳐야만 계속해서 디바이스를 사용할 수 있다.
	// 일단 로스트 상태로 둔다.
	if( D3DERR_DEVICELOST == hr )
		m_bDeviceLost = TRUE;


	return 0;
}



LRESULT WINAPI WndProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
	return MsgProc(hWnd, msg, wParam, lParam);
}



INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR, INT )
{
	if(FAILED(Create(hInst)))
		return -1;

	return Run();
}