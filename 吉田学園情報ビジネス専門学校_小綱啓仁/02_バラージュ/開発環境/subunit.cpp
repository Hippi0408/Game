//=============================================================================
//
// subunit.cpp
// Author : koduna hirohito
//
//=============================================================================

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "subunit.h"
#include "2dpolygon.h"
#include "texture.h"
#include "bulletmanager.h"
#include "effect.h"
#include "manager.h"
#include <assert.h>

//*****************************************************************************
// 静的変数宣言
//*****************************************************************************
const float CSubunit::MAX_RANGE_WITH_PLAYER[MAX_SUBUNIT] = { 70.0f,-70.0f };
const float CSubunit::SIZE_SUBUNIT = 50.0f;
//*****************************************************************************
// コンストラクタ
//*****************************************************************************
CSubunit::CSubunit()
{
	ZeroMemory(&m_pSubunit, sizeof(m_pSubunit));
	m_nSubunitCnt = 0;
	m_nSubunitTexIndex = 0;
	m_bUes = true;
}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
CSubunit::~CSubunit()
{
}

//*****************************************************************************
// 初期化
//*****************************************************************************
HRESULT CSubunit::Init(const D3DXVECTOR3 pos)
{
	CManager *pManager = GetManager();
	switch (pManager->GetAirframe())
	{
	case 0:
		m_Color = D3DXCOLOR(1.0f, 0.4f, 0.4f, 1.0f);
		break;
	case 1:
		m_Color = D3DXCOLOR(0.0f, 0.5f, 1.0f, 1.0f);
		break;
	case 2:
		m_Color = D3DXCOLOR(0.5f, 1.0f, 0.0f, 1.0f);
		break;
	default:
		assert(false);
		break;
	}

	m_nSubunitTexIndex = CTexture::LoadTexture("data/TEXTURE/Subunit.png");
	
	SetInitPos(pos);

	return S_OK;
}

//*****************************************************************************
// 終了処理
//*****************************************************************************
void CSubunit::Uninit()
{
	for (int nCnt = 0; nCnt < MAX_SUBUNIT; nCnt++)
	{
		if (m_pSubunit[nCnt] != nullptr)
		{
			// 終了処理
			m_pSubunit[nCnt]->Uninit();
			delete m_pSubunit[nCnt];
			m_pSubunit[nCnt] = nullptr;
		}
	}
}

//*****************************************************************************
// 描画処理
//*****************************************************************************
void CSubunit::Draw()
{
	for (int nCnt = 0; nCnt < MAX_SUBUNIT; nCnt++)
	{
		if (m_pSubunit[nCnt] != nullptr)
		{
			// 描画処理
			m_pSubunit[nCnt]->Draw();
		}
	}
}

//*****************************************************************************
// エフェクト
//*****************************************************************************
void CSubunit::EffeCt(const D3DXVECTOR3 pos)
{
	if ((m_nSubunitCnt % 4) == 0 && m_bUes)
	{
		CEffect::Effect effect;
		effect.fAttenuation = -0.1f;
		effect.fSizeX = SIZE_SUBUNIT;
		effect.fSizeY = SIZE_SUBUNIT;
		effect.nLife = 100;
		effect.nTextIndex = m_nSubunitTexIndex;
		effect.Color = m_Color;
		effect.pos = pos;

		CEffect::CreateEffect(effect);
	}
}