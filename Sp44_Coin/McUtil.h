// Interface for the Utilities.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef _MCUTIL_H_
#define _MCUTIL_H_

#define SAFE_DELETE(p)       { if(p) { delete (p);     (p)=NULL; } }
#define SAFE_DELETE_ARRAY(p) { if(p) { delete[] (p);   (p)=NULL; } }
#define SAFE_RELEASE(p)      { if(p) { (p)->Release(); (p)=NULL; } }


#define SAFE_NEWINIT(p, CLASSTYPE)												\
{																				\
	if(NULL == (p))																\
	{																			\
		p = new CLASSTYPE;														\
																				\
		if(!(p))																\
		{																		\
			return -1;															\
		}																		\
																				\
		if(FAILED((p)->Init()))													\
		{																		\
			delete p;															\
			p = NULL;															\
			return -1;															\
		}																		\
	}																			\
}

#define SAFE_FRAMEMOVE(p)														\
{																				\
	if(p)																		\
	{																			\
		if(FAILED(	(p)->FrameMove()))											\
			return -1;															\
	}																			\
}

#define SAFE_DESTROY(p)		{	if(p)	(p)->Destroy();			}
#define SAFE_INVALIDATE(p)	{	if(p)	(p)->Invalidate();		}
#define SAFE_RENDER(p)		{	if(p)	(p)->Render();			}


INT	McUtil_TextureLoad(LPDIRECT3DDEVICE9 pDev
						, TCHAR* sFile
						, LPDIRECT3DTEXTURE9& pTx
						, D3DXIMAGE_INFO* pInf
						, DWORD dc= 0x00FFFFFF);


#endif