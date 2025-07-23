// Implementation of the CMcCoin class.
//
////////////////////////////////////////////////////////////////////////////////


#include "_StdAfx.h"

void Tcoin::Update()
{
	if(!bAlive)
		return;

	dEnd = timeGetTime();

	if(dEnd <(dBgn+15))
		return;

	dBgn = dEnd;

	// 지면에 충돌
	if(FALSE == bCol && fHg1>=fHg0)
	{
		// 지면과 충돌했다면 더이상 포물선 운동은 필요없어진다.
		bCol = TRUE;

		// 그림자와의 차이를 같게 만든다.
		fHg1 = fHg0;

		// 최종 위치에서 현재 위치 사이의 거리를 이용해서 감쇄값을 설정한다.
		// 1/2 mv*v = m * a * h
		// a = v*v/(2*h)
		// fade ~ speed*speed*0.467/distance;

		D3DXVECTOR3 vcT = vcPf - vcPu;
		FLOAT	fL = D3DXVec3Length(&vcT);

		fFade = -(fSpd*fSpd)/fL * 0.46f;
	}

	fInc +=1.f;

	if(FALSE == bCol)
	{
		fHg1 += fInc * fInc * fG;
	}

	else
	{
		fSpd += fFade;
	}

	if(fSpd<0.f)
	{
		bAlive = FALSE;
		return ;
	}


	if(FALSE == bCol)
	{
		vcPu = vcPi + vcD* float(fInc) * fSpd + vcT * fHg1;
	}

	else
	{
		vcPu += vcD * fSpd;
	}
}


void Tcoin::Set()
{
	dBgn	= timeGetTime();

	fHg0	= 70.f + 3 * (rand()%11);					// start height(그림자와 코인 사이의 최대 거리)
	fSpd	= 16.f + rand()%5;							// 스피드
	fG		= 0.045f + 0.002f*(rand()%6);					// 중력가속도
	vcPi	= D3DXVECTOR3(200, 400, 0);					// 초기 위치


	vcPf	= D3DXVECTOR3(450 + 20.f*(rand()%11), 200 + 20.f*(rand()%11), 0);			// 최종 위치

	// 살아 있는 상태로.. (죽어있으면 운동을 안함)
	bAlive	= TRUE;

	// 지면과 충돌
	bCol	= FALSE;

	fInc	= 0;
	fHg1	= 0.f;

	// 나중위치에서 처음위치를 빼고...
	vcD = vcPf - vcPi;

	// 정규화.
	D3DXVec3Normalize(&vcD, &vcD);

	//		vcT.x = fabsf(vcD.y);
	//		if( vcD.x<0.f)
	//			vcT.x *=-1.f;
	//
	//		vcT.y = fabsf(vcD.x);

	vcT.x = 0.f;
	vcT.y = 1.f;

	// 초기 코인의 위치를 정한다.
	vcPu	= vcPi;
}




CMcCoin::CMcCoin()
{
	m_TxCoin	= NULL;
}

CMcCoin::~CMcCoin()
{

}



INT CMcCoin::Init()
{
	char	sFile[256];

	sprintf(sFile, "texture/coin.png");

	if( FAILED( McUtil_TextureLoad(GDEVICE, sFile, m_TxCoin, NULL, 0xFF000000) ) )
		return -1;


	return 1;
}

void CMcCoin::Destroy()
{
}

INT CMcCoin::FrameMove()
{
	Update();

	return 1;
}


void CMcCoin::Render()
{
	RECT rc2 ={0,96,36,128};


	RECT rc1 ={0,0,36,32};

	D3DXVECTOR3	vcCoin= GetCoinPos();
	D3DXVECTOR3	vcShow = GetCoinShadowPos();

	D3DXMATRIX mtWld;


	//GSPRITE->Draw(m_TxCoin, &rc2, &vcScl, NULL, 0, &vcShow, D3DXCOLOR(1,1,1,0.5f));

	D3DXMatrixScaling(&mtWld, 1.f, 0.8f, 1);
	GSPRITE->SetTransform(&mtWld);
	
	GSPRITE->Draw(m_TxCoin, &rc2, NULL, &vcShow, D3DXCOLOR(1,1,1,0.5f));

	D3DXMatrixIdentity(&mtWld);
	GSPRITE->SetTransform(&mtWld);
	GSPRITE->Draw(m_TxCoin, &rc1, NULL, &vcCoin, D3DXCOLOR(1,1,1,1));
}