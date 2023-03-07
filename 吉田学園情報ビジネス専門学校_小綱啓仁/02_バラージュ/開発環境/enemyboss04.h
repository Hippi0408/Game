//=============================================================================
//
// enemyboss04.h
// Author : koduna hirohito
//
//=============================================================================
#ifndef _ENEMY_BOSS04_H_			//���̃}�N����`������Ȃ�������
#define _ENEMY_BOSS04_H_			//2�d�C���N���[�h�h�~�̃}�N����`

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "enemybase.h"
#include "enemydata.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CEnemyBoss04 : public CEnemyBase
{
private:
	static const float ENEMY_BOSS04_SIZE;
	static const int ENEMY_ATTACK_CNT = 300;
	static const int BOSS_DIEDCNT = 180;

public:
	CEnemyBoss04();
	~CEnemyBoss04() override;
	HRESULT Init() override;
	bool Collision(D3DXVECTOR3 pos, float radius) override;
	bool IsUnused() override;
	void EnemyMove() override;
	void EnemyRot() override;
	void EnemyAttack() override;
	void EnemyEffect()override;
	bool EnemyBossEffect() override;

private:
	int m_nBossAttack;
	int m_nBossRotCnt;
	static int m_nBossNum;
	static int m_nBossDiedCnt;
};

#endif

