// Implementation of the CLcInput class.
//
////////////////////////////////////////////////////////////////////////////////


#include "_StdAfx.h"


CLcInput*	g_pInput;


CLcInput::CLcInput()
{
	g_pInput = this;
}

CLcInput::~CLcInput()
{

}


INT CLcInput::Init()
{
	memset(KeyCur, 0, sizeof(KeyCur));
	memset(KeyOld, 0, sizeof(KeyOld));

	memset(&MousePosCur, 0, sizeof (MousePosCur));
	memset(&MousePosOld, 0, sizeof(MousePosOld));

	memset(&MsStCur, 0, sizeof(MsStCur));
	memset(&MsStOld, 0, sizeof(MsStOld));

	return 1;
}

INT CLcInput::FrameMove()
{
	memcpy(KeyOld		,       KeyCur, sizeof(KeyCur)	  );
	memset(KeyCur		, 0, sizeof(KeyCur));

	memcpy(&MousePosOld	, &MousePosCur, sizeof(MousePosCur));
	memcpy(&MsStOld		, &MsStCur	  , sizeof(MsStCur));

	UpdateGeneral();

	return 1;
}


void CLcInput::UpdateGeneral()
{
	POINT mouse;

	// 1. Update Keyboard
	::GetKeyboardState(KeyCur);

	// 2. Update Mouse
	::GetCursorPos(&mouse);
	::ScreenToClient(GHWND, &mouse );

	MousePosCur.x = FLOAT(mouse.x);
	MousePosCur.y = FLOAT(mouse.y);
}


void CLcInput::AddZ(INT	d)
{
	MousePosCur.z += FLOAT(d);
}

void CLcInput::SetMouseSt(INT nBtn, BOOL bSt)
{
	memset(MsStCur, 0, sizeof(MsStCur));
	MsStCur.m[nBtn]  = bSt;
}


BOOL CLcInput::KeyDown(BYTE cKey)
{
	return (KeyCur[cKey] & 0x80 && KeyOld[cKey] != KeyCur[cKey]);
}

BOOL CLcInput::KeyState(BYTE cKey)
{
	return (KeyCur[cKey] & 0x80 && TRUE);
}


BOOL CLcInput::GetMouseSt(INT nBtn)
{
	return MsStCur.m[nBtn];
}


D3DXVECTOR3	CLcInput::GetMousePos()
{
	return MousePosCur;
}


BOOL CLcInput::IsInRect(RECT rc)
{
	return (MousePosCur.x > rc.left  &&
			MousePosCur.x < rc.right &&
			MousePosCur.y > rc.top   &&
			MousePosCur.y < rc.bottom);
}