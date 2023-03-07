//=============================================================================
//
// enemyboss05.h
// Author : koduna hirohito
//
//=============================================================================
#ifndef _ENEMY_BOSS05_H_			//このマクロ定義がされなかったら
#define _ENEMY_BOSS05_H_			//2重インクルード防止のマクロ定義

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "enemyboss02.h"
#include "enemydata.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CEnemyBoss05 : public CEnemyBoss02
{
private:
	static const float ENEMY_BOSS05_SIZE;
	static const int ENEMY_ATTACK_CNT = 80;
	static const int BOSS_BODY_NUMBER = 20;
	static const int BODY_FRAME_DISTANCE = 6;
	static const int MAX_BOSS_POS_OLD = BODY_FRAME_DISTANCE * BOSS_BODY_NUMBER;
	static const int BOSS_DIEDCNT = 180;

public:
	CEnemyBoss05();
	~CEnemyBoss05() override;
	
	bool EnemyBossHeadCollision(D3DXVECTOR3 pos, float radius)override;
	bool IsUnused() override;
	void EnemyAttack() override;
	bool EnemyBossEffect()override;
private:
	
	static int m_nBossNum;
	static int m_nBossDiedCnt;
};

#endif