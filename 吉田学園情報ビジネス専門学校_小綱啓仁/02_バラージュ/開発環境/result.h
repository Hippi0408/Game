//=============================================================================
//
// Result.h
// Author : koduna hirohito
//
//=============================================================================
#ifndef _RESULT_H_			//このマクロ定義がされなかったら
#define _RESULT_H_			//2重インクルード防止のマクロ定義

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "object.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CUI;
class CRanking;
class CRead;
class CRankingInput;
class CCamera;
class CLight;
class C3DBG;

//*****************************************************************************
// クラス定義
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