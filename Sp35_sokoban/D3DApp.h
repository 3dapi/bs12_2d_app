﻿// Interface for the CD3DApplication class.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef _D3DAPP_H_
#define _D3DAPP_H_

class CD3DApplication
{
protected:
	HINSTANCE	m_hInst		;													// Window Instance
	CHAR		m_sCls[128]	;													// Window Class Name
	CHAR		m_sWin[128]	;													// Window Title
	HWND		m_hWnd		;													// Main Window Handle
	DWORD		m_dWinStyle	;													// Window Style
	DWORD		m_dScnX		;													// Screen Width
	DWORD		m_dScnY		;													// Screen Height
	BOOL		m_bShowCusor;													// Show Cusor

protected:
	LPDIRECT3D9				m_pD3D		;			// 1. Direct3D
	LPDIRECT3DDEVICE9		m_pd3dDevice;			// 2. Direct3D Device
	D3DPRESENT_PARAMETERS	m_d3dpp		;			// 3. D3D Present Parameters
	LPD3DXSPRITE			m_pd3dSprite;			// 4. 2D Sprite
	BOOL					m_bWindow	;			// 5. Window Mode?

public:
	CD3DApplication();
	virtual ~CD3DApplication();

	//Window+Device관련 함수들
	INT		Create(HINSTANCE hInst);											// Window 생성
	INT		Run();																// Winodw Main Loop 함수
	void	Cleanup();															// 윈도우 해제 함수
	virtual	LRESULT MsgProc( HWND, UINT, WPARAM, LPARAM);						// 윈도우 메시지 처리함수
	static	LRESULT WINAPI WndProc(HWND, UINT, WPARAM, LPARAM);					// Window Message Procedure function

public:
	virtual	HRESULT	Init();														// Game Data 생성
	virtual	HRESULT	Destroy();													// Game Data 소멸
	virtual	HRESULT	FrameMove();												// Game Data 갱신
	virtual	HRESULT	Render();													// Game Data 그리기

public:																			// Application
	HINSTANCE			GetInstance(){	return	m_hInst		;	}
	HWND				GetHwnd()	{	return m_hWnd		;	}
	DWORD				GetScnW()	{	return m_dScnX		;	}
	DWORD				GetScnH()	{	return m_dScnY		;	}
	
	LPDIRECT3DDEVICE9	GetDevice()	{	return m_pd3dDevice	;	}
	LPD3DXSPRITE		GetSprite()	{	return m_pd3dSprite	;	}
};


#endif