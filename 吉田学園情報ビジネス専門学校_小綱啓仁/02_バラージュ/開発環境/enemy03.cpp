//=============================================================================
//
// enemy03.cpp
// Author : koduna hirohito
//
//=============================================================================

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "enemy03.h"
#include "game.h"
#include "player.h"
#include "bulletmanager.h"

//*****************************************************************************
// コンストラクタ
//*****************************************************************************
CEnemy03::CEnemy03()
{
	m_nBulletCoolTime = 0;
}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
CEnemy03::~CEnemy03()
{
}

//*****************************************************************************
// 敵の攻撃処理
//*****************************************************************************
void CEnemy03::EnemyAttack()
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

		D3DXMATRIX mtxRot;
		Bullet bullet;
		bullet.fMove = 1.0f;
		bullet.fSize = 20.0f;
		bullet.nTextIndex = GetBulletText();
		bullet.pos = Epos;
		bullet.col = D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f);
		bullet.Type = BULLET_ENEMY;

		bullet.Vector = vec;

		CBulletManager::ShotBullet(bullet, BULLET_MOVE_03, 4, 30.0f);
	}
}
