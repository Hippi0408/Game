//=============================================================================
//
// stageselect.h
// Author : koduna hirohito
//
//=============================================================================
#ifndef _STAGE_SELECT_H_			//このマクロ定義がされなかったら
#define _STAGE_SELECT_H_			//2重インクルード防止のマクロ定義

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "object.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CUI;
class CRead;
class CCamera;
class CLight;
class CStageSelect3DBG;
class C2DPolygon;
enum StageNum;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CStageSelect : public CObject
{
private:
	static const int MAX_STAGE = 6;
	static const float SIZE_UI;
	static const float SIZE_UI_HALF;

	static const int MAX_PL_AIRFRAME = 3;
	static const float SIZE_AIRFRAME_UI;
	static const float SIZE_AIRFRAME_UI_HALF;

	static const float OBJ_DISTANCE;

	static const int SELECTION_COOL_TIME = 38;

	static const int ARROW_MAX = 2;
	static const float ARROW_WIDTH_LEFT_RIGHT;
	static const float ARROW_WIDTH_UP_AND_DOWN;
	static const float ARROW_ADD_WIDTH;
	static const int ARROW_ADD_WIDTH_CNT_MAX = 30;
public:
	CStageSelect();
	~CStageSelect() override;

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

private:
	CUI *m_pUi;
	C2DPolygon *m_pMessageBoxUI;
	C2DPolygon *m_pStageNameUI;
	C2DPolygon *m_pPlayerUI;
	C2DPolygon *m_pArrowLeftRightUI[ARROW_MAX];
	C2DPolygon *m_pArrowUpDownUI[ARROW_MAX];
	CRead *m_pRead;
	CCamera *m_pCamera;
	CStageSelect3DBG *m_pBGObj;
	CLight *m_pLight;
	int m_nStage;
	int m_nAirframe;
	int m_nNotTouchCnt;
	bool m_bDetermination;
	int m_nSelectionCnt;
	float m_fAddArrow;
	int m_nAddArrowCnt;
};

#endif