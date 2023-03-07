//=============================================================================
//
// BulletSpecial01.cpp
// Author : koduna hirohito
//
//=============================================================================

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "bulletspecial01.h"
#include "bulletmanager.h"
#include "game.h"
#include "player.h"
#include "explosion.h"
#include "effect.h"

//*****************************************************************************
// コンストラクタ
//*****************************************************************************
CBulletSpecial01::CBulletSpecial01()
{
	m_nDamageCoolTime = 0;
	m_nLife = BULLET_LIFE;
}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
CBulletSpecial01::~CBulletSpecial01()
{
}

//*****************************************************************************
// 終了条件処理
//*****************************************************************************
bool CBulletSpecial01::IsUnused()
{
	D3DXVECTOR3 pos = GetPos();
	
	if (pos.y > SCREEN_HEIGHT * 0.5f + SCREEN_GAME_HEIGHT * 0.5f)
	{
		return true;
	}

	m_nDamageCoolTime++;
	if (DAMAGE_COOL_TIME > m_nDamageCoolTime)
	{
		return false;
	}

	CPlayer *pPlayer = CGame::GetPlayer();

	if (pPlayer->HetPlayer(pos, GetActualRadius()))
	{
		CExplosion::CreateExplosion(pos);
		m_nDamageCoolTime = 0;
	}

	float fradius = GetActualRadius();

	if (CBulletManager::CollisionBullet(pos, fradius, BULLET_PLAYER))
	{
		m_nLife -= 1;
	}

	if (m_nLife <= 0)
	{
		Bullet bullet;
		bullet.fMove = 10.0f;
		bullet.fSize = 40.0f;
		bullet.nTextIndex = GetTextIndex();
		bullet.pos = GetPos();
		bullet.Type = BULLET_PLAYER;
		bullet.Vector = D3DXVECTOR3(0.0f,-1.0f,0.0f);
		CBulletManager::ShotBullet(bullet, BULLET_MOVE_04, 3, 90.0f);
		return true;
	}

	return false;
}


//*****************************************************************************
// 弾の動き
//*****************************************************************************
void CBulletSpecial01::BulletMove()
{
	float fMove = GetBulletMove();
	D3DXVECTOR3 move = GetMove();
	if (fMove < 4.0f)
	{
		fMove *= 1.02f;
	}
	D3DXVec3Normalize(&move, &move);

	float fradius = GetActualRadius() * 2.0f;
	CEffect::Effect effect;
	effect.fAttenuation = -0.05f;
	effect.fSizeX = fradius;
	effect.fSizeY = fradius;
	effect.nLife = 20;
	effect.fScaleDown = -1.0f;
	effect.nTextIndex = 0;
	effect.pos = GetPos();
	effect.Color = D3DXCOLOR(0.6f, 0.3f, 0.3f, 1.0f);
	effect.move = D3DXVECTOR3(0.0f, -5.0f, 0.0f);
	effect.bAddColor = true;

	CEffect::CreateEffect(effect);
	CEffect::CreateEffect(effect);

	move *= fMove;
	SetBulletMove(fMove);
	SetMove(move);
}

//*****************************************************************************
//弾の向き
//*****************************************************************************
void CBulletSpecial01::BulletRot()
{
	D3DXVECTOR3 rot = GetRot();

	rot.z += 0.1f;

	SetRot(rot);
}