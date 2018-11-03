//
//
////////////////////////////////////////////////////////////////////////////////

#ifndef __STDAFX_H_
#define __STDAFX_H_


#pragma comment(lib, "winmm.lib")

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

#include <windows.h>

#include <d3d9.h>
#include <d3dx9.h>

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <time.h>
#include <Mmsystem.h>

#define GMAIN			g_pApp
#define GHINST			g_pApp->m_hInst
#define GHWND			g_pApp->m_hWnd
#define GDEVICE			g_pApp->m_pd3dDevice

#include "resource.h"
#include "McUtil.h"
#include "McSprite.h"
#include "D3DApp.h"




#include "Main.h"

#endif