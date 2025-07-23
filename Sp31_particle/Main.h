// Interface for the CMain class.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef _MAIN_H_
#define _MAIN_H_


struct Tpart
{
	// 입자의 운동 요소
	D3DXVECTOR2		m_IntP;		// 초기 위치
	D3DXVECTOR2		m_IntV;		// 초기 속도
	D3DXVECTOR2		m_IntA;		// 초기 기가속도

	D3DXVECTOR2		m_CrnP;		// 현재 위치
	D3DXVECTOR2		m_CrnV;		// 현재 속도
	D3DXVECTOR2		m_CrnA;		// 현재 가속도

	FLOAT			m_fElst;	// 탄성(Elastic) 계수
	FLOAT			m_fDamp;	// 공기 저항(Air Registance) 계수

	// 입자의 생명 요소
	DWORD			m_dColor;	//
};



class CMain : public CD3DApp
{
public:
	
	
	
public:
	CLcSprite*		m_pLcSprite;
	CLcInput*		m_pInput;

	CLcTexture*		m_pTex;


	FLOAT			m_fTimeAvg;		// Frame 평균 시간

	INT				m_PrtN;			// 입자의 수
	Tpart*			m_PrtD;			// Particle Data
	BOOL			m_bAni;




public:
	CMain();

	virtual INT		Init();
	virtual void	Destroy();

	virtual INT		FrameMove();
	virtual INT		Render();

	virtual LRESULT MsgProc(HWND, UINT, WPARAM, LPARAM);


void	SetAni(BOOL bAni=TRUE);		// 애니메이션 활성화/ 비활성화
	void	SetAvgTime(FLOAT fTime);	// 평균 시간 설정

public:
	void	SetPart(int nIdx);
};


extern CMain*	g_pApp;

#endif