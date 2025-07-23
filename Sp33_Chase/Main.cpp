// Implementation of the CMain class.
//
////////////////////////////////////////////////////////////////////////////////


#include "_StdAfx.h"


CMain::CMain()
{
	m_pLcSprite	= NULL;
	m_pInput	= NULL;
	

	m_pTex1		= NULL;
	m_pTex2		= NULL;
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

	m_pTex2	= new CLcTexture;
	if( FAILED(m_pTex2->Create(m_pd3dDevice, "Texture/B.png")))
		return -1;	


	m_PrjEnd.SetPosCur(D3DXVECTOR2(750,335));
	m_PrjBgn.SetPosTar(m_PrjEnd.GetPosCur());

	SetWindowText(m_hWnd, "Try to press Mouse L Button");

	return 0;
}

void CMain::Destroy()
{
	SAFE_DELETE(	m_pLcSprite	);
	SAFE_DELETE(	m_pInput	);

	SAFE_DELETE(	m_pTex1		);
	SAFE_DELETE(	m_pTex2		);
}


INT CMain::FrameMove()
{
	if(m_pInput)
		m_pInput->FrameMove();




	if(m_pInput->BtnPress(0))
	{
		D3DXVECTOR3	vcMouse = m_pInput->GetMousePos();
		
		m_PrjEnd.vcC.x = vcMouse.x;
		m_PrjEnd.vcC.y = vcMouse.y;
	}

	m_PrjBgn.SetPosTar(m_PrjEnd.GetPosCur());

	if(SUCCEEDED(m_PrjBgn.FrameMove()))
	{
		m_PrjBgn.ResetSpd();
	}
	else
	{
	}

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
						, &m_PrjBgn.GetPosCur()
						, D3DXCOLOR(1,1,1,1)
						);


	m_pTex2->GetImageRect(&rc);
	m_pLcSprite->Draw(   m_pTex2->GetTexture()
						, &rc
						, NULL
						, NULL
						, 0
						, &m_PrjEnd.GetPosCur()
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