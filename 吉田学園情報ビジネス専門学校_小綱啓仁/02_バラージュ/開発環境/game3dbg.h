//=============================================================================
//
// game3dbg.h
// Author : koduna hirohito
//
//=============================================================================
#ifndef _GAME3DBG_H_			//���̃}�N����`������Ȃ�������
#define _GAME3DBG_H_			//2�d�C���N���[�h�h�~�̃}�N����`

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "main.h"
#include "3dbg.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class C3DObject;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CGame3DBG : public C3DBG
{
private:
	static const int Z_MAX_3DBG_MODEL = 6;
	static const int X_MAX_3DBG_MODEL = 3;
	static const D3DXVECTOR3 STANDARD_3DBG_MODEL;

public:
	CGame3DBG();
	~CGame3DBG() override;

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

private:
	C3DObject *m_pBgModel[X_MAX_3DBG_MODEL][Z_MAX_3DBG_MODEL];
	D3DXVECTOR3 m_BgObjSize;
	D3DXVECTOR3 m_Move;
};

#endif