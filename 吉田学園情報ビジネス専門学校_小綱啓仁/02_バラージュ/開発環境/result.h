//=============================================================================
//
// Result.h
// Author : koduna hirohito
//
//=============================================================================
#ifndef _RESULT_H_			//���̃}�N����`������Ȃ�������
#define _RESULT_H_			//2�d�C���N���[�h�h�~�̃}�N����`

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "object.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CUI;
class CRanking;
class CRead;
class CRankingInput;
class CCamera;
class CLight;
class C3DBG;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CResult : public CObject
{
public:
	CResult();
	~CResult() override;

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	CRanking *GetRanking() { return m_pRanking; }
	CRead *GetRead() { return m_pRead; }

private:
	CUI *m_pResultPolygon;
	CRanking *m_pRanking;
	CRead *m_pRead;
	CRankingInput *m_pRankingInput;
	CCamera *m_pCamera;
	C3DBG *m_pBGObj;
	CLight *m_pLight;
	bool m_bEnd;
};

#endif