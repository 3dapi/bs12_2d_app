//
////////////////////////////////////////////////////////////////////////////////


#pragma warning( disable : 4996)


#include <vector>
using namespace std;

#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>

#include "GameTexture.h"
#include "GameModel.h"



class CGameModel2D : public IGameModel
{
public:

	struct TAniInfo
	{
		DWORD	dTime;				// RECT 애니 이미지
		RECT	ImgRc;				// RECT 애니 이미지

		TAniInfo(){};
		TAniInfo(DWORD v1, RECT v2)
		{
			dTime = v1;
			ImgRc = v2;
		}
	};

	typedef std::vector<TAniInfo >	lsAniInfo;
	typedef lsAniInfo::iterator		itAniInfo;


protected:
	char				m_sName[MAX_PATH];

	INT					m_bAni;				// Animation or Not
	DWORD				m_dTimeDelta;		// 시간 간격
	DWORD				m_dTimeBgn;			// 시작 타임
	DWORD				m_dTimeCur;			// 현재 타임

	INT					m_nAniTot;			// Ani Total Number
	INT					m_nAniCur;			// Current Ani Index

	IGameTexture*			m_pTex	;		// 애니 텍스처
	std::vector<TAniInfo >	m_vAni	;

	LPD3DXSPRITE		m_pSprite	;		// for Render
	RECT				m_ImgRc		;		// for Render

	D3DXVECTOR3			m_vcPos		;
	DWORD				m_dColor	;

public:
	CGameModel2D();
	virtual ~CGameModel2D();

	virtual int		Create(void* pSprite, void* ModelName);
	virtual void	Destroy();

	virtual int		FrameMove();
	virtual void	Render();
	

	virtual void	SetAnimation(int);
	virtual int		GetAnimation();

	virtual void	Play();
	virtual void	Stop();


	virtual	void	SetPos(const FLOAT* pPos);
	virtual	void	SetColor(const DWORD);
};


CGameModel2D::CGameModel2D()
{
	m_pSprite		= NULL;

	m_bAni			= 0;
	m_dTimeDelta	= 0;
	m_dTimeBgn		= timeGetTime();
	m_dTimeCur		= m_dTimeBgn;

	m_nAniTot		= 0;
	m_nAniCur		= 0;

	m_pTex			= NULL;

	memset(&m_sName, 0, sizeof m_sName);

	m_vcPos		= D3DXVECTOR3(0,0,0);
	m_dColor	= 0xFFFFFFFF;
}


CGameModel2D::~CGameModel2D()
{
	Destroy();
}


void CGameModel2D::Destroy()
{
	if(m_pTex)
	{
		delete m_pTex;
		m_pTex = NULL;
	}

	m_vAni.clear();
}


void CGameModel2D::SetAnimation(int nAniIdx)
{
	m_nAniCur = nAniIdx;
}

int CGameModel2D::GetAnimation()
{
	return m_nAniCur;
}

void CGameModel2D::Play()
{
	m_bAni = TRUE;
}

void CGameModel2D::Stop()
{
	m_bAni = FALSE;
}


void CGameModel2D::SetPos(const FLOAT* pPos)
{
	memcpy(&m_vcPos, pPos, sizeof(D3DXVECTOR3));
}


void CGameModel2D::SetColor(DWORD dColor)
{
	m_dColor = dColor;
}


int CGameModel2D::Create(void* pSprite, void* ModelName)
{
	m_pSprite = (LPD3DXSPRITE)pSprite;
	
	strcpy(m_sName, (char*)ModelName);


	char	sLine[512]={0};

	FILE* fp = fopen(m_sName, "rt");

	if(NULL == fp)
		return -1;

	char	sTexFile[MAX_PATH]={0};
	DWORD	dColorKey=0;
	fgets(sLine, 512, fp);
	sscanf(sLine, "%*s %s %x", sTexFile, &dColorKey);
	

	fgets(sLine, 512, fp);
	sscanf(sLine, "%*s %d", &m_nAniTot);

	fgets(sLine, 512, fp);
	sscanf(sLine, "%*s %ld", &m_dTimeDelta);

	int nCnt = 0;

	while(!feof(fp))
	{
		DWORD	dTime;
		RECT	rc;
		fgets(sLine, 512, fp);

		if(strlen(sLine)>5)
		{
			sscanf(sLine, "%ld "
						"%ld %ld %ld %ld"
						, &dTime
						, &rc.left, &rc.top, &rc.right, &rc.bottom);

			m_vAni.push_back( CGameModel2D::TAniInfo(dTime, rc) );

			++nCnt;

			if(nCnt>=m_nAniTot)
				break;
		}
	}

	fclose(fp);


	if(FAILED(LpDev_TextureCreate(IGameTexture::FILE, &m_pTex, sTexFile, dColorKey)))
		return -1;
	

	return 0;
}


int CGameModel2D::FrameMove()
{
	BOOL	nFind = -1;

	DWORD	dDelta =0;

	m_dTimeCur	= timeGetTime();

	dDelta = m_dTimeCur- m_dTimeBgn;

	for(int i=0; i<m_nAniTot; ++i)
	{
		if( m_vAni[i].dTime<=dDelta && dDelta < (m_vAni[i].dTime+ m_dTimeDelta))
		{
			nFind = i;
			break;
		}
	}

	if(-1 == nFind)
	{
		m_dTimeBgn = m_dTimeCur;
		nFind = 0;
	}

	m_nAniCur = nFind;

	m_ImgRc = m_vAni[m_nAniCur].ImgRc;

	return 0;
}


void CGameModel2D::Render()
{
	LPDIRECT3DTEXTURE9	pTex = (LPDIRECT3DTEXTURE9)m_pTex->GetTexture();

	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
	m_pSprite->Draw(pTex, &m_ImgRc, NULL, &m_vcPos, m_dColor);
	m_pSprite->End();
}



int LpDev_ModelCreate(int nOpt, IGameModel** pData, void* pSprite, void* pModelName)
{
	*pData = NULL;

	CGameModel2D* pObj = new CGameModel2D;

	if(FAILED(pObj->Create(pSprite, pModelName)))
	{
		delete pObj;
		return -1;
	}

	*pData = pObj;
	return 0;
}



