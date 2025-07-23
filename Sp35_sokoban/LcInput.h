// Interface for the CLcInput class.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef _LcInput_H_
#define _LcInput_H_

class CLcInput
{
protected:
	struct McMouseSt															// Mouse State
	{
		union
		{
			struct
			{
				BOOL	bBtnLDn, bBtnLUp, bBtnLDc;								// 0 Left Button Down, 1 Left Button Up, 2 Left Button Doublic Click
				BOOL	bBtnRDn, bBtnRUp, bBtnRDc;								// 3 Right Button Down, 4 Right Button Up, 5 Right Button Doublic Click
				BOOL	bBtnMDn, bBtnMUp, bBtnMDc;								// 6 Wheel Button Down, 7 Wheel Button Up, 8 Wheel Button Doublic
			};

			BOOL m[9];
		};

		operator BOOL*()		{	return (BOOL *) &bBtnLDn;				}

	};

	BYTE			KeyCur[256], KeyOld[256];

	D3DXVECTOR3		MousePosCur;												// Z is Wheel Mouse
	D3DXVECTOR3		MousePosOld;
	McMouseSt		MsStCur;
	McMouseSt		MsStOld;

public:
	CLcInput();
	~CLcInput();

	INT		Init();
	INT		FrameMove();

	void	UpdateGeneral();

	void		AddZ(INT d);

public:
	BOOL		KeyDown(BYTE cKey);
	BOOL		KeyState(BYTE cKey);
	BOOL		GetMouseSt(INT nM);
	void		SetMouseSt(INT nBtn, BOOL bSt);

	D3DXVECTOR3	GetMousePos();

	BOOL		IsInRect(RECT rc);

};

#define GINPUT		g_pInput
extern CLcInput*	g_pInput;

#endif
