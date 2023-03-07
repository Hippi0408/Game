//=============================================================================
//
// game.cpp
// Author : koduna hirohito
//
//=============================================================================

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "main.h"
#include "tutorial.h"
#include "input.h"
#include "manager.h"
#include "ui.h"
#include "2dpolygon.h"
#include "texture.h"
#include <assert.h>
#include "sound.h"

//*****************************************************************************
// コンストラクタ
//*****************************************************************************
CTutorial::CTutorial()
{
	m_pUi = nullptr;
}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
CTutorial::~CTutorial()
{
}

//*****************************************************************************
// 初期化
//*****************************************************************************
HRESULT CTutorial::Init()
{
	m_pUi = nullptr;

	m_pUi = new CUI;

	if (FAILED(m_pUi->Init()))
	{
		return -1;
	}

	CInput *pInput = CInput::GetKey();
	int nIndex;

	switch (pInput->GetOldInputType())
	{
	case INPUT_TYPE_KEYBOARD:
		nIndex = CTexture::LoadTexture("data/TEXTURE/TutorialUI01.png");
		break;
	case INPUT_TYPE_JOYPAD:
		nIndex = CTexture::LoadTexture("data/TEXTURE/TutorialUI02.png");
		break;
	default:
		assert(false);
		break;
	}

	C2DPolygon *pPolygon = m_pUi->CreateUi(1);

	pPolygon[0].SetTextIndex(nIndex);
	pPolygon[0].SetPos(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f));
	pPolygon[0].SetDiagonalLine((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT);
	pPolygon[0].SetPolygon();

	m_pPressKeyPolygon = new C2DPolygon;

	if (FAILED(m_pPressKeyPolygon->Init()))
	{
		return -1;
	}

	nIndex = CTexture::LoadTexture("data/TEXTURE/PressKey.png");
	m_pPressKeyPolygon->SetTextIndex(nIndex);
	m_pPressKeyPolygon->SetPos(D3DXVECTOR3(SCREEN_WIDTH - 200.0f, 800.0f, 0.0f));
	m_pPressKeyPolygon->SetDiagonalLine(400.0f, 400.0f);
	m_pPressKeyPolygon->SetFadeSpeed(0.01f);
	m_pPressKeyPolygon->SetPolygon();

	//サウンド停止
	StopSound();
	//サウンド再生
	PlaySound(SOUND_LABEL_BGM_STAGE_SELECT);
	return S_OK;
}

//*****************************************************************************
// 終了処理
//*****************************************************************************
void CTutorial::Uninit()
{
	if (m_pPressKeyPolygon != nullptr)
	{
		m_pPressKeyPolygon->Uninit();
		delete m_pPressKeyPolygon;
		m_pPressKeyPolygon = nullptr;
	}

	//UI
	if (m_pUi != nullptr)
	{
		// 終了処理
		m_pUi->Uninit();
		delete m_pUi;
		m_pUi = nullptr;
	}
}

//*****************************************************************************
// 更新処理
//*****************************************************************************
void CTutorial::Update()
{
	CManager * pManager = GetManager();

	CInput *pInput = CInput::GetKey();

	m_pPressKeyPolygon->SetFlashing(10);
	m_pPressKeyPolygon->Update();

	m_pUi->Update();

	if (pInput->Trigger(KEY_DECISION) && !pManager->IsChangingMode())
	{//ポーズ画面への切り替え
		//サウンド再生
		PlaySound(SOUND_LABEL_SE_DETERMINATION);
		m_pPressKeyPolygon->SetFadeSpeed(0.5f);
		pManager->NextMode(TYPE_STAGE_SELECT);
	}

	
}

//*****************************************************************************
// 描画処理
//*****************************************************************************
void CTutorial::Draw()
{
	//ＵＩ
	m_pUi->Draw();

	m_pPressKeyPolygon->Draw();
}