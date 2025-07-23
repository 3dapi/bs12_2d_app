// Implementation of the CMain class.
//
////////////////////////////////////////////////////////////////////////////////


#include "_StdAfx.h"


int CollisionLineToLine(const D3DXVECTOR2* v1, const D3DXVECTOR2* v2)
{
	//A: v1[0] B: v1[1]
	//C: v2[0] D: v2[1]

	D3DXVECTOR2    CA = v2[0] - v1[0];		// C - A
	D3DXVECTOR2    BA = v1[1] - v1[0];		// B - A
	D3DXVECTOR2    DA = v2[1] - v1[0];		// D - A

	//D3DXVECTOR2  AC = v1[0] - v2[0];
	D3DXVECTOR2    CD = v2[0] - v2[1];		// C - D = -DC
	D3DXVECTOR2    CB = v2[0] - v1[1];		// C - B = -BC
	D3DXVECTOR2    BD = v1[1] - v2[1];		// B - D = -DB
	//D3DXVECTOR2  DB = -BD;


	if( 0 < (CA.x * BA.y - CA.y * BA.x) * (BA.x * DA.y - BA.y * DA.x) && //  (AC X AB) ·(AB X AD)  = (CA X BA) ·(BA X DA) 
		0 < (CA.x * CD.y - CA.y * CD.x) * (CD.x * CB.y - CD.y * CB.x) )  //  (CA X CD)  ·(CD X CB)	
		return 0;		//충돌


	if( 0 == BA.x * CD.y - BA.y * CD.x  &&	// AB X CD  =0
		0 == CA.x * CD.y - CA.y * CD.x  )	// AC X CD = 0
	{

		if( 0 > D3DXVec2Dot(&CA, &DA) ||	// CA ·DA
			0 < D3DXVec2Dot(&CB, &BD) ||	// CB ·DB = -CB ·BD
			0 > D3DXVec2Dot(&CA, &CB) ||	// AC ·BC =  CA ·CB
			0 < D3DXVec2Dot(&DA, &BD)		// AD ·BD = -DA ·BD
			)
		return 0;		//충돌
	
	}

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
	m_pLine1[0]	= D3DXVECTOR2(50, 90);
	m_pLine1[2] = D3DXVECTOR2(1,1.3F) * 150;
	m_pLine1[1] = m_pLine1[0] + m_pLine1[2];

	// Line 2
	m_pLine2[0]	= m_pLine1[1] - m_pLine1[2]*0.1F;
	m_pLine2[2] = D3DXVECTOR2(1, -1.1F) * 200;
	m_pLine2[1] = m_pLine2[0] + m_pLine2[2];

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
	m_pLine1[1] = m_pLine1[0] + m_pLine1[2];


	int hr = CollisionLineToLine(m_pLine2, m_pLine1);


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