//=============================================================================
//
// title.h
// Author : koduna hirohito
//
//=============================================================================
#ifndef _TITLE_H_			//���̃}�N����`������Ȃ�������
#define _TITLE_H_			//2�d�C���N���[�h�h�~�̃}�N����`

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "object.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CUI;
class CTitle3DBG;
class CCamera;
class CLight;
class C3DPolygon;
class C2DPolygon;
class CRanking;
class CRead;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CTitle : public CObject
{
private:
	static const int RANKING_CNT_MAX = 1320;
public:
	CTitle();
	~CTitle() override;

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

private:
	C2DPolygon *m_pPressKeyPolygon;
	float m_fPressKeyPolygonColorA;
	CCamera *m_pCamera;
	CTitle3DBG *m_pBGObj;
	CUI *m_pTitlePolygon;
	CLight *m_pLight;
	C3DPolygon *m_pBG;
	CRanking *m_pRanking;
	CRead *m_pRead;
	int m_nRankingCnt;
	bool m_bRanking;
};

#endif