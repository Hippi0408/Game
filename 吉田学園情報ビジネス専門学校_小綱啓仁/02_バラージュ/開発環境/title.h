//=============================================================================
//
// title.h
// Author : koduna hirohito
//
//=============================================================================
#ifndef _TITLE_H_			//このマクロ定義がされなかったら
#define _TITLE_H_			//2重インクルード防止のマクロ定義

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "object.h"

//*****************************************************************************
// 前方宣言
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
// クラス定義
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