//
//
////////////////////////////////////////////////////////////////////////////////


#pragma warning( disable : 4996)


#pragma once


#ifndef __STDAFX_H_
#define __STDAFX_H_

#pragma comment(lib, "legacy_stdio_definitions.lib")
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "winmm.lib")




// 휠마우스를 쓰려면 이 구문은 반드시 필요.
#define _WIN32_WINNT 0x0400

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <time.h>
#include <Mmsystem.h>

#include <d3d9.h>
#include <d3dx9.h>


#define GMAIN			g_pApp
#define GHINST			g_pApp->m_hInst
#define GHWND			g_pApp->m_hWnd
#define GDEVICE			g_pApp->m_pd3dDevice

#include "resource.h"
#include "McUtil.h"
#include "D3DApp.h"

#include "LcInput.h"


#include "Background.h"

#include "GameObj.h"


#include "Main.h"

#endif