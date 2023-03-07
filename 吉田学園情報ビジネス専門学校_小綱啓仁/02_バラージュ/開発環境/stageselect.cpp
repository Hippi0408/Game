//=============================================================================
//
// stageselect.cpp
// Author : koduna hirohito
//
//=============================================================================

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "main.h"
#include "stageselect.h"
#include "input.h"
#include "manager.h"
#include "ui.h"
#include "2dpolygon.h"
#include "texture.h"
#include "camera.h"
#include "3dobject.h"
#include "light.h"
#include "stageselect3dbg.h"
#include "sound.h"
#include <assert.h>

const float CStageSelect::SIZE_UI = 1.0f / MAX_STAGE;
const float CStageSelect::SIZE_UI_HALF = SIZE_UI * 0.5f;

const float CStageSelect::SIZE_AIRFRAME_UI = 1.0f / MAX_PL_AIRFRAME;
const float CStageSelect::SIZE_AIRFRAME_UI_HALF = SIZE_AIRFRAME_UI * 0.5f;

const float CStageSelect::OBJ_DISTANCE = 200.0f;

const float CStageSelect::ARROW_WIDTH_LEFT_RIGHT = 500.0f;
const float CStageSelect::ARROW_WIDTH_UP_AND_DOWN = 500.0f;
const float CStageSelect::ARROW_ADD_WIDTH = 50.0f;
//*****************************************************************************
// コンストラクタ
//*****************************************************************************
CStageSelect::CStageSelect()
{
	m_pRead = nullptr;
	m_pCamera = nullptr;
	m_pBGObj = nullptr;
	m_pLight = nullptr;
	m_pMessageBoxUI = nullptr;
	m_pStageNameUI = nullptr;
	m_nStage = 0;
	m_nAirframe = 0;
	m_nNotTouchCnt = 0;
	m_bDetermination = false;
	m_nSelectionCnt = SELECTION_COOL_TIME;
	m_fAddArrow = ARROW_ADD_WIDTH;
	m_nAddArrowCnt = 0;
	for (int nCnt = 0; nCnt < ARROW_MAX; nCnt++)
	{
		m_pArrowLeftRightUI[nCnt] = nullptr;
		m_pArrowUpDownUI[nCnt] = nullptr;
	}
}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
CStageSelect::~CStageSelect()
{
}

//*****************************************************************************
// 初期化
//*****************************************************************************
HRESULT CStageSelect::Init()
{
	CManager * pManager = GetManager();
	m_nStage = (int)pManager->GetStage();
	m_nAirframe = pManager->GetAirframe();

	m_pUi = nullptr;

	m_pUi = new CUI;

	if (FAILED(m_pUi->Init()))
	{
		return -1;
	}

	C2DPolygon *pPolygon = m_pUi->CreateUi(1);

	int nIndex = CTexture::LoadTexture("data/TEXTURE/StageSelectUI01.png");
	pPolygon[0].SetTextIndex(nIndex);
	pPolygon[0].SetPos(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f));
	pPolygon[0].SetDiagonalLine((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT);
	pPolygon[0].SetPolygon();

	m_pMessageBoxUI = new C2DPolygon;

	if (FAILED(m_pMessageBoxUI->Init()))
	{
		return -1;
	}
	nIndex = CTexture::LoadTexture("data/TEXTURE/StageSelectUI02.png");
	m_pMessageBoxUI->SetTextIndex(nIndex);
	m_pMessageBoxUI->SetPos(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f));
	m_pMessageBoxUI->SetDiagonalLine((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT);
	m_pMessageBoxUI->SetPolygon();

	m_pStageNameUI = new C2DPolygon;

	if (FAILED(m_pStageNameUI->Init()))
	{
		return -1;
	}
	nIndex = CTexture::LoadTexture("data/TEXTURE/StageSelectUI03.png");
	m_pStageNameUI->SetTextIndex(nIndex);
	m_pStageNameUI->SetUVSize(D3DXVECTOR2(SIZE_UI_HALF, 0.5f));
	m_pStageNameUI->SetUV(D3DXVECTOR2(SIZE_UI_HALF, 0.5f));
	m_pStageNameUI->SetPos(D3DXVECTOR3(SCREEN_WIDTH - 425.0f, 175.0f, 0.0f));
	m_pStageNameUI->SetDiagonalLine(500.0f, 500.0f);
	m_pStageNameUI->SetPolygon();
	
	m_pPlayerUI = new C2DPolygon;

	if (FAILED(m_pPlayerUI->Init()))
	{
		return -1;
	}
	nIndex = CTexture::LoadTexture("data/TEXTURE/StageSelectUI04.png");
	m_pPlayerUI->SetTextIndex(nIndex);
	m_pPlayerUI->SetUVSize(D3DXVECTOR2(0.5f, SIZE_AIRFRAME_UI_HALF));
	m_pPlayerUI->SetUV(D3DXVECTOR2(0.5f, SIZE_AIRFRAME_UI_HALF));
	m_pPlayerUI->SetPos(D3DXVECTOR3(245.0f,585.0f, 0.0f));
	m_pPlayerUI->SetDiagonalLine(300.0f, 500.0f);
	m_pPlayerUI->SetPolygon();

	nIndex = CTexture::LoadTexture("data/TEXTURE/StageSelectUI05.png");

	for (int nCnt = 0; nCnt < ARROW_MAX; nCnt++)
	{
		m_pArrowLeftRightUI[nCnt] = new C2DPolygon;

		if (FAILED(m_pArrowLeftRightUI[nCnt]->Init()))
		{
			return -1;
		}
		float fArrowLeftRightHalf = ARROW_WIDTH_LEFT_RIGHT * 0.5f;
		m_pArrowLeftRightUI[nCnt]->SetTextIndex(nIndex);
		m_pArrowLeftRightUI[nCnt]->SetPos(D3DXVECTOR3(SCREEN_WIDTH * 0.5f - fArrowLeftRightHalf + (ARROW_WIDTH_LEFT_RIGHT * nCnt), SCREEN_GAME_HEIGHT * 0.5f + 150.0f, 0.0f));
		m_pArrowLeftRightUI[nCnt]->SetDiagonalLine(200.0f, 200.0f);
		m_pArrowLeftRightUI[nCnt]->SetRot(D3DXVECTOR3(0.0f,0.0f, D3DXToRadian(90 - 180 * nCnt)));
		m_pArrowLeftRightUI[nCnt]->SetPolygon();

	}

	for (int nCnt = 0; nCnt < ARROW_MAX; nCnt++)
	{
		m_pArrowUpDownUI[nCnt] = new C2DPolygon;

		if (FAILED(m_pArrowUpDownUI[nCnt]->Init()))
		{
			return -1;
		}
		D3DXVECTOR3 pos = m_pPlayerUI->GetPos();
		float fArrowLeftRightHalf = ARROW_WIDTH_UP_AND_DOWN * 0.5f;
		m_pArrowUpDownUI[nCnt]->SetTextIndex(nIndex);
		m_pArrowUpDownUI[nCnt]->SetPos(D3DXVECTOR3(pos.x,
			pos.y - fArrowLeftRightHalf + (ARROW_WIDTH_UP_AND_DOWN * nCnt), 0.0f));
		m_pArrowUpDownUI[nCnt]->SetDiagonalLine(200.0f, 200.0f);
		m_pArrowUpDownUI[nCnt]->SetRot(D3DXVECTOR3(0.0f, 0.0f, D3DXToRadian(180 * nCnt)));
		m_pArrowUpDownUI[nCnt]->SetPolygon();

	}


	//カメラ
	m_pCamera = new CCamera;
	if (FAILED(m_pCamera->Init()))
	{
		return -1;
	}
	m_pCamera->SetPosV(D3DXVECTOR3(0.0f, 0.0f, -300.0f));

	//ライト
	m_pLight = new CLight;
	if (FAILED(m_pLight->Init()))
	{
		return -1;
	}

	//BG3D
	m_pBGObj = new CStageSelect3DBG;
	if (FAILED(m_pBGObj->Init()))
	{
		return -1;
	}

	m_pBGObj->AddPos(-OBJ_DISTANCE * m_nStage);
	m_pPlayerUI->SetUV(D3DXVECTOR2(0.5f, SIZE_AIRFRAME_UI_HALF + SIZE_AIRFRAME_UI * m_nAirframe));
	m_pPlayerUI->SetPolygon();

	if (!UseSound(SOUND_LABEL_BGM_STAGE_SELECT))
	{
		//サウンド停止
		StopSound();
		//サウンド再生
		PlaySound(SOUND_LABEL_BGM_STAGE_SELECT);
	}


	return S_OK;
}

//*****************************************************************************
// 終了処理
//*****************************************************************************
void CStageSelect::Uninit()
{
	//UI
	if (m_pUi != nullptr)
	{
		// 終了処理
		m_pUi->Uninit();
		delete m_pUi;
		m_pUi = nullptr;
	}

	if (m_pMessageBoxUI != nullptr)
	{
		// 終了処理
		m_pMessageBoxUI->Uninit();
		delete m_pMessageBoxUI;
		m_pMessageBoxUI = nullptr;
	}

	if (m_pStageNameUI != nullptr)
	{
		// 終了処理
		m_pStageNameUI->Uninit();
		delete m_pStageNameUI;
		m_pStageNameUI = nullptr;
	}

	if (m_pPlayerUI != nullptr)
	{
		// 終了処理
		m_pPlayerUI->Uninit();
		delete m_pPlayerUI;
		m_pPlayerUI = nullptr;
	}

	for (int nCnt = 0; nCnt < ARROW_MAX; nCnt++)
	{
		if (m_pArrowLeftRightUI[nCnt] != nullptr)
		{
			// 終了処理
			m_pArrowLeftRightUI[nCnt]->Uninit();
			delete m_pArrowLeftRightUI[nCnt];
			m_pArrowLeftRightUI[nCnt] = nullptr;
		}

		if (m_pArrowUpDownUI[nCnt] != nullptr)
		{
			// 終了処理
			m_pArrowUpDownUI[nCnt]->Uninit();
			delete m_pArrowUpDownUI[nCnt];
			m_pArrowUpDownUI[nCnt] = nullptr;
		}
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

	//ライト
	if (m_pLight != nullptr)
	{
		m_pLight->Uninit();
		delete m_pLight;
		m_pLight = nullptr;
	}

}

//*****************************************************************************
// 更新処理
//*****************************************************************************
void CStageSelect::Update()
{
	//3DBG
	if (m_pBGObj != nullptr)
	{
		m_pBGObj->Update();
	}

	if (m_bDetermination)
	{
		return;
	}

	CInput *pInput = CInput::GetKey();

	m_nSelectionCnt++;

	if (pInput->Press(KEY_LEFT) && m_nSelectionCnt > SELECTION_COOL_TIME)
	{
		if (!(m_nStage <= StageNum_01))
		{
			m_nSelectionCnt = 0;
			//サウンド再生
			PlaySound(SOUND_LABEL_SE_LEFT_RIGHT);
			m_nNotTouchCnt = 0;
			m_pMessageBoxUI->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
			m_pStageNameUI->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
			m_nStage--;
			m_pBGObj->AddDestPos(OBJ_DISTANCE);
			
		}
	}
	else if (pInput->Press(KEY_RIGHT) && m_nSelectionCnt > SELECTION_COOL_TIME)
	{
		if (!(m_nStage >= (StageNum_MAX - 1)))
		{
			m_nSelectionCnt = 0;
			//サウンド再生StageNum_02
			PlaySound(SOUND_LABEL_SE_LEFT_RIGHT);
			m_nNotTouchCnt = 0;
			m_pMessageBoxUI->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
			m_pStageNameUI->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
			m_nStage++;
			m_pBGObj->AddDestPos(-OBJ_DISTANCE);
			
		}
	}

	if (m_nStage == StageNum_01)
	{
		m_pArrowLeftRightUI[0]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	}
	else if (m_nStage == (StageNum_MAX - 1))
	{
		m_pArrowLeftRightUI[1]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	}
	else
	{
		m_pArrowLeftRightUI[0]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_pArrowLeftRightUI[1]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}

	if (pInput->Trigger(KEY_UP))
	{
		//サウンド再生
		PlaySound(SOUND_LABEL_SE_UP_DOWN);
		m_nAirframe++;
	}
	else if (pInput->Trigger(KEY_DOWN))
	{
		//サウンド再生
		PlaySound(SOUND_LABEL_SE_UP_DOWN);
		m_nAirframe--;
	}

	if (m_nAirframe >= MAX_PL_AIRFRAME)
	{
		m_nAirframe = 0;
	}
	else if (m_nAirframe < 0)
	{
		m_nAirframe = MAX_PL_AIRFRAME - 1;
	}

	m_pPlayerUI->SetUV(D3DXVECTOR2(0.5f, SIZE_AIRFRAME_UI_HALF + SIZE_AIRFRAME_UI * m_nAirframe));
	m_pPlayerUI->SetPolygon();

	m_nNotTouchCnt++;
	if (m_nNotTouchCnt > 30)
	{
		m_pMessageBoxUI->PolygonAppear(0.05f);
		m_pStageNameUI->PolygonAppear(0.05f);
	}

	m_pStageNameUI->SetUV(D3DXVECTOR2(SIZE_UI_HALF + SIZE_UI * m_nStage, 0.5f));
	m_pStageNameUI->SetPolygon();
	m_pMessageBoxUI->SetPolygon();

	m_nAddArrowCnt++;
	for (int nCnt = 0; nCnt < ARROW_MAX; nCnt++)
	{
		if (m_pArrowLeftRightUI[nCnt] == nullptr)
		{
			assert(false);
		}
		if (m_pArrowUpDownUI[nCnt] == nullptr)
		{
			assert(false);
		}

		if (m_nAddArrowCnt > ARROW_ADD_WIDTH_CNT_MAX)
		{
			float fArrowLeftRight = ARROW_WIDTH_LEFT_RIGHT + m_fAddArrow;
			float fArrowLeftRightHalf = fArrowLeftRight * 0.5f;
			m_pArrowLeftRightUI[nCnt]->SetPos(D3DXVECTOR3(SCREEN_WIDTH * 0.5f - fArrowLeftRightHalf + (fArrowLeftRight * nCnt)
				, SCREEN_GAME_HEIGHT * 0.5f + 150.0f, 0.0f));

			D3DXVECTOR3 pos = m_pPlayerUI->GetPos();
			float fArrowUpDown = ARROW_WIDTH_UP_AND_DOWN + m_fAddArrow;
			float fArrowUpDownHalf = fArrowUpDown * 0.5f;
			m_pArrowUpDownUI[nCnt]->SetPos(D3DXVECTOR3(pos.x,
				pos.y - fArrowUpDownHalf + (fArrowUpDown * nCnt), 0.0f));

		}

		m_pArrowLeftRightUI[nCnt]->SetPolygon();
		m_pArrowUpDownUI[nCnt]->SetPolygon();
	}
	if (m_nAddArrowCnt > ARROW_ADD_WIDTH_CNT_MAX)
	{
		m_fAddArrow = ARROW_ADD_WIDTH - m_fAddArrow;
		m_nAddArrowCnt = 0;
	}

	if (pInput->Trigger(KEY_DECISION))
	{
		//サウンド再生
		PlaySound(SOUND_LABEL_SE_DETERMINATION);
		m_bDetermination = true;
		CManager * pManager = GetManager();
		pManager->SetStage((StageNum)m_nStage);
		pManager->SetAirframe(m_nAirframe);
		pManager->NextMode(TYPE_GAME);
	}
}

//*****************************************************************************
// 描画処理
//*****************************************************************************
void CStageSelect::Draw()
{
	////カメラ
	m_pCamera->SetCamera();
	////背景
	m_pBGObj->Draw();
	//ＵＩ
	m_pUi->Draw();
	m_pMessageBoxUI->Draw();
	m_pStageNameUI->Draw();
	m_pPlayerUI->Draw();
	for (int nCnt = 0; nCnt < ARROW_MAX; nCnt++)
	{
		if (m_pArrowLeftRightUI[nCnt] != nullptr)
		{
			m_pArrowLeftRightUI[nCnt]->Draw();
		}
		if (m_pArrowUpDownUI[nCnt] != nullptr)
		{
			m_pArrowUpDownUI[nCnt]->Draw();
		}
	}

}