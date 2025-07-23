//
////////////////////////////////////////////////////////////////////////////////

#include <vector>

using namespace std;

#include <windows.h>

#include <d3d9.h>
#include <d3dx9.h>

#include "GameTexture.h"
#include "GameModel.h"

#include "GameObject.h"


CGameObject::CGameObject()
{
	m_pModel	= NULL;
	m_vcPos		= D3DXVECTOR3(0,0,0);
}


CGameObject::~CGameObject()
{
	Destroy();
}


void CGameObject::Destroy()
{
	if(m_pModel)
	{
		delete m_pModel;
		m_pModel = NULL;
	}
}


void CGameObject::SetPos(const FLOAT* pPos)
{
	memcpy(&m_vcPos, pPos, sizeof(D3DXVECTOR3));
}


int CGameObject::Create()
{
	return 0;
}


int CGameObject::FrameMove()
{
	if(m_pModel)
	{
		m_pModel->SetPos(m_vcPos);
		m_pModel->FrameMove();
	}

	return 0;
}


void CGameObject::Render()
{
	if(m_pModel)
		m_pModel->Render();
}



int CGameObject::SetModel(char* sModel)
{
	if(FAILED(LpDev_ModelCreate(IGameTexture::FILE, &m_pModel, sModel)))
		return -1;

	return 0;
}