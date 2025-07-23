//
////////////////////////////////////////////////////////////////////////////////


#ifndef _GameObject_H_
#define _GameObject_H_


#ifndef interface
#define struct interface
#endif

interface IGameObject
{
	virtual ~IGameObject(){};

	virtual int		Create() = 0;
	virtual void	Destroy() = 0;

	virtual int		FrameMove() = 0;
	virtual void	Render() = 0;

	virtual	int		SetModel(char* sModel)=0;
	virtual	void	SetPos(const FLOAT*)=0;
};



class CGameObject : public IGameObject
{
protected:
	D3DXVECTOR3		m_vcPos;
	IGameModel*		m_pModel;

public:
	CGameObject();
	virtual ~CGameObject();

	virtual int		Create();
	virtual void	Destroy();

	virtual int		FrameMove();
	virtual void	Render();

	virtual	int		SetModel(char* sModel);
	virtual	void	SetPos(const FLOAT* pPos);
};



#endif


