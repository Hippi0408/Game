//=============================================================================
//
// enemyboss02.h
// Author : koduna hirohito
//
//=============================================================================
#ifndef _ENEMY_BOSS02_H_			//このマクロ定義がされなかったら
#define _ENEMY_BOSS02_H_			//2重インクルード防止のマクロ定義

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
class CEnemyBoss02 : public CEnemyBase
{
private:
	static const float ENEMY_BOSS02_SIZE;
	static const int ENEMY_ATTACK_CNT = 80;
	static const int BOSS_BODY_NUMBER = 40;
	static const int BODY_FRAME_DISTANCE = 6;
	static const int MAX_BOSS_POS_OLD = BODY_FRAME_DISTANCE * BOSS_BODY_NUMBER;

public:
	CEnemyBoss02();
	~CEnemyBoss02() override;
	HRESULT Init() override;
	void Uninit() override;
	void Draw() override;
	bool Collision(D3DXVECTOR3 pos, float radius) override;
	bool IsUnused() override;
	void EnemyMove() override;
	void EnemyRot() override;
	void EnemyAttack() override;
	void EnemyEffect() override;
	virtual bool EnemyBossHeadCollision(D3DXVECTOR3 pos, float radius);

protected:
	int m_nBossBodyMax;
	int m_nFixedValueBodyMax;
	float m_fBodySize;
	int m_nBossAttack;
	C2DPolygon *m_pBossBody[BOSS_BODY_NUMBER];
private:
	int m_nBodyLife[BOSS_BODY_NUMBER];
	float m_fBodyRot[MAX_BOSS_POS_OLD];
	D3DXVECTOR3 m_BossPosOld[MAX_BOSS_POS_OLD];
	int m_nCarrent;
	bool m_bBody[BOSS_BODY_NUMBER];
};

#endif