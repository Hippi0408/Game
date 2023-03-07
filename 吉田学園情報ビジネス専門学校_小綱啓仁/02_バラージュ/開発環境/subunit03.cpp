//=============================================================================
//
// subunit03.cpp
// Author : koduna hirohito
//
//=============================================================================

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "subunit03.h"
#include "2dpolygon.h"
#include "bulletmanager.h"
#include "manager.h"
#include <assert.h>

//*****************************************************************************
// 静的変数宣言
//*****************************************************************************
const float CSubunit03::SUB_UNIT_SUBTRAHEND_Y = 0.7f;
const float CSubunit03::SUB_UNIT_SUBTRAHEND_X = 0.3f;
const float CSubunit03::X_SUB_UNIT_WIDTH = -75.0f;

//*****************************************************************************
// コンストラクタ
//*****************************************************************************
CSubunit03::CSubunit03()
{
}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
CSubunit03::~CSubunit03()
{
}

//*****************************************************************************
// 更新処理
//*****************************************************************************
void CSubunit03::Update(const D3DXVECTOR3 pos)
{
	m_nSubunitCnt += 4;

	if (m_nSubunitCnt >= 360)
	{
		m_nSubunitCnt = 0;
	}

	for (int nCnt = 0; nCnt < MAX_SUBUNIT; nCnt++)
	{
		if (m_pSubunit[nCnt] == nullptr)
		{
			return;
		}

		D3DXVECTOR3 Pos;

		float fRadUnit = D3DXToRadian(m_nSubunitCnt);

		Pos.x = pos.x + sinf(fRadUnit) * MAX_RANGE_WITH_PLAYER[nCnt] * SUB_UNIT_SUBTRAHEND_X;
		Pos.y = pos.y + cosf(fRadUnit) * MAX_RANGE_WITH_PLAYER[nCnt] * SUB_UNIT_SUBTRAHEND_Y;
		if (nCnt == 0)
		{
			Pos.x += X_SUB_UNIT_WIDTH;
		}
		else
		{
			Pos.x -= X_SUB_UNIT_WIDTH;
		}
		
		Pos.z = 0.0f;

		m_pSubunit[nCnt]->SetPos(Pos);

		m_pSubunit[nCnt]->SetPolygon();

		EffeCt(Pos);

	}
}

//*****************************************************************************
// サブユニットの初期位置の設定
//*****************************************************************************
void CSubunit03::SetInitPos(const D3DXVECTOR3 pos)
{
	for (int nCnt = 0; nCnt < MAX_SUBUNIT; nCnt++)
	{
		m_pSubunit[nCnt] = new C2DPolygon;

		if (FAILED(m_pSubunit[nCnt]->Init()))
		{
			assert(false);
		}
		m_pSubunit[nCnt]->SetDiagonalLine(SIZE_SUBUNIT, SIZE_SUBUNIT);
		m_pSubunit[nCnt]->SetTextIndex(m_nSubunitTexIndex);
		D3DXVECTOR3 Pos = pos;

		Pos.x = pos.x + sinf(D3DXToRadian(m_nSubunitCnt)) * MAX_RANGE_WITH_PLAYER[nCnt] * SUB_UNIT_SUBTRAHEND_X;
		Pos.y = pos.y + cosf(D3DXToRadian(m_nSubunitCnt)) * MAX_RANGE_WITH_PLAYER[nCnt] * SUB_UNIT_SUBTRAHEND_Y;
		if (nCnt == 0)
		{
			Pos.x += X_SUB_UNIT_WIDTH;
		}
		else
		{
			Pos.x -= X_SUB_UNIT_WIDTH;
		}
		Pos.z = 0.0f;

		m_pSubunit[nCnt]->SetColor(m_Color);
		m_pSubunit[nCnt]->SetPos(Pos);
		m_pSubunit[nCnt]->SetPolygon();
	}
}

//*****************************************************************************
// 弾の発射
//*****************************************************************************
void CSubunit03::SetBullet(int nTextIndex, D3DXVECTOR3 pos)
{
	for (int nCnt = 0; nCnt < MAX_SUBUNIT; nCnt++)
	{
		if (m_pSubunit[nCnt] != nullptr)
		{
			Bullet bullet;
			bullet.fMove = 8.0f;
			bullet.fSize = 30.0f;
			bullet.nTextIndex = nTextIndex;
			bullet.pos = m_pSubunit[nCnt]->GetPos();
			if (nCnt == 1)
			{
				bullet.Vector = D3DXVECTOR3(0.5f, -0.5f, 0.0f);
			}
			else
			{
				bullet.Vector = D3DXVECTOR3(-0.5f, -0.5f, 0.0f);
			}

			D3DXVec3Normalize(&bullet.Vector, &bullet.Vector);

			bullet.Type = BULLET_PLAYER;
			bullet.col = m_Color;

			CBulletManager::ShotBullet(bullet, BULLET_MOVE_00, 5, 30.0f);
		}
	}
}
