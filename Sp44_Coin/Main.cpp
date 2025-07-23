// Implementation of the CMain class.
//
////////////////////////////////////////////////////////////////////////////////


#include "_StdAfx.h"


CMain::CMain()
{
	m_pTxBck	= NULL;
	m_pCoin		= NULL;
}


INT CMain::Init()
{
	D3DXFONT_DESC hFont =
	{
		14, 0, FW_BOLD, 1, FALSE
		, HANGUL_CHARSET
		, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FF_DONTCARE
		, "굴림체"
	};

	D3DXCreateFontIndirect(GDEVICE, &hFont, &m_pD3DXFont);


	if( FAILED( McUtil_TextureLoad(GDEVICE, "Texture/Background.png", m_pTxBck, &m_ImgBck, 0x00FFFFFF)))
		return -1;


	SetRect(&m_ImgRcB, 0,0, m_ImgBck.Width, m_ImgBck.Height);


	m_iCnt	= 6;
	m_pCoin = new CMcCoin[m_iCnt];

	for(int i=0; i<m_iCnt; ++i)
	{
		m_pCoin[i].Init();
	}


	return 0;
}

void CMain::Destroy()
{
	SAFE_DELETE_ARRAY(	m_pCoin		);

	SAFE_RELEASE(	m_pD3DXFont	);

	// 디바이스 해제 이전에 텍스처를 해제
	SAFE_RELEASE(	m_pTxBck	);
}


INT CMain::FrameMove()
{
	static CHAR bResetOld = 0;
	static CHAR bResetCur = 0;

	bResetOld = bResetCur;

	bResetCur = 0;

	if(GetAsyncKeyState('R') & 0x8000)
	{
		bResetCur = 1;
	}

	if(0== bResetOld && 1==bResetCur)
	{
		for(int i=0; i<m_iCnt; ++i)
		{
			m_pCoin[i].Set();
		}
	}


	for(int i=0; i<m_iCnt; ++i)
	{
		m_pCoin[i].FrameMove();
	}

	return 0;
}


INT CMain::Render()
{
	m_pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER, 0xFF006699, 1.0f, 0 );

	if( FAILED( m_pd3dDevice->BeginScene() ) )
		return -1;


	m_pd3dSprite->Begin(D3DXSPRITE_ALPHABLEND);

	m_pd3dSprite->Draw(m_pTxBck, &m_ImgRcB, NULL, NULL, D3DXCOLOR(1,1,1,1));

	for(INT i=0; i<m_iCnt; ++i)
	{
		m_pCoin[i].Render();
	}


	m_pd3dSprite->End();




	RECT	rt	= { 10, 10, m_dScnX-10, 50};
	m_pD3DXFont->DrawText(NULL, "Animation Texture..", -1, &rt, 0, D3DXCOLOR(1,1,0,1));


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