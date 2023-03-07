//=============================================================================
//
// Bullet03.cpp
// Author : koduna hirohito
//
//=============================================================================

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "bullet03.h"
#include "game.h"
#include "player.h"
#include "enemymanager .h"
#include "explosion.h"

//*****************************************************************************
// コンストラクタ
//*****************************************************************************
CBullet03::CBullet03()
{
}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
CBullet03::~CBullet03()
{
}

//*****************************************************************************
// 終了条件処理
//*****************************************************************************
bool CBullet03::IsUnused()
{

	if (m_bReflection)
	{
		return CBulletBase::IsUnused();
	}

	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 move = GetMove();

	if (pos.y < SCREEN_HEIGHT * 0.5f - SCREEN_GAME_HEIGHT * 0.5f)
	{
		move.y *= -1.0f;
		pos.y = SCREEN_HEIGHT * 0.5f - SCREEN_GAME_HEIGHT * 0.5f;
	}
	else if (pos.y > SCREEN_HEIGHT * 0.5f + SCREEN_GAME_HEIGHT * 0.5f)
	{
		move.y *= -1.0f;
		pos.y = SCREEN_HEIGHT * 0.5f + SCREEN_GAME_HEIGHT * 0.5f;
	}

	if (pos.x < SCREEN_WIDTH * 0.5f - SCREEN_GAME_WIDTH * 0.5f)
	{
		move.x *= -1.0f;
		pos.x = SCREEN_WIDTH * 0.5f - SCREEN_GAME_WIDTH * 0.5f;
	}
	else if (pos.x > SCREEN_WIDTH * 0.5f + SCREEN_GAME_WIDTH * 0.5f)
	{
		move.x *= -1.0f;
		pos.x = SCREEN_WIDTH * 0.5f + SCREEN_GAME_WIDTH * 0.5f;
	}

	if (pos != GetPos())
	{
		SetPos(pos);
		SetMove(move);
		m_bReflection = true;
	}

	return CBulletBase::IsUnused();
}

