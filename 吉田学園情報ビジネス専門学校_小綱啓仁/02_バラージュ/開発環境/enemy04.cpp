//=============================================================================
//
// enemy04.cpp
// Author : koduna hirohito
//
//=============================================================================

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "enemy04.h"
#include "game.h"
#include "player.h"
#include "bulletmanager.h"

//*****************************************************************************
// コンストラクタ
//*****************************************************************************
CEnemy04::CEnemy04()
{
	m_nBulletCoolTime = 0;
}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
CEnemy04::~CEnemy04()
{
}

//*****************************************************************************
// 敵の攻撃処理
//*****************************************************************************
void CEnemy04::EnemyAttack()
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


		D3DXMatrixRotationZ(&mtxRot, D3DXToRadian(45.0f));
		D3DXVec3TransformCoord(&vec, &vec, &mtxRot);

		bullet.Vector = vec;

		CBulletManager::ShotBullet(bullet, BULLET_MOVE_03, 4, 275.0f);
	}
}
