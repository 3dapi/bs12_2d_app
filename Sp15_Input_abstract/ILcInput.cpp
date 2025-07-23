// Implementation of the ILcInput class.
//
////////////////////////////////////////////////////////////////////////////////

#include <windows.h>
#include <d3dx9.h>

#include "ILcInput.h"
#include "LcInput.h"

int LcDev_InputCreate(int opt, ILcInput** pData, void* hWnd)
{
	*pData = NULL;

	CLcInput* pObj = new CLcInput;

	if(pObj->Create(hWnd))
	{
		delete pObj;
		return -1;
	}

	*pData = pObj;

	return 0;
}