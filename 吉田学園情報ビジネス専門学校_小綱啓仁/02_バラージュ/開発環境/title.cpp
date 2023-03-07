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
#include "title.h"
#include "2dpolygon.h"
#include "texture.h"
#include "input.h"
#include "manager.h"
#include "ui.h"
#include "3dobject.h"
#include "title3dbg.h"
#include "camera.h"
#include "light.h"
#include "3dpolygon.h"
#include "sound.h"
#include "ranking.h"
#include "read.h"

//*****************************************************************************
// コンストラクタ
//*****************************************************************************
CTitle::CTitle()
{
	m_pTitlePolygon = nullptr;
	m_pCamera = nullptr;
	m_pBGObj = nullptr;
	m_pLight = nullptr;
	m_pBG = nullptr;
	m_pPressKeyPolygon = nullptr;
	m_fPressKeyPolygonColorA = 1.0f;
	m_nRankingCnt = 0;
	m_bRanking = false;
}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
CTitle::~CTitle()
{
}

//*****************************************************************************
// 初期化
//*****************************************************************************
HRESULT CTitle::Init()
{
	m_pTitlePolygon = nullptr;

	m_pTitlePolygon = new CUI;

	if (FAILED(m_pTitlePolygon->Init()))
	{
		return -1;
	}

	C2DPolygon *pPolygon = m_pTitlePolygon->CreateUi(1);

	int nIndex = CTexture::LoadTexture("data/TEXTURE/タイトルロゴ.png");
	pPolygon->SetTextIndex(nIndex);
	pPolygon->SetPos(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f));
	pPolygon->SetDiagonalLine(800.0f, 800.0f);
	pPolygon->SetPolygon();


	m_pPressKeyPolygon = new C2DPolygon;

	if (FAILED(m_pPressKeyPolygon->Init()))
	{
		return -1;
	}

	nIndex = CTexture::LoadTexture("data/TEXTURE/PressKey.png");
	m_pPressKeyPolygon->SetTextIndex(nIndex);
	m_pPressKeyPolygon->SetPos(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT - 200.0f, 0.0f));
	m_pPressKeyPolygon->SetDiagonalLine(600.0f, 600.0f);
	m_pPressKeyPolygon->SetColor(D3DXCOLOR(1.0f,1.0f,1.0f, m_fPressKeyPolygonColorA));
	m_pPressKeyPolygon->SetFadeSpeed(0.01f);
	m_pPressKeyPolygon->SetPolygon();

	//カメラ
	m_pCamera = new CCamera;
	if (FAILED(m_pCamera->Init()))
	{
		return -1;
	}

	m_pCamera->SetPosV(D3DXVECTOR3(-30.0f, 25.0f, -50.0f));
	m_pCamera->SetPosR(D3DXVECTOR3(-30.0f, 10.0f, 0.0f));
	m_pCamera->SetVecU(D3DXVECTOR3(0.0f, 1.0f, 0.0f));

	//ライト
	m_pLight = new CLight;
	if (FAILED(m_pLight->Init()))
	{
		return -1;
	}

	//BG3D
	m_pBGObj = new CTitle3DBG;
	if (FAILED(m_pBGObj->Init()))
	{
		return -1;
	}


	//BG3D
	m_pBG = new C3DPolygon;
	if (FAILED(m_pBG->Init()))
	{
		return -1;
	}
	nIndex = CTexture::LoadTexture("data/TEXTURE/galaxy.png");
	m_pBG->SetPos(D3DXVECTOR3(-30.0f,-20.0f, 500.0f));
	m_pBG->SetRot(D3DXVECTOR3(D3DXToRadian(-70), D3DXToRadian(0), D3DXToRadian(0)));
	m_pBG->SetTextIndex(nIndex);
	m_pBG->SetDiagonalLine(500.0f, 500.0f);
	m_pBG->SetPolygon();

	CManager *pManager = GetManager();

	D3DXVECTOR3 Pos = D3DXVECTOR3(1400.0f, -1900.0f, 0.0f);
	m_pRanking = new CRanking;
	m_pRanking->Init(Pos);
	

	m_pRead = new CRead;
	m_pRead->ReadRanking(pManager->GetStage(), m_pRanking);

	m_pRanking->Update();
	//サウンド停止
	StopSound();
	//サウンド再生
	PlaySound(SOUND_LABEL_BGM_TITLE);
	return S_OK;
}

//*****************************************************************************
// 終了処理
//*****************************************************************************
void CTitle::Uninit()
{
	if (m_pTitlePolygon != nullptr)
	{
		// 終了処理
		m_pTitlePolygon->Uninit();
		delete m_pTitlePolygon;
		m_pTitlePolygon = nullptr;
	}

	if (m_pPressKeyPolygon != nullptr)
	{
		m_pPressKeyPolygon->Uninit();
		delete m_pPressKeyPolygon;
		m_pPressKeyPolygon = nullptr;
	}

	//カメラ
	if (m_pCamera != nullptr)
	{
		m_pCamera->Uninit();
		delete m_pCamera;
		m_pCamera = nullptr;
	}
	//3DBG
	if (m_pBGObj != nullptr)
	{
		m_pBGObj->Uninit();
		delete m_pBGObj;
		m_pBGObj = nullptr;
	}

	//3DBG
	if (m_pBG != nullptr)
	{
		m_pBG->Uninit();
		delete m_pBG;
		m_pBG = nullptr;
	}

	C3DObject::UninitAllModel();

	//ライト
	if (m_pLight != nullptr)
	{
		m_pLight->Uninit();
		delete m_pLight;
		m_pLight = nullptr;
	}

	if (m_pRead != nullptr)
	{
		delete m_pRead;
		m_pRead = nullptr;
	}

	if (m_pRanking != nullptr)
	{
		// 終了処理
		m_pRanking->Uninit();
		delete m_pRanking;
		m_pRanking = nullptr;
	}
}

//*****************************************************************************
// 更新処理
//*****************************************************************************
void CTitle::Update()
{
	if (!m_bRanking)
	{
		m_pTitlePolygon->Update();

		m_pPressKeyPolygon->SetFlashing(10);
		m_pPressKeyPolygon->Update();
	}
	else
	{
		m_pRanking->Update();
	}
	
	m_pBGObj->Update();

	m_pBG->Update();

	m_nRankingCnt++;
	if (RANKING_CNT_MAX < m_nRankingCnt)
	{
		if (m_bRanking)
		{
			D3DXVECTOR3 Pos = D3DXVECTOR3(1400.0f, -1900.0f, 0.0f);
			m_pRanking->SetPos(Pos);
			m_pRanking->Update();
			m_bRanking = false;
		}
		else
		{
			m_bRanking = true;
		}
		m_nRankingCnt = 0;
	}
	
	
	CInput *pInput = CInput::GetKey();

	if (pInput->Trigger(KEY_DECISION))
	{
		//サウンド再生
		PlaySound(SOUND_LABEL_SE_DETERMINATION);
		m_pPressKeyPolygon->SetFadeSpeed(0.5f);
		CManager * pManager = GetManager();
		pManager->NextMode(TYPE_TUTORIAL);
		m_bRanking = false;
		m_nRankingCnt = 0;
	}
}

//*****************************************************************************
// 描画処理
//*****************************************************************************
void CTitle::Draw()
{
	//カメラ
	m_pCamera->SetCamera();

	m_pBG->Draw();
	//背景
	m_pBGObj->Draw();

	if (!m_bRanking)
	{
		m_pTitlePolygon->Draw();

		m_pPressKeyPolygon->Draw();
	}
	else
	{
		m_pRanking->Draw();
	}
}