//
////////////////////////////////////////////////////////////////////////////////


#ifndef _GameTexture_H_
#define _GameTexture_H_


#ifndef interface
#define struct interface
#endif

interface IGameTexture
{
	enum EGameTexture
	{
		FILE	= 1,
		RESOURCE = 2,
		MEMORY	= 3,
	};

	virtual ~IGameTexture(){};

	virtual int		Create(void* TextureName, DWORD dColorKey) = 0;
	virtual void	Destroy() = 0;

	virtual int		GetImageWidth() = 0;
	virtual int		GetImageHeight() = 0;
	virtual void*	GetTexture() = 0;

	virtual const char*	GetName() = 0;
};


void	LpDev_TextureInit(void* pDev);
int		LpDev_TextureCreate(int nOpt, IGameTexture** pData, void* pTextureName, DWORD dColorKey);



#endif

