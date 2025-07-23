// Interface for the CMcCoin class.
//
//////////////////////////////////////////////////////////////////////

#ifndef _MCCOIN_H_
#define _MCCOIN_H_

struct Tcoin
{
	DWORD		dBgn;
	DWORD		dEnd;

	D3DXVECTOR3	vcD;
	D3DXVECTOR3	vcT;

	D3DXVECTOR3	vcPi;		// start position
	D3DXVECTOR3	vcPf;		// final position
	D3DXVECTOR3	vcPu;		// update position

	FLOAT		fHg0;		// start height(그림자와 코인 사이의 최대 거리)

	FLOAT		fHg1;		// 업데이트된 그림자와 코인사이의 거리
	FLOAT		fInc;		// 증가분

	BOOL		bAlive;		// 생존?
	BOOL		bCol;		// 충돌?

	FLOAT		fSpd;		// 스피드
	FLOAT		fFade;		// 감소값
	FLOAT		fG;			// 중력가속도



	Tcoin()
	{
		Set();
		bAlive	= FALSE;
	}


	void Update();
	void Set();

	// Coin Position
	D3DXVECTOR3 GetCoinPos()
	{
		return vcPu;
	}

	// shadow Coin Position
	D3DXVECTOR3 GetCoinShadowPos()
	{
		if(bCol)
		{
			return vcPu;
		}

		return vcPi + vcD* float(fInc) * fSpd + vcT * fHg0;
	}
};


class CMcCoin : public Tcoin
{
public:
	LPDIRECT3DTEXTURE9 m_TxCoin;

	D3DXVECTOR3	m_vcP;

public:
	CMcCoin();
	virtual ~CMcCoin();

	INT		Init();
	void	Destroy();

	INT		FrameMove();
	void	Render();

};

#endif