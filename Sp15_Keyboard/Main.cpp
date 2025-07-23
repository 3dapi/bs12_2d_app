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
	m_pInput = new CLcInput;

	return 0;
}

void CMain::Destroy()
{
	SAFE_DELETE(	m_pInput	);
}




INT CMain::Restore()
{
	return 0;
}


void CMain::Invalidate()
{
}


INT CMain::FrameMove()
{
	if(m_pInput)
		m_pInput->FrameMove();

	return 0;
}


INT CMain::Render()
{
	m_pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER, 0xFF006699, 1.0f, 0 );

	if( FAILED( m_pd3dDevice->BeginScene() ) )
		return -1;



	TCHAR	sMsg[128];
	INT		i;

	sprintf(sMsg, "Keboard Test. Try to Press Ani Key");


	for(i=0; i<256; ++i)
	{
		if( m_pInput->KeyDown(i))
		{
			sprintf(sMsg, "key Downed: %c(%d)", i, i);
		}
	}

	for(i=0; i<256; ++i)
	{
		if( m_pInput->KeyPress(i))
		{
			sprintf(sMsg, "key Pressed: %c(%d)", i, i);
		}
	}

	for(i=0; i<256; ++i)
	{
		if( m_pInput->KeyUp(i))
		{
			sprintf(sMsg, "key Up:  %c(%d)", i, i);
		}
	}

	SetWindowText(m_hWnd, sMsg);


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