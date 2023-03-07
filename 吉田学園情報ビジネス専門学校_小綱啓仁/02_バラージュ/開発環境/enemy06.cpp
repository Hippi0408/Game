//=============================================================================
//
// enemy06.cpp
// Author : koduna hirohito
//
//=============================================================================

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "enemy06.h"
#include "bulletmanager.h"
#include "sound.h"
#include "game.h"
#include "player.h"

//*****************************************************************************
// コンストラクタ
//*****************************************************************************
CEnemy06::CEnemy06()
{
	m_nBulletCoolTime = 0;
}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
CEnemy06::~CEnemy06()
{
}

//*****************************************************************************
// 敵の攻撃処理
//*****************************************************************************
void CEnemy06::EnemyAttack()
{
	m_nBulletCoolTime++;

	if (m_nBulletCoolTime >= ENEMY_ATTACK_CNT)
	{
		m_nBulletCoolTime = 0;

		CPlayer *pPlayer = CGame::GetPlayer();

		D3DXVECTOR3 PLpos = pPlayer->GetPos();

		D3DXVECTOR3 Epos = GetPos();

		D3DXVECTOR3 vec = PLpos - Epos;

		D3DXVec3Normalize(&vec, &vec);

		Bullet bullet;
		bullet.fMove = 1.0f;
		bullet.fSize = 40.0f;
		bullet.nTextIndex = GetBulletText();
		bullet.pos = GetPos();
		bullet.col = D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f);
		bullet.Type = BULLET_ENEMY;
		bullet.Vector = vec;

		CBulletManager::ShotBullet(bullet, BULLET_MOVE_03, 3, 60.0f);
	}
}

//*****************************************************************************
// 終了条件処理
//*****************************************************************************
bool CEnemy06::IsUnused()
{
	if (m_nLife <= 0)
	{
		//サウンド再生
		PlaySound(SOUND_LABEL_SE_EXPLOSION);

		Bullet bullet;
		bullet.fMove = 1.0f;
		bullet.fSize = 40.0f;
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