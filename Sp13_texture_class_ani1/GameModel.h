//
////////////////////////////////////////////////////////////////////////////////


#ifndef _GameModel_H_
#define _GameModel_H_


#ifndef interface
#define struct interface
#endif

interface IGameModel
{
	virtual ~IGameModel(){};

	virtual int		Create(void* pSprite, void* ModelName) = 0;
	virtual void	Destroy() = 0;

	virtual int		FrameMove() = 0;
	virtual void	Render() = 0;
	

	virtual void	SetAnimation(int) = 0;
	virtual int		GetAnimation() = 0;

	virtual void	Play() = 0;
	virtual void	Stop() = 0;


	virtual	void	SetPos(const FLOAT*)=0;
	virtual	void	SetColor(const DWORD)=0;
};


int LpDev_ModelCreate(int nOpt, IGameModel** pData, void* pSprite, void* pModelName);


#endif


