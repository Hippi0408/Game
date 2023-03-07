//=============================================================================
//
// subunit02.cpp
// Author : koduna hirohito
//
//=============================================================================

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "subunit02.h"
#include "2dpolygon.h"
#include "bulletmanager.h"
#include "manager.h"
#include <assert.h>

//*****************************************************************************
// コンストラクタ
//*****************************************************************************
CSubunit02::CSubunit02()
{
}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
CSubunit02::~CSubunit02()
{
}

//*****************************************************************************
// 更新処理
//*****************************************************************************
void CSubunit02::Update(const D3DXVECTOR3 pos)
{
	m_nSubunitCnt += 2;

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

		Pos.x = pos.x + sinf(fRadUnit) * MAX_RANGE_WITH_PLAYER[nCnt];
		Pos.y = pos.y + cosf(fRadUnit) * MAX_RANGE_WITH_PLAYER[nCnt];
		Pos.z = 0.0f;

		m_pSubunit[nCnt]->SetPos(Pos);

		m_pSubunit[nCnt]->SetPolygon();

		EffeCt(Pos);

	}
}

//*****************************************************************************
// サブユニットの初期位置の設定
//*****************************************************************************
void CSubunit02::SetInitPos(const D3DXVECTOR3 pos)
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

		float fRadUnit = D3DXToRadian(m_nSubunitCnt);

		Pos.x = pos.x + sinf(fRadUnit) * MAX_RANGE_WITH_PLAYER[nCnt];
		Pos.y = pos.y + cosf(fRadUnit) * MAX_RANGE_WITH_PLAYER[nCnt];
		Pos.z = 0.0f;

		m_pSubunit[nCnt]->SetColor(m_Color);
		m_pSubunit[nCnt]->SetPos(Pos);
		m_pSubunit[nCnt]->SetPolygon();
	}
}

//*****************************************************************************
// 弾の発射
//*****************************************************************************
void CSubunit02::SetBullet(int nTextIndex, D3DXVECTOR3 pos)
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
			bullet.Vector = m_pSubunit[nCnt]->GetPos() - pos;

			D3DXVec3Normalize(&bullet.Vector, &bullet.Vector);

			bullet.Type = BULLET_PLAYER;
			bullet.col = m_Color;

			CBulletManager::ShotBullet(bullet, BULLET_MOVE_00);
		}
	}
}
