// LcTexture.cpp: implementation of the CLcTexture class.
//
//////////////////////////////////////////////////////////////////////

#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>


#include "LcTexture.h"


CLcTexture::CLcTexture()
{
	m_pDev	= NULL;

	m_pTx	= NULL;
	memset(&m_Img, 0, sizeof m_Img);
}

CLcTexture::~CLcTexture()
{
	Destroy();
}


void CLcTexture::Destroy()
{
	if(m_pTx)
	{
		m_pTx->Release();
		m_pTx= NULL;
	}
}


INT CLcTexture::Create(LPDIRECT3DDEVICE9 pDev, char* sFile, DWORD	dRsc)
{
	m_pDev	= pDev;

	DWORD	dColorKey	= 0x00FFFFFF;

	if(sFile && strlen(sFile)>6)
	{
		dColorKey	= dRsc;
		if(FAILED(D3DXCreateTextureFromFileEx(
			m_pDev
			, sFile
			, D3DX_DEFAULT
			, D3DX_DEFAULT
			, 1
			, 0
			, D3DFMT_UNKNOWN
			, D3DPOOL_MANAGED
			, D3DX_FILTER_NONE
			, D3DX_FILTER_NONE
			, dColorKey
			, &m_Img
			, NULL
			, &m_pTx
			)) )
		{
			m_pTx = NULL;
			MessageBox( GetActiveWindow()
						, "Create Texture Failed"
						, "Err"
						, MB_ICONEXCLAMATION
						);
			return -1;
		}
	}
	
	else if(dRsc)
	{
		HINSTANCE	hInst	= GetModuleHandle(NULL);
		HRSRC		hrsc	= FindResource(hInst, MAKEINTRESOURCE( dRsc ), "png");
		HGLOBAL		hglobal = LoadResource(hInst, hrsc);
		DWORD		dwSize	= SizeofResource(hInst,hrsc);
		void*		pMemory = LockResource(hglobal);

		if(FAILED(D3DXCreateTextureFromFileInMemoryEx(
			m_pDev
			, pMemory
			, dwSize
			, D3DX_DEFAULT
			, D3DX_DEFAULT
			, 1
			, 0
			, D3DFMT_UNKNOWN
			, D3DPOOL_MANAGED
			, D3DX_FILTER_NONE
			, D3DX_FILTER_NONE
			, dColorKey
			, &m_Img
			, NULL
			, &m_pTx
			)) )
		{
			m_pTx = NULL;
			MessageBox( GetActiveWindow()
						, "Create Texture Failed"
						, "Err"
						, MB_ICONEXCLAMATION
						);
			return -1;
		}

		UnlockResource(hglobal);
		FreeResource(hglobal);
	}


	return 0;
}



INT CLcTexture::GetImageWidth()
{
	return m_Img.Width;
}


INT CLcTexture::GetImageHeight()
{
	return m_Img.Height;
}

void CLcTexture::GetImageRect(RECT* pRc)
{
	pRc->left	= 0;
	pRc->top	= 0;
	pRc->right	= m_Img.Width;
	pRc->bottom	= m_Img.Height;
}

LPDIRECT3DTEXTURE9 CLcTexture::GetTexture()
{
	return m_pTx;
}