//=============================================================================
//
// BulletSpecial02.h
// Author : koduna hirohito
//
//=============================================================================
#ifndef _BULLET_SPECIAL02_H_			//このマクロ定義がされなかったら
#define _BULLET_SPECIAL02_H_			//2重インクルード防止のマクロ定義

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "bulletbase.h"

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CBulletSpecial02 : public CBulletBase
{
private:
	static const int DAMAGE_COOL_TIME = 60;
	static const int BULLET_LIFE = 5;
public:

	CBulletSpecial02();//コンストラクタ
	~CBulletSpecial02() override;//デストラクタ

	bool IsUnused() override;//終了条件
	void BulletRot() override;//弾の向き
	void BulletMove() override;//弾の動き
	void SetBullet(const Bullet bullet)override;
private:
	int m_nDamageCoolTime;
	int m_nLife;
	
};

#endif