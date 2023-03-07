//=============================================================================
//
// warning.h
// Author : koduna hirohito
//
//=============================================================================
#ifndef _WARNING_H_			//このマクロ定義がされなかったら
#define _WARNING_H_			//2重インクルード防止のマクロ定義

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "main.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class C2DPolygon;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CWarning
{
private:
	static const int MAX_WARNING = 4;
	static const D3DXVECTOR3 WARNING_POS[MAX_WARNING];
	static const D3DXVECTOR3 WARNING_ROT[MAX_WARNING];
	static const D3DXVECTOR2 WARNING_SISE[MAX_WARNING];

public:
	CWarning();
	~CWarning();

	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();

	bool GetWarning() { return m_bWarning; }
	void SetWarning() { m_bWarning = true; }
	bool OutWarning();

private:
	C2DPolygon *m_pWarning[MAX_WARNING];
	C2DPolygon *m_pRedFade;
	bool m_bWarning;
};

#endif