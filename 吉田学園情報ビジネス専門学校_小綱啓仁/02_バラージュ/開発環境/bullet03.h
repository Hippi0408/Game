//=============================================================================
//
// Bullet03.h
// Author : koduna hirohito
//
//=============================================================================
#ifndef _BULLET03_H_			//このマクロ定義がされなかったら
#define _BULLET03_H_			//2重インクルード防止のマクロ定義

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "bullet01.h"

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CBullet03 : public CBullet01
{

public:

	CBullet03();//コンストラクタ
	~CBullet03() override;//デストラクタ
	bool IsUnused() override;//終了条件

private:
	bool m_bReflection;
};

#endif