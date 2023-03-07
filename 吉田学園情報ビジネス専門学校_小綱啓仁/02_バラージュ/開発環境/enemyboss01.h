//=============================================================================
//
// enemyboss01.h
// Author : koduna hirohito
//
//=============================================================================
#ifndef _ENEMY_BOSS01_H_			//���̃}�N����`������Ȃ�������
#define _ENEMY_BOSS01_H_			//2�d�C���N���[�h�h�~�̃}�N����`

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