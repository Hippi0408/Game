//=============================================================================
//
// enemyboss03.h
// Author : koduna hirohito
//
//=============================================================================
#ifndef _ENEMY_BOSS03_H_			//このマクロ定義がされなかったら
#define _ENEMY_BOSS03_H_			//2重インクルード防止のマクロ定義

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "enemybase.h"
#include "enemydata.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CEnemyBoss03 : public CEnemyBase
{
private:
	static const float ENEMY_BOSS03_SIZE;
	static const int ENEMY_ATTACK_CNT = 120;

public:
	CEnemyBoss03();
	~CEnemyBoss03() override;
	HRESULT Init() override;
	bool Collision(D3DXVECTOR3 pos, float radius) override;
	bool IsUnused() override;
	void EnemyMove() override;
	void EnemyAttack() override;
	void EnemyEffect()override;
private:
	int m_nBossAttack;
	int m_nSpecialBulletTex;
};

#endif