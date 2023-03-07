//=============================================================================
//
// enemyboss05.cpp
// Author : koduna hirohito
//
//=============================================================================

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "enemyboss05.h"
#include "game.h"
#include "player.h"
#include "bulletmanager.h"
#include "counter.h"
#include "manager.h"
#include "explosion.h"
#include <assert.h>
#include "sound.h"
#include "enemymanager .h"

const float CEnemyBoss05::ENEMY_BOSS05_SIZE = 50.0f;
int CEnemyBoss05::m_nBossNum = 0;
int CEnemyBoss05::m_nBossDiedCnt = 0;
//*****************************************************************************
// コンストラクタ
//*****************************************************************************
CEnemyBoss05::CEnemyBoss05()
{
	m_nBossNum = 2;
	m_nFixedValueBodyMax = BOSS_BODY_NUMBER;
	m_fBodySize = ENEMY_BOSS05_SIZE;
	m_nBossBodyMax = m_nFixedValueBodyMax - 1;

}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
CEnemyBoss05::~CEnemyBoss05()
{
}

//*****************************************************************************
// 終了条件処理
//*****************************************************************************
bool CEnemyBoss05::IsUnused()
{
	if (m_nBossNum <= 1)
	{
		m_nBossDiedCnt++;
	}

	if (m_nLife <= 0)
	{
		m_nBossNum--;
		if (m_nBossNum <= 0)
		{
			if (BOSS_DIEDCNT > m_nBossDiedCnt)
			{
				CCounter::AddCounter(1500);
			}
			CManager * pManager = GetManager();
			pManager->NextMode(TYPE_RESULT, 180);
			CBulletManager::BreakBullet(BULLET_ENEMY);
		}

		for (int nCnt = 0; nCnt <= m_nBossBodyMax; nCnt++)
		{
			CExplosion::CreateExplosion(m_pBossBody[nCnt]->GetPos());
		}

		return true;
	}
	return false;
}

//*****************************************************************************
// 頭単体の判定
//*****************************************************************************
bool CEnemyBoss05::EnemyBossHeadCollision(D3DXVECTOR3 pos, float radius)
{
	if (C2DPolygon::Collision(pos, radius))
	{
		m_nLife -= 4;
		//サウンド再生
		PlaySound(SOUND_LABEL_SE_ENEMY_DAMAGE);
		if (m_nLife <= 0)
		{
			DiedEnemy();
			CCounter::AddCounter(1500);
			CCounter::AddCounter(m_nBossBodyMax * 100);
		}
		return true;
	}
	return false;
}

//*****************************************************************************
// ボスの死亡のエフェクト
//*****************************************************************************
bool CEnemyBoss05::EnemyBossEffect()
{
	if (m_nBossNum <= 0)
	{
		return true;
	}
	return false;
}

//*****************************************************************************
// 敵の攻撃処理
//*****************************************************************************
void CEnemyBoss05::EnemyAttack()
{
	m_nBulletCoolTime++;

	if (m_nBulletCoolTime < ENEMY_ATTACK_CNT)
	{
		return;
	}
	m_nBulletCoolTime = 0;

	Bullet bullet;
	bullet.fMove = 2.0f;
	bullet.fSize = 20.0f;
	bullet.nTextIndex = GetBulletText();
	bullet.Type = BULLET_ENEMY;
	CPlayer *pPlayer = CGame::GetPlayer();
	D3DXVECTOR3 PLpos = pPlayer->GetPos();
	D3DXVECTOR3 Epos;
	D3DXVECTOR3 vec;

	for (int nCnt = 0; nCnt <= m_nBossBodyMax; nCnt++)
	{
		if ((nCnt % 2) == m_nBossAttack)
		{
			continue;
		}

		Epos = m_pBossBody[nCnt]->GetPos();
		vec = PLpos - Epos;
		D3DXVec3Normalize(&vec, &vec);

		bullet.Vector = vec;
		bullet.pos = Epos;

		switch (m_nBossAttack)
		{
		case 0:
			CBulletManager::ShotBullet(bullet, BULLET_MOVE_02, 4, 270.0f, ENEMY_BOSS05_SIZE);
			break;
		case 1:
			bullet.col = D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f);
			CBulletManager::ShotBullet(bullet, BULLET_MOVE_03, 12, 330.0f);
			break;
		default:
			break;
		}

	}


	m_nBossAttack = (1 - m_nBossAttack);


}
