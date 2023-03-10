//=============================================================================
//
// Bullet01.h
// Author : koduna hirohito
//
//=============================================================================
#ifndef _BULLET01_H_			//このマクロ定義がされなかったら
#define _BULLET01_H_			//2重インクルード防止のマクロ定義

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "bulletbase.h"

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CBullet01 : public CBulletBase
{

public:

	CBullet01();//コンストラクタ
	~CBullet01() override;//デストラクタ
	void BulletMove() override;//弾の動き
private:
};

#endif