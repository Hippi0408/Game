//=============================================================================
//
// result3dbg.h
// Author : koduna hirohito
//
//=============================================================================
#ifndef _RESULT_3DBG_H_			//���̃}�N����`������Ȃ�������
#define _RESULT_3DBG_H_			//2�d�C���N���[�h�h�~�̃}�N����`

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "main.h"
#include "3dbg.h"
#include "manager.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class C3DObject;
class CRead;
class C3DPolygon;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CResult3DBG : public C3DBG
{
private:
	static const D3DXVECTOR3 STANDARD_3DBG_MODEL;
public:
	CResult3DBG();
	~CResult3DBG() override;

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

private:
	C3DObject *m_pBgModel;
	D3DXVECTOR3 m_Rotation;		//���]
	D3DXVECTOR3 m_RotationMove;		//���]���x
	CRead *m_pRead;
	C3DPolygon *m_pBG;

};

#endif