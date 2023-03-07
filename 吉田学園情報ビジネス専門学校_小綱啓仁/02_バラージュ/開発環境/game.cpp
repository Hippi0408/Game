//=============================================================================
//
// game.cpp
// Author : koduna hirohito
//
//=============================================================================

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "player.h"
#include "main.h"
#include "game.h"
#include "input.h"
#include "manager.h"
#include "ui.h"
#include "2dpolygon.h"
#include "texture.h"
#include "enemymanager .h"
#include "bulletmanager.h"
#include "anim.h"
#include "explosion.h"
#include "counter.h"
#include "time.h"
#include "read.h"
#include "gauge.h"
#include "counter.h"
#include "camera.h"
#include "3dobject.h"
#include "light.h"
#include "game3dbg.h"
#include "effect.h"
#include "pause.h"
#include "warning.h"
#include "sound.h"

CPlayer *CGame::m_pPlayer = nullptr;
CEnemyManager *CGame::m_pEnemyManager = nullptr;
CBulletManager *CGame::m_pBulletManager = nullptr;
//*****************************************************************************
// コンストラクタ
//*****************************************************************************
CGame::CGame()
{
	m_pPlayer = nullptr;
	m_pEnemyManager = nullptr;
	m_pBulletManager = nullptr;
	m_pRead = nullptr;
	m_pCamera = nullptr;
	m_pBGObj = nullptr;
	m_pLight = nullptr;
	m_pPause = nullptr;
	m_nWarningCnt = 0;
}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
CGame::~CGame()
{
}

//*****************************************************************************
// 初期化
//*****************************************************************************
HRESULT CGame::Init()
{
	m_bBossDied = false;
	
	CEffect::ALLInit();

	m_pUi = nullptr;

	m_pUi = new CUI;

	if (FAILED(m_pUi->Init()))
	{
		return -1;
	}

	C2DPolygon *pPolygon = m_pUi->CreateUi(5);

	int nIndex = CTexture::LoadTexture("data/TEXTURE/gameui01.png");
	pPolygon[0].SetTextIndex(nIndex);
	pPolygon[0].SetPos(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f));
	pPolygon[0].SetDiagonalLine((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT);
	pPolygon[0].SetPolygon();

	nIndex = CTexture::LoadTexture("data/TEXTURE/gameui02.png");
	pPolygon[1].SetTextIndex(nIndex);
	pPolygon[1].SetPos(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f));
	pPolygon[1].SetDiagonalLine((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT);
	pPolygon[1].SetPolygon();

	nIndex = CTexture::LoadTexture("data/TEXTURE/gameui03.png");
	pPolygon[2].SetTextIndex(nIndex);
	pPolygon[2].SetPos(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f));
	pPolygon[2].SetDiagonalLine((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT);
	pPolygon[2].SetColor(D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f));
	pPolygon[2].SetPolygon();

	pPolygon[3].SetTextIndex(0);
	pPolygon[3].SetPos(D3DXVECTOR3(225.0f, 170.0f, 0.0f));
	pPolygon[3].SetDiagonalLine(350.0f, 25.0f);
	pPolygon[3].SetColor(D3DXCOLOR(0.5f,0.5f,0.5f,1.0f));
	pPolygon[3].SetPolygon();

	pPolygon[4].SetTextIndex(0);
	pPolygon[4].SetPos(D3DXVECTOR3(225.0f, 195.0f, 0.0f));
	pPolygon[4].SetDiagonalLine(350.0f, 15.0f);
	pPolygon[4].SetColor(D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));
	pPolygon[4].SetPolygon();

	m_pPlayer = nullptr;

	m_pPlayer = new CPlayer;

	if (FAILED(m_pPlayer->Init()))
	{
		return -1;
	}

	m_pEnemyManager = new CEnemyManager;

	if (FAILED(m_pEnemyManager->Init()))
	{
		return -1;
	}

	m_pBulletManager = new CBulletManager;

	if (FAILED(m_pBulletManager->Init()))
	{
		return -1;
	}

	m_pRead = new CRead;

	m_pRead->ReadAnchorPoint();

	CManager * pManager = GetManager();
	StageNum Stage = pManager->GetStage();
	m_pRead->ReadEnemy(Stage);
	ModelTxt modeltxt = ModelTxtMax;

	switch (Stage)
	{
	case StageNum_01:
		modeltxt = GameStage01;
		break;
	case StageNum_02:
		modeltxt = GameStage02;
		break;
	case StageNum_03:
		modeltxt = GameStage03;
		break;
	case StageNum_04:
		modeltxt = GameStage04;
		break;
	case StageNum_05:
		modeltxt = GameStage05;
		break;
	case StageNum_06:
		modeltxt = GameStage06;
		break;
	default:
		break;
	}
	m_pRead->ReadModel(modeltxt);

	//サウンド停止
	StopSound();
	//サウンド再生
	PlaySound((SOUND_LABEL)Stage);

	CAnim::ALLInit();

	CExplosion::Init();

	D3DXVECTOR3 Pos = D3DXVECTOR3(240.0f, 600.0f, 0.0f);
	int nDigit = 3;
	int nNumerical = 120;
	int nTime = 120;
	float fSize = 160.0f;
	if (FAILED(CTime::Init(Pos, nDigit, nNumerical, nTime, fSize)))
	{
		return -1;
	}

	//スコア
	Pos = D3DXVECTOR3(SCREEN_WIDTH - 50.0f, 400.0f, 0.0f);
	nDigit = 8;
	nNumerical = 0;
	fSize = 100.0f;
	CCounter *Counter = CCounter::Create(); 
	if (FAILED(Counter->Init(Pos, nDigit,fSize, nNumerical)))
	{
		return -1;
	}

	//カメラ
	m_pCamera = new CCamera;
	if (FAILED(m_pCamera->Init()))
	{
		return -1;
	}
	m_pCamera->SetPosV(D3DXVECTOR3(0.0f, 70.0f, -100.0f));

	//ライト
	m_pLight = new CLight;
	if (FAILED(m_pLight->Init()))
	{
		return -1;
	}

	//BG3D
	m_pBGObj = new CGame3DBG;
	if (FAILED(m_pBGObj->Init()))
	{
		return -1;
	}

	//ポーズ
	m_pPause = new CPause;
	if (FAILED(m_pPause->Init()))
	{
		return -1;
	}

	m_pWarning = new CWarning;
	if (FAILED(m_pWarning->Init()))
	{
		return -1;
	}

	return S_OK;
}

//*****************************************************************************
// 終了処理
//*****************************************************************************
void CGame::Uninit()
{
	CManager *pManager = GetManager();
	int nScore = CCounter::GetCounter();
	pManager->SetScore(nScore);

	CCounter::AllUninit();
	CTime::Uninit();
	CEffect::ALLUninit();
	CExplosion::Uninit();
	CAnim::ALLUninit();
	CGauge::AllUninit();

	//UI
	if (m_pUi != nullptr)
	{
		// 終了処理
		m_pUi->Uninit();
		delete m_pUi;
		m_pUi = nullptr;
	}

	if (m_pWarning != nullptr)
	{
		// 終了処理
		m_pWarning->Uninit();
		delete m_pWarning;
		m_pWarning = nullptr;
	}

	//ポーズ画面
	if (m_pPause != nullptr)
	{
		// 終了処理
		m_pPause->Uninit();
		delete m_pPause;
		m_pPause = nullptr;
	}

	//プレイヤー
	if (m_pPlayer != nullptr)
	{
		// 終了処理
		m_pPlayer->Uninit();
		delete m_pPlayer;
		m_pPlayer = nullptr;
	}

	//エネミーマネージャー
	if (m_pEnemyManager != nullptr)
	{
		// 終了処理
		m_pEnemyManager->Uninit();
		delete m_pEnemyManager;
		m_pEnemyManager = nullptr;
	}

	//バレットマネージャー
	if (m_pBulletManager != nullptr)
	{
		// 終了処理
		m_pBulletManager->Uninit();
		delete m_pBulletManager;
		m_pBulletManager = nullptr;
	}

	//カメラ
	if (m_pCamera != nullptr)
	{
		m_pCamera->Uninit();
		delete m_pCamera;
		m_pCamera = nullptr;
	}

	//外部ファイル
	if (m_pRead != nullptr)
	{
		delete m_pRead;
		m_pRead = nullptr;
	}

	//3DBG
	if (m_pBGObj != nullptr)
	{
		m_pBGObj->Uninit();
		delete m_pBGObj;
		m_pBGObj = nullptr;
	}
	C3DObject::UninitAllModel();

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
void CGame::Update()
{

	CManager * pManager = GetManager();

	CInput *pInput = CInput::GetKey();

	if (pInput->Trigger(KEY_PAUSE) && !pManager->IsChangingMode())
	{//ポーズ画面への切り替え
		if (m_pPause->GetPause())
		{
			//サウンド再生
			PlaySound(SOUND_LABEL_SE_BACK);
			m_pPause->SetPause(false);
		}
		else
		{
			//サウンド再生
			PlaySound(SOUND_LABEL_SE_DETERMINATION);
			m_pPause->SetPause(true);
		}
	}

	if (m_pPause->GetPause())
	{
		m_pPause->Update();
		return;
	}

	m_pBGObj->Update();
	
	if (!m_pWarning->GetWarning())
	{
		m_pEnemyManager->Update();
	}
	else
	{
		m_nWarningCnt++;
		m_pWarning->Update();
	}

	if (m_nWarningCnt > WARNING_CNT_MAX)
	{
		if (m_pWarning->OutWarning())
		{
			m_nWarningCnt = 0;
		}
	}

	m_pUi->Update();

	m_pPlayer->Update();

	CTime::Update(TYPE_RESULT);

	m_pBulletManager->Update();

	CEffect::ALLUpdate();

	CAnim::ALLUpdate();

	if (m_bBossDied)
	{
		CExplosion::BossDiedExplosion();
	}

}

//*****************************************************************************
// 描画処理
//*****************************************************************************
void CGame::Draw()
{
	//カメラ
	m_pCamera->SetCamera();
	//背景
	m_pBGObj->Draw();
	//エフェクト
	CEffect::ALLDraw();
	//エネミーマネージャー
	m_pEnemyManager->Draw();
	//プレイヤー
	m_pPlayer->Draw();
	//バレット
	m_pBulletManager->Draw();
	//アニメーション
	CAnim::ALLDraw();
	//ワーニング表示
	m_pWarning->Draw();
	//ＵＩ
	m_pUi->Draw();
	//カウンター
	CCounter::AllDraw();
	//タイム
	CTime::Draw();
	//ゲージ
	CGauge::AllDraw();

	//ポーズの描画
	if (m_pPause->GetPause())
	{
		m_pPause->Draw();
	}
}

//*****************************************************************************
// ワーニング表示
//*****************************************************************************
void CGame::SetWarning()
{
	//サウンド再生
	PlaySound(SOUND_LABEL_SE_WARNING);
	m_pWarning->SetWarning();
	CBulletManager::BreakBullet(BULLET_ENEMY);
}
