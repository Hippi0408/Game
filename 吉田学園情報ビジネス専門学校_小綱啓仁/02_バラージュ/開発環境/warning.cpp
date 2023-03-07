//=============================================================================
//
// warning.cpp
// Author : koduna hirohito
//
//=============================================================================

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "main.h"
#include "warning.h"
#include "2dpolygon.h"
#include "texture.h"
#include <assert.h>

//*****************************************************************************
// 静的変数宣言
//*****************************************************************************
// ワーニング表示のPOS
const D3DXVECTOR3 CWarning::WARNING_POS[MAX_WARNING] =
{
	D3DXVECTOR3(500.0f,200.0f,0.0f),
	D3DXVECTOR3(1000.0f,200.0f,0.0f),
	D3DXVECTOR3(900.0f,600.0f,0.0f),
	D3DXVECTOR3(600.0f,600.0f,0.0f)
};

// ワーニング表示のROT
const D3DXVECTOR3 CWarning::WARNING_ROT[MAX_WARNING] =
{
	D3DXVECTOR3(0.0f,0.0f,D3DXToRadian(45)),
	D3DXVECTOR3(0.0f,0.0f,D3DXToRadian(-20)),
	D3DXVECTOR3(0.0f,0.0f,D3DXToRadian(10)),
	D3DXVECTOR3(0.0f,0.0f,D3DXToRadian(-30))
};

// ワーニング表示のSISE
const D3DXVECTOR2 CWarning::WARNING_SISE[MAX_WARNING] =
{
	D3DXVECTOR2(700.0f,100.0f),
	D3DXVECTOR2(1400.0f,50.0f),
	D3DXVECTOR2(1000.0f,200.0f),
	D3DXVECTOR2(1200.0f,50.0f)
};

//*****************************************************************************
// コンストラクタ
//*****************************************************************************
CWarning::CWarning()
{
	ZeroMemory(&m_pWarning, sizeof(m_pWarning));
	m_pRedFade = nullptr;
	m_bWarning = false;
}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
CWarning::~CWarning()
{
}

//*****************************************************************************
// 初期化
//*****************************************************************************
HRESULT CWarning::Init()
{
	int nTex = CTexture::LoadTexture("data/TEXTURE/warning.png");

	for (int nCnt = 0; nCnt < MAX_WARNING; nCnt++)
	{
		m_pWarning[nCnt] = new C2DPolygon;

		if (FAILED(m_pWarning[nCnt]->Init()))
		{
			assert(false);
		}

		m_pWarning[nCnt]->SetTextIndex(nTex);
		m_pWarning[nCnt]->SetPos(WARNING_POS[nCnt]);
		m_pWarning[nCnt]->SetDiagonalLine(WARNING_SISE[nCnt].x, WARNING_SISE[nCnt].y);
		m_pWarning[nCnt]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		m_pWarning[nCnt]->SetRot(WARNING_ROT[nCnt]);
		m_pWarning[nCnt]->SetUVMove(D3DXVECTOR2(0.005f,0.0f));
		m_pWarning[nCnt]->SetFadeSpeed(0.01f);
		m_pWarning[nCnt]->SetPolygon();

	}

	m_pRedFade = new C2DPolygon;

	if (FAILED(m_pRedFade->Init()))
	{
		assert(false);
	}

	m_pRedFade->SetTextIndex(0);
	m_pRedFade->SetPos(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f));
	m_pRedFade->SetDiagonalLine(1000.0f, 1000.0f);
	m_pRedFade->SetColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.0f));
	m_pRedFade->SetFadeSpeed(0.01f);
	m_pRedFade->SetAlphaLimitValue(0.6f,0.2f);
	m_pRedFade->SetPolygon();

	return S_OK;
}

//*****************************************************************************
// 終了処理
//*****************************************************************************
void CWarning::Uninit()
{
	for (int nCnt = 0; nCnt < MAX_WARNING; nCnt++)
	{
		if (m_pWarning[nCnt] != nullptr)
		{
			// 終了処理
			m_pWarning[nCnt]->Uninit();
			delete m_pWarning[nCnt];
			m_pWarning[nCnt] = nullptr;
		}
	}

	if (m_pRedFade != nullptr)
	{
		// 終了処理
		m_pRedFade->Uninit();
		delete m_pRedFade;
		m_pRedFade = nullptr;
	}
}

//*****************************************************************************
// 更新処理
//*****************************************************************************
void CWarning::Update()
{
	if (!m_bWarning)
	{
		return;
	}
	
	for (int nCnt = 0; nCnt < MAX_WARNING; nCnt++)
	{
		if (m_pWarning[nCnt] != nullptr)
		{
			m_pWarning[nCnt]->SetFlashing(10);
			m_pWarning[nCnt]->Update();
		}
	}

	m_pRedFade->SetFlashing(10);
	m_pRedFade->Update();
}

//*****************************************************************************
// 描画処理
//*****************************************************************************
void CWarning::Draw()
{
	if (!m_bWarning)
	{
		return;
	}
	for (int nCnt = 0; nCnt < MAX_WARNING; nCnt++)
	{
		if (m_pWarning[nCnt] != nullptr)
		{
			m_pWarning[nCnt]->Draw();
		}
	}
	m_pRedFade->Draw();
}

//*****************************************************************************
// ワーニング終了
//*****************************************************************************
bool CWarning::OutWarning()
{
	D3DXCOLOR col;

	for (int nCnt = 0; nCnt < MAX_WARNING; nCnt++)
	{
		col = m_pWarning[nCnt]->GetColor();
		col.a -= 0.1f;

		if (col.a < 0.0f)
		{
			col.a = 0.0f;
		}

		m_pWarning[nCnt]->SetColor(col);
	}

	col = m_pRedFade->GetColor();
	
	col.a -= 0.05f;

	if (col.a < 0.0f)
	{
		col.a = 0.0f;
	}

	m_pRedFade->SetColor(col);

	if (col.a <= 0.0f)
	{
		m_bWarning = false;
		return true;
	}
	return false;
}
