//=============================================================================
//
// enemy05.cpp
// Author : koduna hirohito
//
//=============================================================================

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "enemy05.h"
#include "bulletmanager.h"
#include "sound.h"

//*****************************************************************************
// コンストラクタ
//*****************************************************************************
CEnemy05::CEnemy05()
{
	m_nBulletCoolTime = 0;
}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
CEnemy05::~CEnemy05()
{
}

//*****************************************************************************
// 敵の攻撃処理
//*****************************************************************************
void CEnemy05::EnemyAttack()
{
	m_nBulletCoolTime++;

	if (m_nBulletCoolTime >= ENEMY_ATTACK_CNT)
	{
		m_nBulletCoolTime = 0;

		Bullet bullet;
		bullet.fMove = 1.0f;
		bullet.fSize = 20.0f;
		bullet.nTextIndex = GetBulletText();
		bullet.pos = GetPos();
		bullet.col = D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f);
		bullet.Type = BULLET_ENEMY;
		bullet.Vector = D3DXVECTOR3(0.0f,-1.0f,0.0f);

		CBulletManager::ShotBullet(bullet, BULLET_MOVE_03, 6, 300.0f);
	}
}

//*****************************************************************************
// 終了条件処理
//*****************************************************************************
bool CEnemy05::IsUnused()
{
	if (m_nLife <= 0)
	{
		//サウンド再生
		PlaySound(SOUND_LABEL_SE_EXPLOSION);

		Bullet bullet;
		bullet.fMove = 1.0f;
		bullet.fSize = 20.0f;
		bullet.nTextIndex = GetBulletText();
		bullet.pos = GetPos();
		bullet.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		bullet.Type = BULLET_ENEMY;
		bullet.Vector = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
		CBulletManager::ShotBullet(bullet, BULLET_MOVE_02, 8, 315.0f, GetActualRadius() * 2.0f);
		return true;
	}
	return false;
}