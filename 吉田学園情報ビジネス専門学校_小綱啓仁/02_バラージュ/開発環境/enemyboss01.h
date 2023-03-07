//=============================================================================
//
// enemyboss01.h
// Author : koduna hirohito
//
//=============================================================================
#ifndef _ENEMY_BOSS01_H_			//このマクロ定義がされなかったら
#define _ENEMY_BOSS01_H_			//2重インクルード防止のマクロ定義

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
class CEnemyBoss01 : public CEnemyBase
{
private:
	static const float ENEMY_BOSS01_SIZE;
	static const int ENEMY_ATTACK_CNT = 60;

public:
	CEnemyBoss01();
	~CEnemyBoss01() override;
	HRESULT Init() override;
	bool Collision(D3DXVECTOR3 pos, float radius) override;
	bool IsUnused() override;
	void EnemyMove() override;
	void EnemyRot() override;
	void EnemyAttack() override;
	void EnemyEffect()override;
private:
	int m_nBossAttack;
	int m_nBossRotCnt;
};

#endif