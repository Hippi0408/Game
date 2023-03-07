//=============================================================================
//
// stageselect3dbg.h
// Author : koduna hirohito
//
//=============================================================================
#ifndef _STAGE_SELECT_3DBG_H_			//���̃}�N����`������Ȃ�������
#define _STAGE_SELECT_3DBG_H_			//2�d�C���N���[�h�h�~�̃}�N����`

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
class CStageSelect3DBG : public C3DBG
{
private:
	static const D3DXVECTOR3 STANDARD_3DBG_MODEL;
	static const float PLANET_BETWEEN_DISTANCE;
public:
	CStageSelect3DBG();
	~CStageSelect3DBG() override;

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	void AddDestPos(float fAdd) { m_DestObjPos.x += fAdd; }
	void AddPos(float fAdd);
	void SetPos(D3DXVECTOR3 pos);

private:
	C3DObject *m_pBgModel[StageNum_MAX];
	D3DXVECTOR3 m_ObjPos;
	D3DXVECTOR3 m_DestObjPos;
	D3DXVECTOR3 m_Rotation[StageNum_MAX];		//���]
	D3DXVECTOR3 m_RotationMove[StageNum_MAX];		//���]���x
	D3DXVECTOR3 m_BgObjSize;
	D3DXVECTOR3 m_Move;
	CRead *m_pRead;
	C3DPolygon *m_pBG;

};

#endif