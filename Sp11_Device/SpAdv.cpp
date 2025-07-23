// 2D Game App
//
////////////////////////////////////////////////////////////////////////////////


#include "_StdAfx.h"


CD3DApp*	g_pApp;

INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR, INT )
{
	CD3DApp	d3dApp;

	g_pApp = &d3dApp;

	if(FAILED(d3dApp.Create(hInst)))
		return -1;

	return d3dApp.Run();
}