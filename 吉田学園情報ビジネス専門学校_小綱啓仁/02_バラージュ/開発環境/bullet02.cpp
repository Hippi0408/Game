//=============================================================================
//
// Bullet02.cpp
// Author : koduna hirohito
//
//=============================================================================

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "bullet02.h"
#include "game.h"
#include "player.h"

//*****************************************************************************
// コンストラクタ
//*****************************************************************************
CBullet02::CBullet02()
{
}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
CBullet02::~CBullet02()
{
}

//*****************************************************************************
// 弾のセット処理
//*****************************************************************************
void CBullet02::SetBullet(const Bullet bullet)
{
	CPlayer *pplayer = CGame::GetPlayer();
	D3DXVECTOR3 ePos = bullet.pos;
	D3DXVECTOR3 pPos = pplayer->GetPos();
	D3DXVECTOR3 DestPos = pPos - ePos;
	D3DXVECTOR3 move;
	D3DXVec3Normalize(&move, &DestPos);
	move *= bullet.fMove;

	D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, 0.0f, atan2f(DestPos.x, DestPos.y));

	SetDiagonalLine(bullet.fSize, bullet.fSize);
	SetTextIndex(bullet.nTextIndex);
	SetUp(ePos, rot, move);
	SetType(bullet.Type);
	SetColor(bullet.col);
	SetPolygon();
}

//*****************************************************************************
// 弾のセット処理
//*****************************************************************************
void CBullet02::BulletMove()
{
	float fMove = GetBulletMove();
	D3DXVECTOR3 move = GetMove();
	if (fMove < 5.0f)
	{
		fMove *= 1.05f;
	}
	D3DXVec3Normalize(&move, &move);
	move *= fMove;
	SetBulletMove(fMove);
	SetMove(move);
}
