// 2D Game App
//
////////////////////////////////////////////////////////////////////////////////


#include "_StdAfx.h"


CMain*	g_pApp;

//INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR, INT )

int main(int argc, char** argv)
{
	CMain	d3dApp;

	HINSTANCE hInst = (HINSTANCE)GetModuleHandle(NULL);
	g_pApp = &d3dApp;

	if(FAILED(d3dApp.Create(hInst)))
		return -1;

	return d3dApp.Run();
}