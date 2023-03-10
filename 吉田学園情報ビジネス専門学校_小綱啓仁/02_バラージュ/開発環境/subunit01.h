//=============================================================================
//
// subunit01.h
// Author : koduna hirohito
//
//=============================================================================
#ifndef _SUBUUNIT01_H_			//このマクロ定義がされなかったら
#define _SUBUUNIT01_H_			//2重インクルード防止のマクロ定義

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "main.h"
#include "subunit.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class C2DPolygon;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CSubunit01 : public CSubunit
{
private:
	static const float SUB_UNIT_SUBTRAHEND_Y;
	static const float SUB_UNIT_SUBTRAHEND_X;
	static const float Y_SUB_UNIT_WIDTH;
public:
	CSubunit01();
	~CSubunit01() override;
	void Update(const D3DXVECTOR3 pos) override;
	void SetInitPos(const D3DXVECTOR3 pos) override;
	void SetBullet(int nTextIndex, D3DXVECTOR3 pos) override;

protected:

private:

};

#endif