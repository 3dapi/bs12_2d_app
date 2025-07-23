// Interface for the CMain class.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef _MAIN_H_
#define _MAIN_H_


struct PrjObj
{
	D3DXVECTOR2	vcC;		// 현재 위치
	D3DXVECTOR2	vcV;		// 속도
	D3DXVECTOR2	vcD;		// 이동 방향 벡터
	D3DXVECTOR2	vcT;		// 목표 위치

	FLOAT	fSpdI;			// 초기 이동 속력
	FLOAT	fSpdT;			// 이동 속력

	FLOAT	fR;				//충돌 반경
	FLOAT	fW;


	PrjObj()
	{
		vcC.x = 0.f;
		vcC.y = 0.f;

		vcV.x = 0.f;
		vcV.y = 0.f;

		vcT.x = 0.f;
		vcT.y = 0.f;

		fSpdI	=.5f;
		fR		= 2.f;
		fW		= 0.3f;
		fSpdT	= fSpdI;
	}

	INT	FrameMove()
	{
		FLOAT	fV;
		FLOAT	fD;

		vcD = vcT-vcC;

		fD= D3DXVec2Length(&vcD);

		//충돌
		if(fD<= fR)
			return 0;

		if(fD > 8*fR)
		{
			fW +=.01f;
		}

		else if(fD > 4*fR && fD <=8* fR)
		{
			fW +=.5f;
			fSpdT *= 0.9f;
		}

		else if(fD > 2* fR && fD <= 4* fR)
		{
			fW +=1.f;
			fSpdT = fR * 2;
		}

		else if(fD > 1* fR && fD <= 2* fR)
		{
			fW +=2.f;
			fSpdT = fR;
		}

		vcD /= fD;								// 단위 벡터를 만든다.
		vcV += vcD*fW;							// 새로운 속도 벡터를 만든다.

		fV = D3DXVec2Length(&vcV);
		vcV /=fV;

		vcV *= fSpdI;						// 속도를 단위벡터로 만든후 크기를 곱한다.
		vcC +=vcV;							//현재의 위치에 속도벡터를 더해준다.

		return -1;
	}

	void SetPosCur(D3DXVECTOR2	_vcC)
	{
		vcC = _vcC;
	}

	D3DXVECTOR2 GetPosCur()
	{
		return vcC;
	}

	void SetPosTar(D3DXVECTOR2 _vcT)
	{
		vcT = _vcT;
	}

	void ResetSpd()
	{
		fW		= 1.f;
	}

};


class CMain : public CD3DApp
{
public:
	CLcSprite*		m_pLcSprite;
	CLcInput*		m_pInput;

	CLcTexture*		m_pTex1;
	CLcTexture*		m_pTex2;

	PrjObj			m_PrjBgn;
	PrjObj			m_PrjEnd;

public:
	CMain();

	virtual INT		Init();
	virtual void	Destroy();

	virtual INT		FrameMove();
	virtual INT		Render();

	virtual LRESULT MsgProc(HWND, UINT, WPARAM, LPARAM);
};


extern CMain*	g_pApp;

#endif