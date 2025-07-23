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


	m_ObjPos1	= D3DXVECTOR2(150, 30);			// Object 1 Position
	m_ObjPos2	= D3DXVECTOR2(400,300);			// Object 2 Position

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




	D3DXVECTOR2	TempPos = m_ObjPos1;

	if(m_pInput->KeyPress(VK_RIGHT))
	{
		TempPos.x += 0.25f;
	}

	if(m_pInput->KeyPress(VK_LEFT))
	{
		TempPos.x -= 0.25f;
	}

	if(m_pInput->KeyPress(VK_UP))
	{
		TempPos.y -= 0.25f;
	}

	if(m_pInput->KeyPress(VK_DOWN))
	{
		TempPos.y += 0.25f;
	}

	RECT rcCol1;
	RECT rcCol2;

	SetRect(&rcCol1 , INT(TempPos.x)
					, INT(TempPos.y)
					, INT(TempPos.x) + m_pTex1->GetImageWidth()
					, INT(TempPos.y) + m_pTex1->GetImageHeight()
			);

	SetRect(&rcCol2 , INT(m_ObjPos2.x)
					, INT(m_ObjPos2.y)
					, INT(m_ObjPos2.x) + m_pTex2->GetImageWidth()
					, INT(m_ObjPos2.y) + m_pTex2->GetImageHeight()
			);


	INT bColl=0;

	if( rcCol1.left <= rcCol2.right &&
		rcCol1.right>= rcCol2.left  &&

		rcCol1.top   <= rcCol2.bottom &&
		rcCol1.bottom >= rcCol2.top )
	{
		bColl =1;
		SetWindowText(m_hWnd, "Collision");
	}


	if(0==bColl)
	{
		SetWindowText(m_hWnd, "Press Left, Right, Up, Down Key!");
		m_ObjPos1 = TempPos;
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
						, &m_ObjPos1
						, D3DXCOLOR(1,1,1,1)
						);


	m_pTex2->GetImageRect(&rc);
	m_pLcSprite->Draw(   m_pTex2->GetTexture()
						, &rc
						, NULL
						, NULL
						, 0
						, &m_ObjPos2
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