// Implementation of the CMain class.
//
////////////////////////////////////////////////////////////////////////////////


#include "_StdAfx.h"


CMain::CMain()
{
	m_pLcSprite	= NULL;
	m_pInput	= NULL;

	m_pTex		= NULL;
	

	m_PrtN		= 0;
	m_PrtD		= NULL;

	m_fTimeAvg	= 0;
	m_bAni		= FALSE;

}


INT CMain::Init()
{
	m_pLcSprite = new CLcSprite;
	if(FAILED(m_pLcSprite->Create(m_pd3dSprite)))
		return -1;

	m_pInput = new CLcInput;
	if( FAILED(m_pInput->Create(m_hWnd)))
		return -1;



	
	m_pTex	= new CLcTexture;
	if( FAILED(m_pTex->Create(m_pd3dDevice, "Texture/ball16x16.tga")))
		return -1;


	m_PrtN	= 500;
	m_PrtD	= new Tpart[m_PrtN];
	

	SetAni();
	SetAvgTime(1000.f/60);

	return 0;
}

void CMain::Destroy()
{
	SAFE_DELETE(	m_pLcSprite	);
	SAFE_DELETE(	m_pInput	);

	SAFE_DELETE(	m_pTex		);

	SAFE_DELETE_ARRAY(	m_PrtD	);
}


INT CMain::FrameMove()
{
	if(m_pInput)
		m_pInput->FrameMove();


	if(m_pInput->KeyDown('R'))
	{
		SetAni();
		SetAvgTime(1000.f/60);
	}
	


	if(!m_bAni)
		return 0;

	int		i;

	FLOAT	ftime = m_fTimeAvg * 0.005f;


	for(i=0; i<m_PrtN; ++i)
	{
		Tpart* pPrt = &m_PrtD[i];


		// 공기저항을 구한다.
		D3DXVECTOR2	vcAirR = pPrt->m_CrnV;					// 공기저항의 방향 벡터
		FLOAT		fLenV  = D3DXVec2LengthSq(&vcAirR);		// 속도의 제곱(Vx*Vx + Vy*Vy + Vz*Vz)크기 구함

		// 공기저항의 방향 벡터를 구한다.
		D3DXVec2Normalize(&vcAirR, &vcAirR);

		// 이동 속도와 반대로 설정
		vcAirR	*= -1.F;

		// 속력제곱 * 공기 저항 계수를 곱함.
		vcAirR	*= fLenV * pPrt->m_fDamp;


		// 1. 가속도에 공기저항을 더한다.
		pPrt->m_CrnA = pPrt->m_IntA + vcAirR;

		// 2. 현재 속도 갱신
		pPrt->m_CrnV += pPrt->m_CrnA * ftime;

		// 3. 현재 위치 갱신
		pPrt->m_CrnP += pPrt->m_CrnV * ftime;

		// 4. 경계값 설정
		if(pPrt->m_CrnP.y<-40.f)
		{
			SetPart(i);
		}
	}


	return 0;
}


INT CMain::Render()
{
	m_pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0,120,160), 1.0f, 0 );

	if( FAILED( m_pd3dDevice->BeginScene() ) )
		return -1;


	m_pd3dSprite->Begin(D3DXSPRITE_ALPHABLEND);
	if(m_bAni)
	{
		LPDIRECT3DTEXTURE9 pTex = (LPDIRECT3DTEXTURE9)m_pTex->GetTexture();

		for(int i=0; i<m_PrtN; ++i)
		{	
			Tpart* pPrt = &m_PrtD[i];

			D3DXVECTOR3	vcP  =	pPrt->m_CrnP;

			vcP.z = 0;

			m_pd3dSprite->Draw(pTex, NULL, NULL, &vcP, pPrt->m_dColor);
		}

	}

	m_pd3dSprite->End();



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



void CMain::SetAni(BOOL bAni)
{
	m_bAni = bAni;

	if(!m_bAni)
		return;

	for(int i=0; i<m_PrtN; ++i)
	{
		SetPart(i);
	}
}


void CMain::SetAvgTime(FLOAT fTime)
{
	m_fTimeAvg = fTime;
}





void CMain::SetPart(int nIdx)
{
	Tpart* pPrt = &m_PrtD[nIdx];

	FLOAT	fTheta;		// 각도 θ
	FLOAT	fSpdR;		// 속도 크기

	// 초기 가속도
	pPrt->m_IntA = D3DXVECTOR2(0, -0.2F);

	//초기 속도와 위치를 설정하기 위한 변수
	fTheta	= float(rand()%41);
	fTheta	-=20.f;
	

	fSpdR = 100.f + rand()%101;
	fSpdR *=0.1f;

	// 라디안으로 변경
	fTheta	= D3DXToRadian(fTheta);

	// 초기 속도
	pPrt->m_IntV.x = fSpdR * sinf(fTheta);
	pPrt->m_IntV.y = fSpdR * cosf(fTheta);

	// 초기 위치		
	pPrt->m_IntP.x = 400.f;
	pPrt->m_IntP.y = 0.f;


	// 탄성 계수 설정
	pPrt->m_fElst= (50 + rand()%51)*0.01f;

	// 공기저항 계수
	pPrt->m_fDamp= (100 + rand()%101)*0.00001F;

	// 초기 위치, 속도, 가속도를 현재의 값들의 초기 값으로 설정
	pPrt->m_CrnP = pPrt->m_IntP;
	pPrt->m_CrnV = pPrt->m_IntV;
	pPrt->m_CrnA = pPrt->m_IntA;



	// 입자의 생명 요소
	float	fColor = 30.f + rand()%71;
	fColor	*=0.01f;
	pPrt->m_dColor	=	D3DXCOLOR(1, 1, 1, fColor);
}