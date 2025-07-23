// Implementation of the CMain class.
//
////////////////////////////////////////////////////////////////////////////////


#include "_StdAfx.h"

int			m_Pull = 0;

D3DXVECTOR2	m_vcP(20,200);

FLOAT		m_vcV = 0;
FLOAT		m_vcA = 0;
FLOAT		m_vcBgn = 0;
FLOAT		m_vcOld = 0;
FLOAT		m_vcCur = 0;
FLOAT		m_vcEnd = 0;

DOUBLE		m_dTimeBgn = timeGetTime();
DOUBLE		m_dTimeCur = m_dTimeBgn;


CMain::CMain()
{
	m_pLcSprite	= NULL;
	m_pInput	= NULL;
	m_pTex1		= NULL;
}


INT CMain::Init()
{
	m_pLcSprite = new CLcSprite;
	if(FAILED(m_pLcSprite->Create(m_pd3dSprite)))
		return -1;

	m_pInput = new CLcInput;
	if( FAILED(m_pInput->Create(m_hWnd)))
		return -1;



	
	m_pTex1	= new CLcTexture;
	if( FAILED(m_pTex1->Create(m_pd3dDevice, "Texture/A.png")))
		return -1;

	return 0;
}

void CMain::Destroy()
{
	SAFE_DELETE(	m_pLcSprite	);
	SAFE_DELETE(	m_pInput	);

	SAFE_DELETE(	m_pTex1		);
}


INT CMain::FrameMove()
{
	if(m_pInput)
		m_pInput->FrameMove();


//	if(m_pInput->BtnDown(0))
//	{
//		D3DXVECTOR3 vcPos = m_pInput->GetMousePos();
//
//		m_vcBgn = vcPos.x;
//		m_vcCur = m_vcBgn;
//		m_vcOld = m_vcCur;
//
//		m_Pull = 1;
//	}
//
//	if(m_pInput->BtnPress(0))
//	{
//		D3DXVECTOR3 vcPos = m_pInput->GetMousePos();
//
//		m_vcBgn = vcPos.x;
//		m_vcCur = m_vcBgn;
//
//		m_Pull = 1;
//	}
//
//
//	if(m_pInput->BtnUp(0))
//	{
//		D3DXVECTOR3 vcPos = m_pInput->GetMousePos();
//		m_vcCur = vcPos.x;
//
//		m_vcV = m_vcCur - m_vcBgn;
//
//		m_vcBgn = m_vcCur;
//
//		printf("Vel:%f Pos:%.f %.f \n", m_vcV, m_vcP.x, m_vcP.y);
//
//		m_Pull = 2;
//
//		m_dTimeBgn  = timeGetTime();
//		m_dTimeCur  = m_dTimeBgn;
//	}
//
//
//	if(1 == m_Pull)
//	{
//		FLOAT  DELTA = m_vcCur- m_vcOld;
//
//		m_vcP.x += DELTA;
//
//		m_vcOld = m_vcCur;
//	}
//	else if (2 == m_Pull)
//	{ 
//		m_dTimeCur  = timeGetTime();
//
//		DOUBLE TimeDelta = m_dTimeCur - m_dTimeBgn;
//		m_dTimeBgn = m_dTimeCur;
//
//		TimeDelta *=0.001F;
//
//		printf("Vel:%f \n", TimeDelta);
//
//
//		float lensq = m_vcV * m_vcV;
//
//		if(lensq <0.1)
//		{
//			m_vcV = 0;
//			m_Pull = 0;
//		}
//		
//		m_vcV *= (1 - 1.1F * TimeDelta);
//		m_vcP.x += m_vcV * TimeDelta;
//	}



	if(m_pInput->BtnDown(0))
	{
		D3DXVECTOR3 vcPos = m_pInput->GetMousePos();

		m_vcBgn = vcPos.x;
		m_vcCur = m_vcBgn;
		m_vcOld = m_vcCur;

		m_Pull = 1;
	}

	if(m_pInput->BtnPress(0))
	{
		D3DXVECTOR3 vcPos = m_pInput->GetMousePos();

		m_vcBgn = vcPos.x;
		m_vcCur = m_vcBgn;

		m_vcV  = 0;
		m_Pull = 2;
	}

	if(m_pInput->BtnUp(0))
	{
		D3DXVECTOR3 vcPos = m_pInput->GetMousePos();

		m_vcCur = vcPos.x;
		m_vcV = m_vcCur - m_vcBgn;
		m_vcV *= 0.3F;

		m_Pull = 2;
	}



	if(1 == m_Pull)
	{
		FLOAT  DELTA = m_vcCur- m_vcOld;

		m_vcP.x += DELTA;

		m_vcOld = m_vcCur;
	}

	if(2 == m_Pull)
	{
		m_dTimeCur  = timeGetTime();
		DOUBLE TimeDelta = m_dTimeCur - m_dTimeBgn;
		m_dTimeBgn = m_dTimeCur;

		float lensq = m_vcV * m_vcV;

		if(lensq < 0.1F)
		{
			m_Pull = 0;
			m_vcV = 0;
		}


		m_vcV *= (1 - 0.01F * TimeDelta);
		m_vcP.x += m_vcV * TimeDelta;
	}

	if(m_vcP.x>1024)
			m_vcP.x -= 1024;

	if(m_vcP.x<-120)
			m_vcP.x  = 1024;

	return 0;
}


INT CMain::Render()
{
	m_pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0,120,160), 1.0f, 0 );

	if( FAILED( m_pd3dDevice->BeginScene() ) )
		return -1;


	RECT	rc;

	m_pTex1->GetImageRect(&rc);
	m_pLcSprite->Draw(   m_pTex1->GetTexture()
						, &rc
						, NULL
						, NULL
						, 0
						, &m_vcP
						, D3DXCOLOR(1,1,1,1)
						);




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


