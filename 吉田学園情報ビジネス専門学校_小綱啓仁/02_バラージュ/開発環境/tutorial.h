//=============================================================================
//
// tutorial.h
// Author : koduna hirohito
//
//=============================================================================
#ifndef _TUTORIAL_H_			//このマクロ定義がされなかったら
#define _TUTORIAL_H_			//2重インクルード防止のマクロ定義

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "object.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CUI;
class C2DPolygon;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CTutorial : public CObject
{
private:
public:
	CTutorial();
	~CTutorial() override;

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

private:
	C2DPolygon *m_pPressKeyPolygon;
	CUI *m_pUi;
};

#endif