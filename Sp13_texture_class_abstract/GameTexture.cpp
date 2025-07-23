

#pragma warning( disable : 4996)


#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>

#include "GameTexture.h"



class CGameTexture: public IGameTexture
{
protected:
	char				m_sName[MAX_PATH];
	D3DXIMAGE_INFO		m_Img;
	LPDIRECT3DTEXTURE9	m_pTx;

public:
	CGameTexture();
	virtual ~CGameTexture();

	virtual int		Create(void* TextureName, DWORD dColorKey);
	virtual void	Destroy();

	virtual int		GetImageWidth();
	virtual int		GetImageHeight();
	virtual void*	GetTexture();

	virtual const char*	GetName();


	static LPDIRECT3DDEVICE9 m_pDevice;
};



LPDIRECT3DDEVICE9 CGameTexture::m_pDevice = NULL;

void LpDev_TextureInit(void* pDev)
{
	CGameTexture::m_pDevice = (LPDIRECT3DDEVICE9)pDev;
}



CGameTexture::CGameTexture()
{
	memset(&m_sName, 0, sizeof m_sName);
	memset(&m_Img, 0, sizeof m_Img);

	m_pTx = NULL;
}

CGameTexture::~CGameTexture()
{
	Destroy();
}


void CGameTexture::Destroy()
{
	if(m_pTx)
	{
		m_pTx->Release();
		m_pTx = NULL;
	}

	memset(&m_sName, 0, sizeof m_sName);
	memset(&m_Img, 0, sizeof m_Img);
}


int CGameTexture::GetImageWidth()
{
	return m_Img.Width;
}

int CGameTexture::GetImageHeight()
{
	return m_Img.Height;
}

void*  CGameTexture::GetTexture()
{
	return m_pTx;
}


const char* CGameTexture::GetName()
{
	return m_sName;
}


int CGameTexture::Create(void* TextureName, DWORD dColorKey)
{
	strcpy(m_sName, (char*)TextureName);


	if( FAILED( D3DXCreateTextureFromFileEx(
						CGameTexture::m_pDevice		// 디바이스 포인터
						, m_sName					// 텍스처 이름
						, D3DX_DEFAULT
						, D3DX_DEFAULT
						, 1							// 밉 레벨(2D의 경우 반드시 1)
						, 0
						, D3DFMT_UNKNOWN
						, D3DPOOL_MANAGED
						, 0x0000001					// 필터링
						, 0x0000001					// 밉 필터
						, dColorKey					// 컬러 키
						, &m_Img					// 텍스처 인포메이션
						, NULL
						, &m_pTx					// 텍스처 포인터
						)) )
	{
		memset(&m_sName, 0, sizeof m_sName);
		m_pTx = NULL;
		return -1;
	}

	return 0;
}


int LpDev_TextureCreate(int nOpt, IGameTexture** pData, void* pTextureName, DWORD dColorKey)
{
	*pData = NULL;

	CGameTexture* pObj = new CGameTexture;

	if(FAILED(pObj->Create(pTextureName, dColorKey)))
	{
		delete pObj;
		return -1;
	}

	*pData = pObj;
	return 0;
}