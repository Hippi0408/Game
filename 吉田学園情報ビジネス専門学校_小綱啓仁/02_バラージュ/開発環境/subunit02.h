//=============================================================================
//
// subunit02.h
// Author : koduna hirohito
//
//=============================================================================
#ifndef _SUBUUNIT02_H_			//このマクロ定義がされなかったら
#define _SUBUUNIT02_H_			//2重インクルード防止のマクロ定義

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
class CSubunit02 : public CSubunit
{
private:

public:
	CSubunit02();
	~CSubunit02() override;
	void Update(const D3DXVECTOR3 pos) override;
	void SetInitPos(const D3DXVECTOR3 pos) override;
	void SetBullet(int nTextIndex, D3DXVECTOR3 pos) override;

protected:

private:
	
};

#endif