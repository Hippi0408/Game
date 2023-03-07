//=============================================================================
//
// enemy01.cpp
// Author : koduna hirohito
//
//=============================================================================

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "enemyboss01.h"
#include "game.h"
#include "player.h"
#include "bulletmanager.h"
#include "counter.h"
#include "manager.h"
#include <assert.h>
#include "sound.h"

const float CEnemyBoss01::ENEMY_BOSS01_SIZE = 300.0f;
//*****************************************************************************
// コンストラクタ
//*****************************************************************************
CEnemyBoss01::CEnemyBoss01()
{
	m_nBulletCoolTime = 0;
}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
CEnemyBoss01::~CEnemyBoss01()
{
}

//*****************************************************************************
// 初期化
//*****************************************************************************
HRESULT CEnemyBoss01::Init()
{
	if (FAILED(C2DPolygon::Init()))
	{
		return -1;
	}
	m_nBossAttack = 0;
	m_nBossRotCnt = 0;
	SetEnemyMove(1.0f);
	SetDiagonalLine(ENEMY_BOSS01_SIZE, ENEMY_BOSS01_SIZE);//表示するポリゴンの縦横幅設定
	SetPolygon();

	return S_OK;
}

//*****************************************************************************
// 終了条件処理
//*****************************************************************************
bool CEnemyBoss01::IsUnused()
{
	if (m_nLife <= 0)
	{
		CManager * pManager = GetManager();
		pManager->NextMode(TYPE_RESULT,180);
		return true;
	}
	return false;
}

//*****************************************************************************
// 当たり判定
//*****************************************************************************
bool CEnemyBoss01::Collision(D3DXVECTOR3 pos, float radius)
{
	if (C2DPolygon::Collision(pos, radius))
	{
		m_nLife -= 1;
		//サウンド再生
		PlaySound(SOUND_LABEL_SE_ENEMY_DAMAGE);
		if (m_nLife <= 0)
		{
			DiedEnemy();
			CCounter::AddCounter(3000);
			CBulletManager::BreakBullet(BULLET_ENEMY);
		}
		return true;
	}
	return false;
}

//*****************************************************************************
// 敵の移動
//*****************************************************************************
void CEnemyBoss01::EnemyMove()
{
	float fMove = GetEnemyMove();
	D3DXVECTOR3 move = GetMove();
	if (fMove < 6.0f)
	{
		fMove *= 1.01f;
	}
	D3DXVec3Normalize(&move, &move);
	move *= fMove;
	SetEnemyMove(fMove);
	SetMove(move);
}

//*****************************************************************************
// 敵の向きの変化
//*****************************************************************************
void CEnemyBoss01::EnemyRot()
{
	m_nBossRotCnt++;

	if (m_nBossRotCnt >= 360)
	{
		m_nBossRotCnt = 0;
	}

	SetRot(D3DXVECTOR3(0.0f,0.0f, D3DXToRadian(m_nBossRotCnt)));

}

//*****************************************************************************
// 敵のエフェクト
//*****************************************************************************
void CEnemyBoss01::EnemyEffect()
{
}

//*****************************************************************************
// 敵の攻撃処理
//*****************************************************************************
void CEnemyBoss01::EnemyAttack()
{
	m_nBulletCoolTime--;

	D3DXVECTOR3 Epos = GetPos();
	CPlayer *pPlayer = CGame::GetPlayer();

	D3DXVECTOR3 PLpos = pPlayer->GetPos();

	D3DXVECTOR3 vec = PLpos - Epos;

	D3DXVec3Normalize(&vec, &vec);

	Bullet bullet;
	bullet.fMove = 2.0f;
	bullet.fSize = 20.0f;
	bullet.nTextIndex = GetBulletText();
	bullet.pos = Epos;
	bullet.Type = BULLET_ENEMY;
	bullet.Vector = vec;


	if (!(SCREEN_WIDTH / 2.0f - 300.0f < Epos.x
		&& SCREEN_WIDTH / 2.0f + 300.0f > Epos.x))
	{
		return;
	}

	if (m_nBulletCoolTime % 30 == 0)
	{
		CBulletManager::ShotBullet(bullet, BULLET_MOVE_01, 3, 45.0f);
	}

	if (m_nBulletCoolTime > 0)
	{
		return;
	}

	m_nBulletCoolTime = 300;

	switch (m_nBossAttack)
	{
	case 0:
		CBulletManager::ShotBullet(bullet, BULLET_MOVE_01, 5, 45.0f);
		break;
	case 1:
		CBulletManager::ShotBullet(bullet, BULLET_MOVE_01, 12, 45.0f);
		break;
	case 2:
		CBulletManager::ShotBullet(bullet, BULLET_MOVE_01, 5, 45.0f);
		break;
	case 3:
		CBulletManager::ShotBullet(bullet, BULLET_MOVE_01, 36, 30.0f);
		break;
	case 4:
		CBulletManager::ShotBullet(bullet, BULLET_MOVE_01, 5, 45.0f);
		break;
	case 5:
		CBulletManager::ShotBullet(bullet, BULLET_MOVE_02, 36, 360.0f, 200.0f);
		break;
	default:
		assert(false);
		break;
	}

	m_nBossAttack++;
	
	if (m_nBossAttack > 5)
	{
		m_nBossAttack = 0;
	}

}
