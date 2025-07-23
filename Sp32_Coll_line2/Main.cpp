// Implementation of the CMain class.
//
////////////////////////////////////////////////////////////////////////////////


#include "_StdAfx.h"


int CollisionLineToLine(const D3DXVECTOR2* v1, const D3DXVECTOR2* v2)
{
//	D3DXVECTOR2 L0 = v2[0] - v1[0];
//	D3DXVECTOR2 L1 = v1[1] - v1[0];
//	D3DXVECTOR2 L2 = v2[1] - v1[0];
//
//	D3DXVECTOR2 L3 = v1[0] - v2[0];
//	D3DXVECTOR2 L4 = v2[1] - v2[0];
//	D3DXVECTOR2 L5 = v1[1] - v2[0];
//
//	FLOAT	D1;
//	FLOAT	D2;
//
//	//D1 = (L0 ^ L1 * L1 ^ L2);
//	//D2 = (L3 ^ L4 * L4 ^ L5);
//
//	D1 = (L0.x * L1.y - L0.y * L1.x) * (L1.x * L2.y - L1.y * L2.x);
//	D2 = (L3.x * L4.y - L3.y * L4.x) * (L4.x * L5.y - L4.y * L5.x);
//
//	if(  D1>0 && D2 >0)
//		return 0;
	
	
	D3DXVECTOR2 L0 = v2[0] - v1[0];
	D3DXVECTOR2 L1 = v1[1] - v1[0];
	D3DXVECTOR2 L2 = v2[1] - v1[0];

	D3DXVECTOR2 L4 = v2[0] - v2[1];
	D3DXVECTOR2 L5 = v2[0] - v1[1];

	FLOAT	D1 = (L0.x * L1.y - L0.y * L1.x) * (L1.x * L2.y - L1.y * L2.x);
	FLOAT	D2 = (L0.x * L4.y - L0.y * L4.x) * (L4.x * L5.y - L4.y * L5.x);

	if(D1>0 && D2 >0)
		return 0;

	return -1;
}


CMain::CMain()
{
	m_pLcSprite	= NULL;
	m_pInput	= NULL;


	m_pLine		= NULL;
}


INT CMain::Init()
{
	m_pLcSprite = new CLcSprite;
	if(FAILED(m_pLcSprite->Create(m_pd3dSprite)))
		return -1;

	m_pInput = new CLcInput;
	if( FAILED(m_pInput->Create(m_hWnd)))
		return -1;


	D3DXCreateLine(m_pd3dDevice, &m_pLine);
	m_pLine->SetWidth(15);


	// Line 1
	m_pLine1[0]	= D3DXVECTOR2(150, 30);
	m_pLine1[1] = m_pLine1[0] + 200 * D3DXVECTOR2(2,1);

	// Line 2
	m_pLine2[0]	= D3DXVECTOR2(650,190);
	m_pLine2[1] = m_pLine2[0] + 200 * D3DXVECTOR2(-2,1);

	return 0;
}

void CMain::Destroy()
{
	SAFE_RELEASE(	m_pLine		);

	SAFE_DELETE(	m_pLcSprite	);
	SAFE_DELETE(	m_pInput	);
}


INT CMain::FrameMove()
{
	if(m_pInput)
		m_pInput->FrameMove();




	D3DXVECTOR2	TempPos = m_pLine1[0];

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


	m_pLine1[0] = TempPos;
	m_pLine1[1] = m_pLine1[0] + 210 * D3DXVECTOR2(1,1);
	


	int hr = CollisionLineToLine(m_pLine1, m_pLine2);


	if(SUCCEEDED(hr))
		SetWindowText(m_hWnd, "Collision to Line");
	else
		SetWindowText(m_hWnd, " ");


	return 0;
}


INT CMain::Render()
{
	m_pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER, 0xFFaaEEFF, 1.0f, 0 );

	if( FAILED( m_pd3dDevice->BeginScene() ) )
		return -1;


	m_pLine->Begin();

	m_pLine->Draw(m_pLine2, 2, 0xFFFF00FF);
	m_pLine->Draw(m_pLine1, 2, 0xFFFF8800);


	m_pLine->End();

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