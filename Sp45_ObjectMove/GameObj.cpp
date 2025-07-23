// GameObj.cpp: implementation of the CGameObj class.
//
//////////////////////////////////////////////////////////////////////

#include "_StdAfx.h"


CGameObj::CGameObj()
{

}

CGameObj::~CGameObj()
{
	Destroy();
}


INT CGameObj::Create(LPDIRECT3DDEVICE9 pDevice, LPD3DXSPRITE pSprite)
{
	m_pDevice = pDevice;
	m_pSprite = pSprite;

	if(FAILED(D3DXCreateTextureFromFileEx(
			m_pDevice
			, "Texture/mario_all.png"
			, D3DX_DEFAULT
			, D3DX_DEFAULT
			, 1
			, 0
			, D3DFMT_UNKNOWN
			, D3DPOOL_MANAGED
			, D3DX_FILTER_NONE
			, D3DX_FILTER_NONE
			, 0x00FFFFFF
			, &m_pImg
			, NULL
			, &m_pTex
			)) )
	{
		return -1;
	}

	m_vcPos = D3DXVECTOR3(50, 362, 0);
	m_fSpeed = .2f;
	m_vcDir   = D3DXVECTOR3(0, 0, 0);
	m_nDir	=0;


	m_dBgn	= GetTickCount();
	m_dCur	= m_dBgn;
	m_dIntr	= 70;
	m_nBgnX = 0;
	m_nBgnY = 0;

	m_nCur	= 0 ;
	m_nTot	= 4 ;

	return 0;
}

void CGameObj::Destroy()
{
}

INT CGameObj::FrameMove()
{
	FLOAT	fTime = g_pApp->GetAvgTime();

	static D3DXVECTOR3	vcDir[9]=
	{
		D3DXVECTOR3( 0.000F, 0.000F, 0),
		D3DXVECTOR3( 1.000F, 0.000F, 0),
		D3DXVECTOR3( 0.707F,-0.707F, 0),
		D3DXVECTOR3( 0.000F,-1.000F, 0),
		D3DXVECTOR3(-0.707F,-0.707F, 0),
		D3DXVECTOR3(-1.000F, 0.000F, 0),
		D3DXVECTOR3(-0.707F, 0.707F, 0),
		D3DXVECTOR3( 0.000F, 1.000F, 0),
		D3DXVECTOR3( 0.707F, 0.707F, 0),
	};

	// 1. 위치 갱신
	// 최종 위치 = 현재 위치 + 속력 * 방향 * 평균 시간
	m_vcDir = vcDir[m_nDir];
	m_vcPos += m_fSpeed * m_vcDir * fTime;


	// 2. 애니메이션 갱신

	// 2.1 상태에 대한 Y쪽 그림 선택
	m_nBgnY = m_nDir ? 0: 3;		// 0: Idle

	// 2.2 1,2,3,8은 오른쪽으로 이동하는 그림 선택
	if(1== m_nDir ||  2== m_nDir ||  3== m_nDir ||  8== m_nDir)
		m_nBgnX = 0;

	if(4== m_nDir ||  5== m_nDir ||  6== m_nDir ||  7== m_nDir)
		m_nBgnX = 4;
	
	
	// 2.3 애니메이션 인덱스 갱신
	m_dCur = GetTickCount();

	if( m_nDir && m_dCur > (m_dBgn + m_dIntr))
	{
		++m_nCur;

		m_nCur %= m_nTot;
		m_dBgn	= m_dCur;
	}


	
	return 0;
}

void CGameObj::Render()
{
	// 마리오를 그린다.
	int nAniIndexX = m_nBgnX + m_nCur;
	int nAniIndexY = m_nBgnY;

	int		fX1 = m_pImg.Width  * (nAniIndexX+0)/8;
	int		fY1 = m_pImg.Height * (nAniIndexY+0)/4;

	int		fX2 = m_pImg.Width  * (nAniIndexX+1)/8;
	int		fY2 = m_pImg.Height * (nAniIndexY+1)/4;

	RECT	rcMario= { fX1, fY1, fX2, fY2 };


	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
	m_pSprite->Draw(   m_pTex
							, &rcMario
							, NULL
							, &m_vcPos
							, D3DXCOLOR(1,1,1,1)	);

	m_pSprite->End();
}