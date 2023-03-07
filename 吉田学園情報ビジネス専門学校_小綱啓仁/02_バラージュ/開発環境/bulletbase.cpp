//=============================================================================
//
// Bullet.cpp
// Author : koduna hirohito
//
//=============================================================================

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "bulletbase.h"
#include "bullet01.h"
#include "main.h"
#include "enemymanager .h"
#include "game.h"
#include "player.h"
#include "explosion.h"
#include <assert.h>

// ポリゴンの幅
const float CBulletBase::SIZE_BULLET = 16.0f;
//*****************************************************************************
// コンストラクタ
//*****************************************************************************
CBulletBase::CBulletBase()
{
	m_fMove = 1.0f;
	m_Type = BULLET_TYPE_MAX;
}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
CBulletBase::~CBulletBase()
{
}

//*****************************************************************************
// 初期化
//*****************************************************************************
HRESULT CBulletBase::Init()
{
	if (FAILED(C2DPolygon::Init()))
	{
		return -1;
	}
	m_Type = BULLET_TYPE_MAX;
	return S_OK;
}

//*****************************************************************************
// 終了処理
//*****************************************************************************
void CBulletBase::Uninit()
{
	C2DPolygon::Uninit();
}

//*****************************************************************************
// 更新処理
//*****************************************************************************
void CBulletBase::Update()
{
	//弾の動き
	BulletMove();
	//弾の向き
	BulletRot();
	C2DPolygon::Update();
}

//*****************************************************************************
// 描画処理
//*****************************************************************************
void CBulletBase::Draw()
{
	C2DPolygon::Draw();
}

//*****************************************************************************
// 弾のセット処理
//*****************************************************************************
void CBulletBase::SetBullet(const Bullet bullet)
{
	D3DXVECTOR3 pos = bullet.pos;
	D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, 0.0f, atan2f(bullet.Vector.x, bullet.Vector.y));
	D3DXVECTOR3 move;
	D3DXVec3Normalize(&move, &bullet.Vector);
	move *= bullet.fMove;

	SetColor(bullet.col);
	SetDiagonalLine(bullet.fSize, bullet.fSize);
	SetTextIndex(bullet.nTextIndex);
	SetUp(pos, rot, move);
	SetType(bullet.Type);
	SetColor(bullet.col);
	SetPolygon();
}

//*****************************************************************************
//弾の動き
//*****************************************************************************
void CBulletBase::BulletMove()
{
}

//*****************************************************************************
//弾の向き
//*****************************************************************************
void CBulletBase::BulletRot()
{
}

//*****************************************************************************
// 終了条件処理
//*****************************************************************************
bool CBulletBase::IsUnused()
{
	D3DXVECTOR3 pos = GetPos();
	if (pos.y < SCREEN_HEIGHT * 0.5f - SCREEN_GAME_HEIGHT * 0.5f)
	{
		return true;
	}
	else if (pos.y > SCREEN_HEIGHT * 0.5f + SCREEN_GAME_HEIGHT * 0.5f)
	{
		return true;
	}

	if (pos.x < SCREEN_WIDTH * 0.5f - SCREEN_GAME_WIDTH * 0.5f)
	{
		return true;
	}
	else if (pos.x > SCREEN_WIDTH * 0.5f + SCREEN_GAME_WIDTH * 0.5f)
	{
		return true;
	}

	if (m_Type == BULLET_PLAYER)
	{
		if (CEnemyManager::Collision(pos, GetActualRadius()))
		{
			CExplosion::CreateExplosion(pos);
			return true;
		}
	}
	else if (m_Type == BULLET_ENEMY)
	{
		CPlayer *pPlayer = CGame::GetPlayer();

		if (pPlayer->HetPlayer(pos, GetActualRadius()))
		{
			CExplosion::CreateExplosion(pos);
			return true;
		}
	}


	return false;
}

