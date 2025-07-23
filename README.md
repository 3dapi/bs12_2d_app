php
 include '../base/lc\_header.php';
 include '../base/lc\_util.php';
?


  

  
# ◈2D Game Programming (Advanced)◈


  
## 1 C++ 클래스 전환


  
2D 게임프로그래밍 기초 코드를 가지고 2D 게임을 충분히 만들 수 있지만 코드를 하나의
  
파일에 작성을 하게 된다면 확장의 어려움이 있습니다. 실제 게임들은 확장과 유지 보수를
  
위해서 C 스타일의 코드 보다 C++ 스타일의 코드로 게임을 제작하는 경우가 많습니다.
  
C++의 객체지향을 사용하면 구조화가 쉽고, 구현과 디버깅이 편리하며, 코드의 재사용과
  
새로운 요소에 대한 확장이 C스타일의 코드들 보다 월등히 좋습니다. 먼저 디바이스와
  
윈도우를 시작으로 텍스처, 키보드와 마우스에 대한 인풋 시스템, 사운드, 폰트 등을
  
클래스로 만들도록 하겠습니다.
  

  

  

  

  

  
### 1.1. 디바이스와 윈도우


  
앞 강좌의 2D 게임프로그래밍 기초 코드들을 한 번 살펴 보면 게임에서 윈도우와 디바이스,
  
스프라이트는 한 번만 생성을 합니다. 이 부분을 상위클래스로 놓고 이 클래스를 상속받아서
  
사용한다면 하위클래스는 게임에 관련된 객체만 신경을 쓰기만 하면 됩니다. 한번 바꾸어
  
보도록 합시다. 상위 클래스를 CD3DApp이라 하고 게임에 관련된 텍스처를 다루는 클래스를
  
CMain으로 바꾸어 보도록 합시다. VC의 메뉴에서 Insert 메뉴를 확장하면 New Class가
  
있습니다. 여기에 클래스 이름을 CD3DApp을 넣어 OK버튼을 클릭합니다.
  

  

  
![](https://github.com/3dapi/bs12_2d_app/raw/master/img_src/image0001.png)
  

  

  
클래스 뷰를 보면 CD3DApp 클래스가 만들어져 있음을 볼 수 있습니다. 다음으로 비주얼
  
스튜디오의 File->New 를 선택해서 다음 그림과 같이 \_StdAfx.h 파일을 추가합니다.
  

  

  
![](https://github.com/3dapi/bs12_2d_app/raw/master/img_src/image0002.png)
  

  

  
이 \_StdAfx.h 파일은 게임에서 사용되는 모든 헤더 파일들과 라이브러리, 그리고 공통
  
매크로(Macro)를 모아 놓을 것입니다. 지금은 다음과 같이 작성합니다.
  


```

	#ifndef \_\_STDAFX\_H\_
	#define \_\_STDAFX\_H\_

	#pragma comment(lib, "winmm.lib")

	#pragma comment(lib, "d3d9.lib")
	#pragma comment(lib, "d3dx9.lib")

	#include < windows.h>

	#include < d3d9.h>
	#include < d3dx9.h>

	#define WIN32\_LEAN\_AND\_MEAN		// Exclude rarely-used stuff from Windows headers

	#include < windows.h>
	#include < stdio.h>
	#include < stdlib.h>
	#include < string.h>
	#include < malloc.h>
	#include < memory.h>
	#include < tchar.h>
	#include < time.h>
	#include < Mmsystem.h>

	#define SAFE\_DELETE(p)       { if(p) { delete (p);     (p)=NULL; } }
	#define SAFE\_DELETE\_ARRAY(p) { if(p) { delete[] (p);   (p)=NULL; } }
	#define SAFE\_RELEASE(p)      { if(p) { (p)->Release(); (p)=NULL; } }


	#include "D3DApp.h"

	#endif

```

  
다음으로 디바이스를 만들었던 게임 기초 과정의 코드들 중에 일부를 복사해서 D3DApp.h
  
파일에 다음과 같이 붙여 놓고 정리합니다. 이 CD3DApp 에 함수들을 잘라내어 붙이되
  
접근 권한을 public으로 설정합니다.
  
그리고 Init() 함수부터 Render() 함수들은 CD3DApp 클래스를 상속 받은 하위 클래스에서
  
이를 재정의 해서 사용할 수 있도록 들을 virtual로 설정 합니다.
  


```

	class CD3DApp
	{
	public:
		TCHAR			m\_sCls[128]	;
		HINSTANCE		m\_hInst		;
		HWND			m\_hWnd		;
		DWORD			m\_dWinStyle	;
		DWORD			m\_dScnX		;		// Screen Width
		DWORD			m\_dScnY		;		// Screen Height
		BOOL			m\_bShowCusor	;		// Show Cusor
		BOOL			m\_bWindow	;		// Window mode

		D3DPRESENT\_PARAMETERS	m\_d3dpp		;
		LPDIRECT3D9		m\_pD3D		;		// D3D
		LPDIRECT3DDEVICE9	m\_pd3dDevice	;		// Device
		LPD3DXSPRITE		m\_pd3dSprite	;		// 2D Sprite


	public:
		CD3DApp();

		//Window
		INT		Create(HINSTANCE hInst);
		INT		Run();
		Void		Cleanup();
		INT		Render();

		LRESULT MsgProc(HWND, UINT, WPARAM, LPARAM);
		static LRESULT WINAPI WndProc(HWND, UINT, WPARAM, LPARAM);

	protected:
	};

```

  
D3DApp.cpp 파일에서 CD3DApp 생성자 부분에서 다음과 같이 변수들을 초기화 합니다.
  


```

	static CD3DApp*	g\_pD3DApp;

	CD3DApp::CD3DApp()
	{
		g\_pD3DApp	= this;

		strcpy(m\_sCls, "2D Game App");

		m\_hInst		= NULL;
		m\_hWnd		= NULL;
		m\_dWinStyle	= WS\_OVERLAPPED| WS\_CAPTION| WS\_SYSMENU| WS\_VISIBLE;
		m\_dScnX		= 800;
		m\_dScnY		= 600;

		m\_bShowCusor	= TRUE;
		m\_bWindow	= TRUE;			// Window mode

		m\_pD3D		= NULL;			// D3D
		m\_pd3dDevice	= NULL;			// Device
		m\_pd3dSprite	= NULL;			// 2D Sprite
	}

	…

	LRESULT WINAPI CD3DApp::WndProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
	{
		return g\_pD3DApp->MsgProc(hWnd, msg, wParam, lParam);
	}

```

  
디바이스 생성 코드들은 Create() 함수에 옮겨 놓고, 해제 부붑은 Cleanup() 함수 안으로 이동합니다.
  
BegineScene() / EndScene() 함수 내용은 Render() 함수로 옮겨 놓습니다.
  

  
자세한 코드는 다음 예제를 참고 하기 바랍니다.
  

  
[Sp11\_Device.zip](https://github.com/3dapi/bs12_2d_app/raw/master/Sp11_Device.zip)
  

  

  

  

  

  

  
### 1.2. CMain 클래스


  
CD3DApp 클래스는 윈도우와 디바이스의 생성, 초기화, 해제부분을 담당하는 클래스이고 게임
  
데이터를 담당하는 클래스인 CMain 클래스를 만들어 봅시다.
  
CD3DApp 클래스를 만들 때와 마찬가지로 메뉴 -> Insert -> New Class를 선택합니다. Class
  
Information에 CMain을 넣고 Base class에 Derived Form 에 CD3DApp 을 public으로 설정한
  
다음 OK버튼을 클릭합니다.
  

  

  
![](https://github.com/3dapi/bs12_2d_app/raw/master/img_src/image0003.png)
  

  

  
클래스 뷰로 CMain 클래스가 작성되었는지 확인합니다.
  

  
CMain 클래스부분은 게임에 관련된 객체를 다루므로 남아 있던 전역변수들은 CMain 의 멤버
  
변수로 할당합니다. 또한 CD3DApp에서 virtual로 정의되어 있던 Init() ~Destroy() 함수들을
  
CMain 에서 재정의 합니다.
  
CMain 의 헤더파일은 다음과 같이 정리됩니다.
  


```

	class CMain : public CD3DApp
	{
	public:

	public:
		CMain();

		virtual INT	Init();
		virtual void	Destroy();

		virtual INT	FrameMove();
		virtual INT	Render();

		virtual LRESULT MsgProc(HWND, UINT, WPARAM, LPARAM);
	};

	extern CMain*	g\_pApp;

```

  
WinMain()부분은 다음과 같이 정리합니다.
  


```

	#include "\_StdAfx.h"


	CMain*	g\_pApp;

	INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR, INT )
	{
		CMain	d3dApp;

		g\_pApp = &d3dApp

		if(FAILED(d3dApp.Create(hInst)))
			return -1;

		return d3dApp.Run();
	}

```

  
이전에 공통으로 사용하는 매크로를 \_StdAfx.h 파일에 저장했는데 게임 프로그램 안에서
  
두루 사용하는 함수, 매크로, 구조체 등을 Util 파일에 저장해 놓고 사용하도록 합시다.
  
McUtil.cpp와 McUtil.h파일을 추가해서 공통 사용 매크로 등을 옮겨 놓습니다.
  

  
코드의 자세한 내용은 다음 예제를 참고 하기 바랍니다.
  

  
[Sp12\_Main.zip](https://github.com/3dapi/bs12_2d_app/raw/master/Sp12_Main.zip)
  

  

  

  

  

  
### 1.3. 텍스처 클래스


  
2D 게임 텍스처를 생성하기 위해서는 D3DXCreateTextureFromFileEx() 함수를 이용해야 합니다.
  
그런데 이 함수의 인수 리스트는 상당히 많고, 옵션 또한 기억하기 어렵습니다. 또한
  
텍스처뿐만 아니라 원본 이미지의 정보 또한 필요한데 이것을 처음 DirectX를 사용하는 사람은
  
그대로 D3DXIMAGE\_INFO 구조체 변수를 따로 만들어 놓고 사용합니다.
  

  
LPDIRECT3DTEXTURE9 변수와 D3DXIMAGE\_INFO 구조체 변수를 하나의 클래스 안에 저장해 놓고
  
사용하면 편리한 점이 많은데 이 클래스를 CLcTexture 클래스로 정하겠습니다. 이 클래스는
  
LPDIRECT3DDEVICE9 변수 m\_pDev, D3DXIMAGE\_INFO 변수 m\_Img, LPDIRECT3DTEXTURE9 변수 m\_pTx를
  
멤버 변수로 가지고 있습니다.
  

  
주요 메시지는 이미지의 폭과 높이, 그리고 텍스처 포인터를 가져 오는 함수들입니다.
  
생성과 소멸을 합쳐 구현 한다면 다음과 같이 정의 됩니다.
  


```

	class CLcTexture
	{
	protected:
		LPDIRECT3DDEVICE9	m\_pDev;

		D3DXIMAGE\_INFO		m\_Img;
		LPDIRECT3DTEXTURE9	m\_pTx;

	public:
		CLcTexture();
		virtual ~CLcTexture();

		virtual INT	Create(LPDIRECT3DDEVICE9 pDev, char* sFile);
		virtual void	Destroy();

	public:
		INT		GetImageWidth();
		INT		GetImageHeight();
		Void		GetImageRect(RECT* pRc);

		LPDIRECT3DTEXTURE9	GetTexture();
	};

```

  
각 함수에 대한 구현은 먼저 생성자에서 이미지 정보와 텍스처 포인터를 초기화 합니다.
  


```

	CLcTexture::CLcTexture()
	{
		m\_pDev	= NULL;

		m\_pTx	= NULL;
		memset(&m\_Img, 0, sizeof m\_Img);
	}

```

  
텍스처 포인터 해제는 Destroy() 함수에서 진행 하도록 합니다.
  


```

	void CLcTexture::Destroy()
	{
		if(m\_pTx)
		{
			m\_pTx->Release();
			m\_pTx= NULL;
		}
	}

```

  
텍스처 객체를 생성은 Create() 함수가 담당을 하고 코드 내부에서
  
D3DXCreateTextureFrom-FileEx() 함수를 호출하도록 합니다.
  


```

	INT CLcTexture::Create(LPDIRECT3DDEVICE9 pDev, char* sFile)
	{
		m\_pDev	= pDev;

		DWORD	dColorKey	= 0x00FFFFFF;

		if(FAILED(D3DXCreateTextureFromFileEx(
			m\_pDev
			, sFile
			, D3DX\_DEFAULT
			, D3DX\_DEFAULT
			, 1
			, 0
			, D3DFMT\_UNKNOWN
			, D3DPOOL\_MANAGED
			, D3DX\_FILTER\_NONE
			, D3DX\_FILTER\_NONE
			, dColorKey
			, &m\_Img
			, NULL
			, &m\_pTx
			)) )
		{
			m\_pTx = NULL;
			MessageBox( GetActiveWindow()
					, "Create Texture Failed"
					, "Err"
					, MB\_ICONEXCLAMATION
					);
			return -1;
		}

		return 0;
	}

```

  
이미지 정보와 텍스처 포인터를 가져오는 함수는 다음과 같이 구현합니다.
  


```

	INT CLcTexture::GetImageWidth()
	{
		return m\_Img.Width;
	}


	INT CLcTexture::GetImageHeight()
	{
		return m\_Img.Height;
	}

	void CLcTexture::GetImageRect(RECT* pRc)
	{
		pRc->left	= 0;
		pRc->top	= 0;
		pRc->right	= m\_Img.Width;
		pRc->bottom	= m\_Img.Height;
	}

	LPDIRECT3DTEXTURE9 CLcTexture::GetTexture()
	{
		return m\_pTx;
	}

```

  
전체 내용은 다음 예제를 참고 하기 바랍니다.
  

  
[Sp13\_Texture.zip](https://github.com/3dapi/bs12_2d_app/raw/master/Sp13_Texture.zip)
  

  

  
만약 사용자 정의 리소스에서 텍스처를 생성할 경우도 있는데 이러한 경우
  
D3DXCreateTextureFromFileInMemoryEx() 함수를 이용해야 합니다.
  
다음은 리소스에서 텍스처를 생성할 수 있도록 위의 코드를 확장한 텍스처
  
클래스 예제입니다.
  

  
[Sp13\_TextureRsc.zip](https://github.com/3dapi/bs12_2d_app/raw/master/Sp13_TextureRsc.zip)
  

  

  

  

  

  
### 1.4. ID3DXFont


  
문자열을 화면에 출력하는 방법은 DirectX Back buffer의 포인터를 가져와 DC
  
(Device Context)를 얻어 출력하는 방법, 출력할 문자열에 따른 실시간 텍스처를
  
만들어서 스프라이트로 출력하는 방법, DirectX의 문자열 출력 인터페이스
  
ID3DXFont를 이용하는 방법 등이 있습니다.
  
여기서는 문자열 출력 클래스를 만들지 않고 편리하게 사용할 수 있는 DirectX의
  
ID3DXFont를 이용 방법을 소개하겠습니다.
  

  
ID3DXFont 인터페이스는 DirectX의 버전에 따라 ID3DXSprite 만큼 조금 - 상당히 많이 -
  
달라졌습니다. 개인적으로 9.0b 버전 인터페이스가 잘 되어 있지 않나 생각이 듭니다.
  
이 부분은 나중에 더 말씀 드리죠. 여기서는 9.0c 기준으로 설명하겠습니다.
  

  
ID3DXFont 인스턴스를 얻기 위해서는 두 가지 방법이 있는데 하나는 D3DXFONT\_DESC 구조체를
  
이용해서 D3DXCreateFontIndirect() 함수로 ID3DXFont 객체를 생성하는 Indirect 와
  
D3DXCreateFont () 함수에 인수 리스트를 작성하는 방법이 있습니다.
  

  
D3DXCreateFont() 함수의 인수 리스트 내용은 D3DXFONT\_DESC 구조체를 채우는 값들과
  
동일하므로 Indirect 방법을 가지고 설명하겠습니다.
  

  
먼저 폰트객체 포인터를 선언을 해야 합니다. [Sp14\_ID3DXFont.zip](https://github.com/3dapi/bs12_2d_app/raw/master/Sp14_ID3DXFont.zip) 파일의 압축을 풀고
  
CMain 클래스를 보면 다음과 같이 ID3DXFont 객체들을 선언합니다.
  


```

	class CMain : public CD3DApp
	{
	protected:
		ID3DXFont*	m\_pDXFont1;
		LPD3DXFONT	m\_pDXFont2; 	//LPD3DXFONT = ID3DXFont*
	…

```

  
으로 되어 있습니다.
  

  
앞서 ID3DXFont는 디바이스의 인스턴스가 필요하므로 CMain::Init() 함수를 보면
  
HFONT와 LOGFONT구조체를 이용하는 두 가지 방법의 예가 있습니다.
  


```

	if( FAILED(D3DXCreateFont( m\_pd3dDevice
				, 20, 0
				, FW\_BOLD, 1, FALSE
				, HANGUL\_CHARSET
				, OUT\_DEFAULT\_PRECIS, ANTIALIASED\_QUALITY, FF\_DONTCARE
				, "궁서체"
				, &m\_pDXFont1 )))
		return -1;


	D3DXFONT\_DESC hFont =
	{
		28, 0
		, FW\_BOLD, 1, FALSE
		, HANGUL\_CHARSET
		, OUT\_DEFAULT\_PRECIS, ANTIALIASED\_QUALITY, FF\_DONTCARE
		, "굴림체"
	};

	if(FAILED(D3DXCreateFontIndirect(GDEVICE, &hFont, &m\_pDXFont2)))
		return -1;

```

  
주의할 점은 위의 경우처럼 LOGFONT를 이용하지 않고 HFONT를 이용할 경우 LPD3DXFONT의
  
인스턴스를 만들고 나서 반드시 DeleteObject() 함수를 통해서 HFONT의 인스턴스를 반드시
  
해제한다는 점입니다.
  

  
LPD3DXFONT 에 대한 해제는 COM을 상속받으므로 역시 Release() 함수를 통해서 해제합니다.
  
자세한 코드는 CMain::Destroy() 함수에 구현해 놓았습니다.
  


```

	RECT	rc;
	::SetRect(&rc, 100, 50, 500, 50 + 30);

	m\_pDXFont1->DrawText(NULL, "Hello world", -1, &rc, 0, D3DXCOLOR(1,1,0,1)    );

	::SetRect(&rc, 100, 90, 800, 90 + 30);

	m\_pDXFont2->DrawText(NULL, "안녕하세요. ID3DXFont 예제입니다."
	, -1, &rc, 0, XCOLOR(0,1,1,1));

```

  
문자열을 출력하는 부분은 CMain::Render() 함수 안에 구현되어 있는데 객체의 DrawText()
  
함수를 호출하는 것으로 되어 있습니다. 폰트의 DrawText() 함수 사용은 디바이스의
  
BeginScene(), EndScene() 함수 안에서 호출 해야 됩니다.
  

  
DrawText() 함수의 인수 리스트는 문자열이 옵니다. 다음으로 -1값이 있는데 -1을 설정해주면
  
문자열 전체를 출력해 줍니다. 그 다음으로 출력할 문자열의 범위를 이미지를 출력할 때와
  
마찬가지로 지정해야 합니다.
  
다음으로 정렬(왼쪽, 오른쪽, 중앙 상, 하)하는 옵션이고, 마지막은 문자열의 색상입니다.
  

  
DrawText() 함수는 여러 가지 편리한 점이 많이 있음에도 한가지 아쉬운 점은 문자열이 출력될
  
영역을 프로그래머가 작성해야 한다는 것입니다. 위의 예제는 임의로 값을 넣었지만 정확하게
  
문자열의 영역을 얻으려면 HFONT 인스턴스를 가지고 GetTextExtentPoint32() 함수를 통해서
  
얻는 수밖에 없습니다. 이 부분은 2D 게임 만들기 과정에서 벗어나는 부분인지라 더 이상
  
진행하지 않겠습니다. 여러분은 임의로 글자의 영역을 지정해서 사용해도 2D 게임을 만드는
  
데 전혀 지장이 없으므로 그리 걱정을 안 해도 됩니다.
  

  
[Sp14\_ID3DXFont.zip](https://github.com/3dapi/bs12_2d_app/raw/master/Sp14_ID3DXFont.zip)
  

  

  

  

  

  
### 1.5. 키보드와 마우스


  
게임프로그램에서 키보드와 마우스에 대한 처리는 Window API 함수들을 이용하는 방법과
  
Direct Input를 이용하는 두 가지 방법이 있습니다. Window API를 이용하는 방법은 그리
  
복잡한 개념 없이 단 4개의 함수로 처리가 가능하고, 아스키(ASCII) 코드 값과 키보드의
  
키 값이 거의 일치되어 있고, 마이크로소프트의 윈도우 운영체제를 사용하는 모든 기기에서
  
작동이 가능하기 때문에 일단 코드를 만들어 놓으면 그리 큰 수고를 들이지 않아도 유지
  
보수가 가능합니다. 그래도 아쉬운 점은 마우스 휠 스크롤을 얻기 위해서 메시지 프로시저를
  
통해서 처리해야 한다는 것입니다.
  

  
Direct Input은 디바이스와 비슷한 구조와 절차를 거치는 과정이 필요합니다. 이것을 만드는데
  
조금(?) 수고가 들지만 한 번 만들어 놓으면 거의 변함 없이 사용할 수 있기 때문에 경력자들은
  
Direct Input을 많이 선호 하는 편입니다. 하지만 Window API함수나 Direct Input를 사용하나
  
성능의 차이는 거의 없다고 보면 됩니다.
  

  
여기서는 Direct Input이 아닌 키보드와 마우스에 대한 Window API함수를 이용해서 클래스로
  
만들도록 하겠습니다.
  

  
키보드에 대한 처리 함수는 GetAsyncKeyState() 함수와 GetKeyboardState() 함수 두 종류가
  
있습니다. GetAsyncKeyState() 함수는 키보드와 마우스를 포함한 256개의 가상 키 값에 대한
  
이벤트(down)을 각각 처리합니다. 예를 들어서 'A' 키(대문자 임을 주의하십시오.) 의 이벤트를
  
받고 싶다면 다음 과 같이 처리하면 됩니다.
  


```

	if( 0x8000 & GetAsyncKeyState('A') )
		MessageBox(m\_hWnd, "You Pressed A Key.", 0,0);

```

  
주의할 점은 0x8000 값과 비트 연산을 하는데 이것은 GetAsyncKeyState() 함수 리턴 값이
  
short 형으로 되어 있고, 키 이벤트는 상위 바이트에 값이 저장되기 때문 입니다.
  

  
GetKeyboardState() 함수는 GetAsyncKeyState() 함수와 키 이벤트를 처리하는데 다른 점은
  
한꺼번에 가상 키 256개만큼 모든 이벤트들을 처리합니다. 사용법은 다음과 같습니다.
  


```

	// 초기화
	memset(m\_KeyCur, 0, sizeof(m\_KeyCur));
	SetKeyboardState(m\_KeyCur);
	…
	unsigned char KeyCur[256]={0};
	GetKeyboardState(KeyCur);
	…
	if( 0x80 & KeyCur['B'] )
		MessageBox(m\_hWnd, "You Pressed B Key.", 0,0);

	if( 0x80 & KeyCur[VK\_LBUTTON] )
		MessageBox(m\_hWnd, "You Pressed Left Mouse Button.", 0,0);

```

  
윈도우 CE에서 간혹 GetKeyboardState() 함수를 사용할 수 없을 경우가 있는데 이 때에는
  
for 문 안에서 256 만큼 GetAsyncKeyState() 함수를 호출해야 합니다.
  

  
다음으로 마우스의 위치를 얻는 방법입니다. 마우스의 위치는 GetCursorPos() 함수를 통해서
  
바탕화면에 대한 마우스의 위치를 얻습니다. 그리고 이 값을 현재 윈도우의 그리기
  
RECT 영역으로 환원하는 함수 ScreenToClient() 함수를 호출해서 윈도우에 대한 상대적인
  
좌표 값으로 바꿉니다.
  


```

	POINT mouse;
	::GetCursorPos(&mouse);
	::ScreenToClient(m\_hWnd, &mouse );

```

  
이 내용을 가지고 키보드와 마우스에 대한 클래스를 만들어 봅시다.
  
먼저 키보드에서 주요 메시지들을 보면 키보드의 눌렀을 때, 누르고 있을 때, 누르고 있는
  
것을 뗐을 때 세 가지 기본 동작이 필요합니다. 이 부분을 생각하고 CLcInput 클래스를
  
만들고 다음과 같이 멤버와 함수를 설정합니다.
  


```

	class CLcInput
	{
	public:
		enum EInputState
		{
			EINPUT\_NONE	= 0,
			EINPUT\_DOWN	= 1,
			EINPUT\_UP	= 2,
			EINPUT\_PRESS=	3,
		};

	protected:
		BYTE	m\_KeyCur[256];	// 현재의 상태
		BYTE	m\_KeyOld[256];	// 이전의 상태
		BYTE	m\_KeyMap[256];	// 키보드 맵

	public:
		CLcInput();
		virtual ~CLcInput();

		INT	FrameMove();

		BOOL	KeyDown	(INT nKey);
		BOOL	KeyUp	(INT nKey);
		BOOL	KeyPress(INT nKey);
		INT	KeyState(INT nKey);
	};

```

  
키보드 이벤트의 처리는 CLcInput::FrameMove() 함수에서 처리하는데 다음과 같이 현재
  
키보드의 값들을 이전 값에 복사를 한 다음 이 둘을 이용해서 각각의 세 가지 상태를
  
키보드 맵에 설정을 합니다.
  


```

	INT CLcInput::FrameMove()
	{
		INT i=0;

		//1. currrent 값을 old 에 복사, 이전 상태를 저장한다.
		memcpy(m\_KeyOld, m\_KeyCur, sizeof(m\_KeyOld));

		//2. Current 와 Map의 값을 0으로 초기화
		memset(m\_KeyCur, 0, sizeof(m\_KeyCur));
		memset(m\_KeyMap, 0, sizeof(m\_KeyMap));

		//3. 키보드 이벤트를 가져옴
		GetKeyboardState(m\_KeyCur);

		for(i=0; i< 256; ++i)
		{
			BYTE	vKey = m\_KeyCur[i] & 0x80;	// 현재의 키보드 상태를 읽어온다.
			m\_KeyCur[i] = (vKey)? 1: 0;		// 키보드 상태를 0과 1로 정한다.

			INT nOld = m\_KeyOld[i];
			INT nCur = m\_KeyCur[i];

			if	(0 == nOld && 1 ==nCur)	m\_KeyMap[i] = EINPUT\_DOWN;	// Down
			else if	(1 == nOld && 0 ==nCur)	m\_KeyMap[i] = EINPUT\_UP;	// Up
			else if	(1 == nOld && 1 ==nCur)	m\_KeyMap[i] = EINPUT\_PRESS;	// Press
			else				m\_KeyMap[i] = EINPUT\_NONE;	// NONE
		}

		return 0;
	}

```

  
좀 더 자세한 코드는 다음 예제를 참고 하기 바랍니다.
  

  
[Sp15\_Keyboard.zip](https://github.com/3dapi/bs12_2d_app/raw/master/Sp15_Keyboard.zip)
  

  

  
마우스에 대한 처리도 키보드와 유사 합니다. CLcInput 클래스 선언에 다음과 같이 설정합니다.
  


```

	class CLcInput
	{
	protected:
		BYTE			m\_BtnCur[8];		// 현재의 상태
		BYTE			m\_BtnOld[8];		// 이전의 상태
		BYTE			m\_BtnMap[8];		// 맵

		D3DXVECTOR3		m\_vcCur;		// Z is Wheel Mouse
		D3DXVECTOR3		m\_vcOld;
		D3DXVECTOR3		m\_vcEps;

		HWND			m\_hWnd;

	public:
		CLcInput();
		~CLcInput();

		INT		Create(HWND hWnd);
		INT		FrameMove();
		LRESULT		MsgProc(HWND,UINT, WPARAM, LPARAM);

	public:
		BOOL		BtnDown	 (INT nBtn);
		BOOL		BtnUp	 (INT nBtn);
		BOOL		BtnPress (INT nBtn);
		INT		BtnState (INT nBtn);

		D3DXVECTOR3 GetMousePos();
		D3DXVECTOR3 GetMouseEps();
	};

```

  
마우스의 왼쪽 버튼, 오른 쪽 버튼, x, y 위치는 CLcInput::FrameMove() 함수에서
  
처리하고 휠 마우스에 대한 이벤트는 CLcInput::MsgProc() 함수에서 처리합니다.
  

  
CLcInput::MsgProc() 함수는 CLcInput 객체가 생성되고 나서 CMain::MsgProc() 함수에서
  
호출 될 수 있도록 합니다.
  


```

	INT CLcInput::FrameMove()
	{
		INT nBtn=0;

		//1. currrent 값을 old 에 복사, 이전 상태를 저장한다.
		memcpy(m\_BtnOld, m\_BtnCur, sizeof(m\_BtnOld));

		//2. Current 와 Map의 값을 0으로 초기화
		memset(m\_BtnCur, 0, sizeof(m\_BtnCur));
		memset(m\_BtnMap, 0, sizeof(m\_BtnMap));

		//3. current 이벤트 를 가져옴
		m\_BtnCur[0] = (GetAsyncKeyState(VK\_LBUTTON) & 0x8000)? 1: 0;	// Left Button
		m\_BtnCur[1] = (GetAsyncKeyState(VK\_RBUTTON) & 0x8000)? 1: 0;	// Right Button
		m\_BtnCur[2] = (GetAsyncKeyState(VK\_MBUTTON) & 0x8000)? 1: 0;	// Middle Button

		for(nBtn=0; nBtn< 8; ++nBtn)
		{
			INT nOld = m\_BtnOld[nBtn];
			INT nCur = m\_BtnCur[nBtn];

			if	(0 == nOld && 1 ==nCur)	m\_BtnMap[nBtn] = EINPUT\_DOWN;	// Down
			else if	(1 == nOld && 0 ==nCur)	m\_BtnMap[nBtn] = EINPUT\_UP;	// Up
			else if	(1 == nOld && 1 ==nCur)	m\_BtnMap[nBtn] = EINPUT\_PRESS;	// Press
		}

		// 4. Update Mouse Position
		POINT pt;
		::GetCursorPos(&pt);
		::ScreenToClient(m\_hWnd, &pt);

		m\_vcOld.x = m\_vcCur.x;
		m\_vcOld.y = m\_vcCur.y;

		m\_vcCur.x = FLOAT(pt.x);
		m\_vcCur.y = FLOAT(pt.y);

		m\_vcEps = m\_vcCur - m\_vcOld;
		m\_vcOld.z = m\_vcCur.z;

		return 0;
	}
	…

	// Wheel Mouse 처리
	LRESULT CLcInput::MsgProc(HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam)
	{
		switch( msg )
		{
			case WM\_MOUSEWHEEL:
			{
				INT c= HIWORD(wParam);
				INT d= LOWORD(wParam);

				c = short( c );
				m\_vcCur.z += FLOAT(c);
				break;
			}
		}

		return 0;
	}

```

  
휠 마우스를 사용하려면 비주얼 스튜디오 6.0의 경우 windows.h 헤더 파일 include 전에
  
다음 매크로를 추가해야 합니다.
  


```

	#define \_WIN32\_WINNT 0x0400

```

  
이것은 휠 마우스는 운영체제가 NT 이상에서 처리되기 때문입니다.
  

  
좀 더 자세한 코드는 다음 예제를 참고 하기 바랍니다.
  

  
[Sp15\_Mouse.zip](https://github.com/3dapi/bs12_2d_app/raw/master/Sp15_Mouse.zip)
  

  

  
키보드, 마우스에 대해서 각각 따로 처리하지 않고 통합된 인풋 클래스를 다음 예제에
  
구현해 놓았으니 참고 하기 바랍니다.
  

  
[Sp15\_Input.zip](https://github.com/3dapi/bs12_2d_app/raw/master/Sp15_Input.zip)
  

  

  

  

  

  
## 2 응용 예제


  
### 2.1. 프레임 계산


  
프레임은 1초 동안 화면에 렌더링 하는 횟수로 진동수와 동일한 의미 입니다. 프레임이 크면
  
클수록 화면에 출력되는 일이 많으므로 이 프레임을 가지고 비디오 카드 사이의 성능을
  
비교한다던가 같은 그래픽 카드에서 프로그램의 성능을 비교할 때 사용합니다. 컴퓨터의
  
자원은 유한하므로 게임프로그래머는 제작하고 있는 게임이 컴퓨터에서 적절한 성능으로
  
운영되고 있는지 이 프레임을 가지고 체크 합니다.
  

  
프레임 계산에서 시간관련 함수가 필요한데 C언어에서 제공하는 함수도 있지만 윈도우 기반의
  
프로그램은 윈도우 API 함수를 이용합니다.
  
윈도우 API 함수 중에서 가장 많이 사용하는 함수가 GetTickCount()와 timeGetTime() 함수
  
입니다.
  
timeGetTime() 함수를 이용하려면 윈도우 미디어 라이브러리 winmm,lib 파일을 링크해주어야
  
하고 코드 를 작성할 때 mnsystem.h파일을 인클루드 해주어야 합니다.
  


```

	#pragma comment(lib, “winmm,lib”)
	#include < mnsystem.h>

```

  
GetTickCount()와 timeGetTime() 함수는 컴퓨터가 부팅 하고부터 시간을 milli-second(1/1000 초)
  
단위로 반환을 해주며 사용법은 다음과 같습니다.
  


```

	DWORD dBegin = timeGetTime();
	DWORD dBegin = GetTickCount();

```

  
프레임 값은 평균값을 주로 사용합니다. 평균값을 사용하는 이유는 프로그램도 음악의
  
LP 판처럼 동작 중에 갑자기 튈 때가 있습니다. 평균값을 이용하지 않으면 이 프레임을
  
가지고 애니메이션을 처리할 경우 캐릭터의 동작도 같이 튀게 되게 되는데 이럴 경우
  
게임을 하는 유저들을 굉장히 피곤하게 만들게 됩니다.
  

  
보통 8~10번 렌더링 한 후에 계산하기도 하고 프레임은 원칙적으로 초당 렌더링 횟수 이므로
  
1초 정도 렌더링 한 후 이 횟수를 사용하기도 합니다.
  
다음은 30을 평균 길이로 정하고 프레임을 계산하는 코드 입니다.
  


```

	void CD3DApp::UpdateFrame()
	{
		static int	iCnt =0;
		static DWORD	dB = timeGetTime();
		DWORD	dE = timeGetTime();

		++iCnt;

		if(iCnt>30)	// 30Frame을 기준
		{
			m\_fFps = FLOAT(dE-dB);
			m\_fFps = iCnt*1000/m\_fFps;

			iCnt = 0;
			dB = dE;
		}
	}

```

  
GetTickCount() 함수와 timeGetTime() 함수는 이후 3D 게임에서 시간관련 로직에서도
  
종종 사용하고 있느니 잘 기억하기 바랍니다.
  

  
GetTickCount() 함수와 timeGetTime() 함수 이외에 QueryPerformenceCounter() 함수와
  
QueryPerformanceFrequency() 함수를 사용해서 시간을 구하기도 합니다. 이 함수는
  
timeGetTime() 함수보다 더 정밀한 1/10000000 초 값을 계산해 주는데 이 함수를 사용하기
  
위해서는 CPU가 지원하는지 확인해야 합니다. 다행히 QueryPeeformanceFrequency() 함수의
  
리턴 값을 가지고 CPU 지원 여부를 확인할 수 있습니다.
  
게임 제작에서 1/10000000 초 정밀도를 요구하는 경우는 거의 없으므로 이 부분에 대한
  
구현은 3D 강의에서 다시 진행하겠습니다.
  

  
다음은 timeGetTime() 함수를 이용해서 프레임을 계산하는 예제입니다.
  

  
[Sp21\_Frame.zip](https://github.com/3dapi/bs12_2d_app/raw/master/Sp21_Frame.zip)
  

  

  

  

  

  
### 2.2. ID3DXSprite 와 행렬


  
2D 기초과정에서 ID3DXSprite 객체의 Draw() 함수를 사용해 보았습니다. 만약 렌더링에서
  
회전과 크기 변환이 있는 경우에는 행렬을 사용해야 합니다.
  
행렬을 사용하기 위해서 다음과 같이 D3DXMATRIX 구조체를 이용합니다.
  


```

	D3DXMATRIX	mtW;

```

  
행렬의 초기화는 행렬을 항등 행렬(또는 단위 행렬)이라 부르는 정방행렬 중에서 주 대각이
  
1이고 나머지가 0인 값을 가지는 행렬로 만듭니다.
  
항등행렬의 특성은 행렬의 연산 중에서 행렬 곱에서 주어진 행렬과 항등 행렬을 곱하면
  
그 곱하는 순서에 상관 없이 결과가 주어진 행렬 값과 동일한 결과를 만들어 냅니다.
  

  
위의 행렬을 항등 행렬을 만들기 위해 다음과 같이 DirectX에 있는 함수를 이용합니다.
  


```

	D3DXMatrixIdentity(&mtW);

```

  
만약 크기와 위치가 있는 경우라면 행렬을 만들고, 스프라이트(ID3DXSprite) 객체의
  
SetTransform() 함수를 호출해서 스프라이트의 세계 행렬(World Matrix)을 설정한 후에
  
Draw() 함수를 호출 합니다. Draw() 함수를 호출하고 나서 더 이상 렌더링이 없다면
  
다시 항등 행렬을 스프라이트 객체에 설정합니다. 구체적인 코드는 다음과 같습니다.
  


```

	D3DXMATRIX	mtW;
	D3DXMatrixIdentity(&mtW);

	mtW.\_11 =  Scaling.x;
	mtW.\_22 =  Scaling.y;
	mtW.\_41 =  Position.x;
	mtW.\_42 =  Position.y;
	m\_pd3dSprite->SetTransform(&mtW);

	m\_pd3dSprite->Draw(pTex1, &rc1, NULL, NULL, D3DXCOLOR(1,1,1,1));

	D3DXMatrixIdentity(&mtW);
	m\_pd3dSprite->SetTransform(&mtW);

```

  
다음은 간단하게 행렬을 이용해서 텍스처를 출력하는 예제입니다.
  

  
[Sp22\_Draw.zip](https://github.com/3dapi/bs12_2d_app/raw/master/Sp22_Draw.zip)
  

  

  
만약 크기 변환과 회전과 이동까지 포함하는 경우라면 조금 복잡해 집니다. 이 경우에는
  
크기 변환, 회전, 이동, 회전 중심 위치 등에 대해서 행렬을 만든 후에 다음의 공식대로
  
행렬을 곱해서 최종 행렬을 만들어 냅니다.
  


```

	최종 행렬 = 크기변환 행렬 * 회전 중심 역 행렬 * 회전 행렬 * 회전 중심 행렬 * 이동 행렬

```

  
크기 변환 행렬은 D3DXMatrixScaling() 함수를 이용합니다.
  
역 행렬은 D3DXMatrixInverse() 함수를 이용합니다.
  

  
회전 행렬은 여러 가지가 있는데 2D의 경우 회전 중심 축은 DirectX를 기준으로
  
볼 때 -Z 축입니다.
  
이에 대한 행렬이 D3DXMatrixRotationZ() 함수 이며 각도는 라디안(Radian)이고 -Z 축으로
  
회전해야 하므로 각도를 -(음수) 값을 곱해서 입력합니다.
  

  
이동에 대한 행렬은 D3DXMatrixTranslation() 함수를 사용합니다.
  

  
만약 크기 변환, 회전 중심, 회전 각, 이동 값이 주어진다면 이것을 매번 행렬로 만드는 일은
  
비효율적이므로 함수를 사용하거나 객체를 만들어서 다음과 같이 처리합니다.
  


```

	INT CLcSprite::Draw(LPDIRECT3DTEXTURE9 pTex
				, const RECT* pSrcRect
				, const D3DXVECTOR2* pScaling		// Scaling
				, const D3DXVECTOR2* pCenter		// Rotation Center
				, FLOAT	fAngle				// Degree
				, const D3DXVECTOR2* pPosition		// Translation
				, D3DCOLOR Color
				)
	{
		m\_pDxSprite->Begin(D3DXSPRITE\_ALPHABLEND);

		D3DXMATRIX mtW;
		D3DXMatrixIdentity(&mtW);

		FLOAT			fTheta = D3DXToRadian(fAngle);
		D3DXMATRIX		mtScl;		// Scaling Matrix
		D3DXMATRIX		mtRot;		// Rotation Matrix
		D3DXMATRIX		mtTrn;		// Translation Matrix
		D3DXMATRIX		mtRct;		// Rotation Center Matrix
		D3DXMATRIX		mtRctI;		// Rotation Center Matrix Inverse

		D3DXMatrixIdentity(&mtScl);
		D3DXMatrixIdentity(&mtRct);
		D3DXMatrixIdentity(&mtRot);
		D3DXMatrixIdentity(&mtTrn);
		D3DXMatrixIdentity(&mtRctI);

		if(pScaling)
			D3DXMatrixScaling(&mtScl, pScaling->x, pScaling->y, 1);


		D3DXMatrixRotationZ(&mtRot, -fTheta);


		if(pCenter)
			D3DXMatrixTranslation(&mtRct, pCenter->x, pCenter->y, 0);

		//	D3DXMatrixInverse(&mtRctI, NULL, &mtRct);
		if(pCenter)
			D3DXMatrixTranslation(&mtRctI, -pCenter->x, -pCenter->y, 0);


		if(pPosition)
		D3DXMatrixTranslation(&mtTrn, pPosition->x, pPosition->y, 0);


		mtW =  mtScl * mtRctI * mtRot * mtRct * mtTrn;


		m\_pDxSprite->SetTransform(&mtW);
		m\_pDxSprite->Draw(pTex, pSrcRect, NULL, NULL, Color);

		D3DXMatrixIdentity(&mtW);
		m\_pDxSprite->SetTransform(&mtW);

		m\_pDxSprite->End();

		return 0;
	}

```

  
위의 코드는 스프라이트를 편리하게 사용하기 위해서 D3DXVECTOR3 구조체를 사용하지 않고
  
D3DXVECTOR2 구조체를 이용했습니다. 또한 DirectX는 각도를 Radian을 이용하는데 대부분
  
Radian보다 Degree가 익숙하므로 Degree 값을 대입하면 내부적으로 Radian으로 바꾸도록
  
만들었습니다.
  
이 외에 스프라이트의 Begin()/End() 함수를 외부에서 호출하지 않아도 내부에서 처리하도록
  
코드를 만들었습니다.
  

  
이 객체를 만들고 사용하는 예는 CMain::Render() 함수에서 다음과 같이 사용합니다.
  


```

	m\_pLcSprite->Draw(pTex1, &rc1, NULL, NULL, 0, &D3DXVECTOR2(50, 50), D3DXCOLOR(1,1,1,1));

	vcPos.x = 100 + (rc1.right - rc1.left) * 1.f;
	vcPos.y =  50 + (rc1.bottom - rc1.top) * 1.f;

	m\_pLcSprite->Draw(pTex1	, &rc1, &D3DXVECTOR2(0.5f, 0.5f)
			, NULL, 0, &vcPos, D3DXCOLOR(1,1,1,1));

```

  

  
전체 코드는 다음 예제를 살펴보기 바랍니다.
  

  
[Sp22\_Draw\_class.zip](https://github.com/3dapi/bs12_2d_app/raw/master/Sp22_Draw_class.zip)
  

  

  

  

  

  
### 2.3. 스프라이트와 텍스처


  
지금까지 과정을 종합하는 의미에서 CLcTexture 클래스와 CLcSprite 클래스 두 클래스를
  
이용한 간단 텍스처 예제를 만들어 봅시다.
  
텍스처 소스는 인터넷에서 얻은 수퍼 마리오 텍스처를 변형 해서 만들었습니다. 다음 예제의
  
코드의 설명은 안 하겠습니다. 각자 해석해 봅시다.
  

  
[Sp23\_Tex\_Ani.zip](https://github.com/3dapi/bs12_2d_app/raw/master/Sp23_Tex_Ani.zip)
  

  

  

  

  

  
### 2.4. 풀 모드(Full Mode)와 윈도우 모드(Window Mode)


  
화면 전체를 독점적으로 사용하는 풀 모드와 다른 프로그램과 나누어 사용하는 윈도우 모드를
  
설정해 봅시다. 보통 게임 프로그램은 풀 모드에서 동작을 합니다. 게임프로그램이 진행 되고
  
있는 동안 윈도우의 이벤트가 발생해서 비활성화 되면 풀 모드를 해제하고 윈도우 모드나
  
최소화 상태로 있어야 합니다. 이렇게 모드가 변경될 경우 “장치는 로스트(Lost) 된다.
  
”라고 하며 다시 장치를 설정(Reset)해야 합니다.
  

  
모드의 변경이 일어나면 장치의 present() 함수는 DEVICE\_LOST 값을 돌려 줍니다. 따라서
  
매 번 렌더링 하면서 이 값을 확인해서 디바이스가 로스트 되면 장치를 리셋을 해야 합니다.
  
리셋이 제대로 이행 됐는지 확인하기 위해 장치의 멤버 함수 중에서 TestCooperativeLevel()
  
함수를 호출합니다.
  


```

	HRESULT hr= m\_pd3dDevice->Present( NULL, NULL, NULL, NULL);

	if( D3DERR\_DEVICELOST == hr )
		m\_bDeviceLost = TRUE;


	if( m\_bDeviceLost )
	{
	if( FAILED( hr = m\_pd3dDevice->TestCooperativeLevel() ) )
		{
			if( D3DERR\_DEVICENOTRESET == hr )
			{
				Reset();
			}

			else if( D3DERR\_DEVICELOST == hr )
			{
			}
		}
		else
			m\_bDeviceLost = FALSE;
	}
	…

	INT Reset()
	{
		D3DDISPLAYMODE d3ddm;
		if( FAILED( m\_pD3D->GetAdapterDisplayMode( D3DADAPTER\_DEFAULT, &d3ddm ) ) )
			return -1;

		m\_bWindow ^= 1;

		memset(&m\_d3dpp, 0, sizeof m\_d3dpp);

		m\_d3dpp.Windowed			= m\_bWindow;
		m\_d3dpp.SwapEffect			= D3DSWAPEFFECT\_DISCARD;
		m\_d3dpp.BackBufferFormat		= D3DFMT\_X8R8G8B8;
		m\_d3dpp.BackBufferWidth			= m\_dScnX;
		m\_d3dpp.BackBufferHeight		= m\_dScnY;
		m\_d3dpp.EnableAutoDepthStencil		= TRUE;
		m\_d3dpp.AutoDepthStencilFormat		= D3DFMT\_D16;
		m\_d3dpp.FullScreen\_RefreshRateInHz	= m\_bWindow? 0 : d3ddm.RefreshRate;

		hr = m\_pd3dDevice->Reset(&m\_d3dpp);

		return 0;
	}

```

  
다시 정리한다면 다음과 같습니다.
  

  
present() 함수의 리턴 값 확인 -> 로스트면 장치의 Reset()함수 호출
  
-> 리셋 되었는지 TestCooperativeLevel() 함수로 확인
  

  
좀 더 자세한 코드는 다음 예제를 이용하기 바랍니다.
  

  
[Sp24\_TestCoop.zip](https://github.com/3dapi/bs12_2d_app/raw/master/Sp24_TestCoop.zip)
  

  

  
DirectX의 객체 들 중에 일부는 모드 변환에서 장치처럼 Set/Reset을 설정 해야 합니다.
  
특히, ID3DXFont 객체와 ID3DXSprite 객체가 그러한데 이들의 객체들은 Reset의 경우
  
OnResetDevice() 함수를 통해서 설정하고, 장치를 잃어버리는 로스트(Lost) 상황이라면
  
OnLostDevice() 함수를 호출 합니다.
  


```

	m\_pD3DXFont->OnResetDevice();
	…
	m\_pD3DXFont->OnLostDevice();

```

  
다음의 예제는 ID3DXSprite 객체, ID3DXFont 객체, 그리고 풀 모드와 윈도우 모드에 대한
  
예제입니다.
  

  
[Sp25\_Swith\_Scn.zip](https://github.com/3dapi/bs12_2d_app/raw/master/Sp25_Swith_Scn.zip)
  

  

  

  

  

  
## 3 기타


  
### 3.1. 직사각형 충돌


  
2D게임에서 가장 많이 사용하는 충돌 검사 방식은 원과 직사각형 충돌입니다. 특히 직사각형
  
충돌은 다음의 의사 코드와 같이 별다른 수학 연산이 필요 없이 가장 빠르게 충돌을 검사합니다.
  


```

	RECT rcCol1;
	RECT rcCol2;

	if(	rcCol1.left  < = rcCol2.right &&
		rcCol1.right > = rcCol2.left  &&
		rcCol1.top   < = rcCol2.bottom &&
		rcCol1.bottom > = rcCol2.top )
	{
		충돌;
	}

```

  
![](https://github.com/3dapi/bs12_2d_app/raw/master/img_src/Sp31_Coll_rect.png)
  

  
다음 예제는 충돌 박스를 그림으로 표현한 예제입니다.
  

  
[Sp31\_Coll\_rect.zip](https://github.com/3dapi/bs12_2d_app/raw/master/Sp31_Coll_rect.zip)
  

  

  

  

  

  
### 3.2. 직선 충돌


  
직선 충돌은 외적을 이용 하면 편리합니다. 두 직선의 충돌을 보면 다음 그림과 같은 상황입니다.

  
![](https://github.com/3dapi/bs12_2d_app/raw/master/img_src/Sp32_Coll_line2.png)
  
한 평면 위에 있는 두 개의 직선이 충돌한 조건은 외적으로 다음 수식으로 표현될 수 있습니다.

  
![](https://github.com/3dapi/bs12_2d_app/raw/master/img_src/Sp32_Coll_line3.png)
  

  
2차원의 경우 외적을 사용할 수 없지만 화면을 뚫고 지나가는 z 축이 있다고 가정한다면
  
두 직선 L1, L2의 외적의 값은 L0.x * L1.y - L0.y * L1.x 으로 정할 수 있고 이것을 충돌 조건에
  
대입하면 다음과 같이 충돌 함수를 만들 수 있습니다.

```

int CollisionLineToLine(const D3DXVECTOR2* v1, const D3DXVECTOR2* v2)
{
	D3DXVECTOR2 L0 = v2[0] - v1[0];
	D3DXVECTOR2 L1 = v1[1] - v1[0];
	D3DXVECTOR2 L2 = v2[1] - v1[0];

	D3DXVECTOR2 L3 = v1[0] - v2[0];
	D3DXVECTOR2 L4 = v2[1] - v2[0];
	D3DXVECTOR2 L5 = v1[1] - v2[0];

	FLOAT	D1;
	FLOAT	D2;

	D1 = (L0.x * L1.y - L0.y * L1.x) * (L1.x * L2.y - L1.y * L2.x);
	D2 = (L3.x * L4.y - L3.y * L4.x) * (L4.x * L5.y - L4.y * L5.x);

	if(  D1>0 && D2 >0)
		return 0;

	return -1;
}

```

  
![](https://github.com/3dapi/bs12_2d_app/raw/master/img_src/Sp32_Coll_line.png)
  

  
다음 예제는 두 직선 충돌을 구하는 예제입니다.
  

  
[Sp32\_Coll\_line.zip](https://github.com/3dapi/bs12_2d_app/raw/master/Sp32_Coll_line.zip)
  

  

  

  

  

  
### 3.2. 추적


  
추적의 원리는 태양계 행성의 운동과 비슷합니다. 추적의 대상이 위치를 바꾸면 그에 대한
  
방향으로 조금씩 바꾸어 가면서 방향을 설정합니다. 그리 어려운 내용이 아니라서 설명을
  
생략하겠습니다. 추적에 관한 코드는 다음 예제를 살펴보기 바랍니다.
  

  
[Sp33\_Chase.zip](https://github.com/3dapi/bs12_2d_app/raw/master/Sp33_Chase.zip)
  

  
[Sp31\_particle.zip](https://github.com/3dapi/bs12_2d_app/raw/master/Sp31_particle.zip)
  

  

  

  

  

  
### 3.4. 그림자


  
2D 게임에서 재미있는 주제가 그림자 입니다. 그림자는 대부분 그래픽 디자이너가 만들어
  
주지만 때로는 프로그램에서 처리할 경우도 있습니다.
  
그림자를 만드는 방법은 간단합니다. 실시간으로 그림자 텍스처를 원본 이미지의 크기와
  
동일하게 만든 다음, 원본 이미지의 픽셀을 불러와서 원본 이미지의 R, G, B 값을 가지고
  
다음과 같은 공식을 이용해서 그림자 색상에 적용합니다.
  


```

	I = 0.30 * R + 0.59 * G + 0.11 * B
	최종 색상 = RGB(I, I, I)

```

  
실시간 텍스처를 만들기 위해서 D3DXCreateTexture() 함수를 다음과 같이 사용합니다.
  


```

	D3DXCreateTexture(m\_pd3dDevice, ImgW, ImgH, 1, 0
		, dsc.Format, D3DPOOL\_MANAGED, &m\_pTexAniS);

```

  
텍스처의 색상을 값을 가져오기 위해 텍스처 객체의 멤버 함수 LockRect()/UnlockRect() 함수를 다음과 같이 이용합니다.
  


```

	D3DSURFACE\_DESC dsc;
	D3DLOCKED\_RECT	drc;
	DWORD*	pColorSrc= NULL;
	DWORD*	pColorDst= NULL;

	LPDIRECT3DTEXTURE9	pTexAni = m\_pTexAni->GetTexture();

	pTexAni->GetLevelDesc(0, &dsc);

	INT ImgW	= dsc.Width;
	INT ImgH	= dsc.Height;
	m\_pTexAniS	= NULL;

	pColorSrc	= new DWORD[ImgW * ImgH];

	// 임시 버퍼에 칼라 값들을 복사한다.
	pTexAni->LockRect(0, &drc, NULL, 0);
	{
		memcpy(pColorSrc, drc.pBits, ImgW * ImgH * sizeof(DWORD));
	}
	pTexAni->UnlockRect(0);

```

  
위에서 픽셀의 포맷, 텍스처 폭, 높이 같은 정보를 얻기 위해 GetLevelDesc() 함수를
  
사용했습니다.
  
그 다음으로 복사한 색상 값들을 이용해서 흑백 이미지를 만듭니다.
  


```

	m\_pTexAniS->LockRect(0, &drc, NULL, 0);
	{
		pColorDst = (DWORD*)drc.pBits;
		McColor\_TransColorMono(pColorDst, pColorSrc, ImgW, ImgH);
	}
	m\_pTexAniS->UnlockRect(0);

```

  
LockRect() 함수는 다른 프로세스가 간섭하지 못하도록 독점 모드 동작과 픽셀 정보를
  
가져옵니다.
  
이 때 픽셀 데이터는 void형 포인터 되어 있는데 이것을 GetLevelDesc() 함수를 통해 얻은
  
픽셀 포맷 정보를 가지고 알맞은 크기로 캐스팅 해야 합니다. 예를 들어 포맷이
  
D3DFMT\_X8R8G8B8은 32비트로, D3DFMT\_R8G8B8은 24비트로, D3DFMT\_X1R5G5B5는 16비트로
  
캐스팅해야 합니다. 일반적으로 텍스처는 32비트 ARGB를 사용하므로 위에서는 DWORD형으로
  
캐스팅했습니다.
  


```

	void McColor\_TransColorMono(DWORD* pOut, DWORD* pIn, INT iImgW, INT iImgH)
	{
		for(int y=0; y< iImgH; ++y)
		{
			for(int x=0; x< iImgW; ++x)
			{
				int nIdx = y*iImgW + x;

				D3DXCOLOR c = pIn[nIdx];

				//I = 0.30R + 0.59G + 0.11B
				float I = c.r * 0.3f + c.g * 0.59f + c.b * 0.11f;
				pOut[nIdx] = D3DXCOLOR(I, I, I, c.a);
			}
		}
	}

```

  
![](https://github.com/3dapi/bs12_2d_app/raw/master/img_src/Sp34_Shadow.png)
  

  
이렇게 흑백 이미지를 만들고 나면 원본 이미지 밑에 출력하면 그림자 효과가 완성이 됩니다.
  
좀더 자세한 내용은 다음 코드를 참고 하기 바랍니다.
  

  
[Sp34\_Shadow.zip](https://github.com/3dapi/bs12_2d_app/raw/master/Sp34_Shadow.zip)
  

  

  

  

  

  
### 3.5. 소코반 게임


  
게임개발자가 자신의 스킬을 레벨업하는 방법 중에 가장 빠른 방법은 게임을 많이 많이 만들어
  
보는 것입니다. 아래 게임은 위의 내용을 토대로 만든 2D 소코반 게임입니다.
  
(제작:청강문화산업대학 장청명)
  

  
![](https://github.com/3dapi/bs12_2d_app/raw/master/img_src/Sp35_sokoban.png)
  

  
[Sp35\_sokoban.zip](https://github.com/3dapi/bs12_2d_app/raw/master/Sp35_sokoban.zip)
  


php
 include '../base/lc\_tail.php';
?
