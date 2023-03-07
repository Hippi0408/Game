//=============================================================================
//
// enemy.cpp
// Author : koduna hirohito
//
//=============================================================================

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "manager.h"
#include "game.h"
#include "texture.h"
#include "enemymanager .h"
#include <assert.h>
#include "enemybase.h"
#include "enemy01.h"
#include "enemy02.h"
#include "enemy03.h"
#include "enemy04.h"
#include "enemy05.h"
#include "enemy06.h"
#include "enemyboss01.h"
#include "enemyboss02.h"
#include "enemyboss03.h"
#include "enemyboss04.h"
#include "enemyboss05.h"
#include "enemyboss06.h"

int CEnemyManager::m_nBulletTextIndex = -1;
CEnemyBase *CEnemyManager::m_pEnemy[ENEMY_MAX] = {};
//*****************************************************************************
// コンストラクタ
//*****************************************************************************
CEnemyManager::CEnemyManager()
{
	//エネミーのテクスチャ
	ZeroMemory(&m_nEnemyTextIndex,sizeof(m_nEnemyTextIndex));

	//エネミーグループ情報
	m_nGroupNum = 0;				//現在生成中の敵グループの数
	m_nGroupMax = 0;					//登録敵グループの数
	ZeroMemory(&m_GroupData, sizeof(m_GroupData));	//グループの全データ

	m_nEnemyMoveTypeMax = 0;		   //エネミーの登録した動きの数
	//エネミーの動きの元
	ZeroMemory(&m_EnemyMoveType, sizeof(m_EnemyMoveType));

	//ゲーム上で生きているエネミーの数
	m_nAliveEnemyCnt = 0;

	//インターバル
	m_nInterval = 0;

}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
CEnemyManager::~CEnemyManager()
{
}

//*****************************************************************************
// 初期化
//*****************************************************************************
HRESULT CEnemyManager::Init()
{
	CManager *pManager = GetManager();

	StageNum Stage = pManager->GetStage();

	//ゲーム開始時、最初のグループが出るまでの間
	m_nInterval = FIRST_INTERVAL;

	m_nBulletTextIndex = CTexture::LoadTexture("data/TEXTURE/EnemyBullet.png");

	m_nEnemyTextIndex[0] = CTexture::LoadTexture("data/TEXTURE/enemy01.png");
	m_nEnemyTextIndex[1] = CTexture::LoadTexture("data/TEXTURE/enemy01.png");
	m_nEnemyTextIndex[2] = CTexture::LoadTexture("data/TEXTURE/enemy02.png");
	m_nEnemyTextIndex[3] = CTexture::LoadTexture("data/TEXTURE/enemy03.png");
	m_nEnemyTextIndex[4] = CTexture::LoadTexture("data/TEXTURE/enemy04.png");
	m_nEnemyTextIndex[5] = CTexture::LoadTexture("data/TEXTURE/enemy05.png");
	m_nEnemyTextIndex[6] = CTexture::LoadTexture("data/TEXTURE/enemy06.png");

	switch (Stage)
	{
	case StageNum_01:
		m_nEnemyTextIndex[7] = CTexture::LoadTexture("data/TEXTURE/boss01.png");
		break;
	case StageNum_02:
		m_nEnemyTextIndex[8] = CTexture::LoadTexture("data/TEXTURE/boss02.png");
		break;
	case StageNum_03:
		m_nEnemyTextIndex[9] = CTexture::LoadTexture("data/TEXTURE/boss03.png");
		break;
	case StageNum_04:
		m_nEnemyTextIndex[10] = CTexture::LoadTexture("data/TEXTURE/boss01.png");
		break;
	case StageNum_05:
		m_nEnemyTextIndex[11] = CTexture::LoadTexture("data/TEXTURE/boss02.png");
		break;
	case StageNum_06:
		m_nEnemyTextIndex[12] = CTexture::LoadTexture("data/TEXTURE/boss03.png");
		break;
	case StageNum_MAX:
	default:
		assert(false);
		break;
	}
	
	
	

	return S_OK;
}

//*****************************************************************************
// 終了処理
//*****************************************************************************
void CEnemyManager::Uninit()
{
	for (int nCnt = 0; nCnt < ENEMY_MAX; nCnt++)
	{
		if (m_pEnemy[nCnt] != nullptr)
		{
			m_pEnemy[nCnt]->Uninit();
			delete m_pEnemy[nCnt];
			m_pEnemy[nCnt] = nullptr;
		}
	}

	//グループの破棄
	for (int nCnt = 0; nCnt < ENEMY_GROUP_MAX; nCnt++)
	{
		if (m_GroupData[nCnt].pEnemyMoveType != nullptr)
		{
			delete[] m_GroupData[nCnt].pEnemyMoveType;
			m_GroupData[nCnt].pEnemyMoveType = nullptr;
		}

		if (m_GroupData[nCnt].pEnemyType != nullptr)
		{
			delete[] m_GroupData[nCnt].pEnemyType;
			m_GroupData[nCnt].pEnemyType = nullptr;
		}

		if (m_GroupData[nCnt].pAddPos != nullptr)
		{
			delete[] m_GroupData[nCnt].pAddPos;
			m_GroupData[nCnt].pAddPos = nullptr;
		}
	}

	//エネミーの動きの破棄
	for (int nCnt = 0; nCnt < ENEMY_MOVE_SOURCE_MAX; nCnt++)
	{
		if (m_EnemyMoveType[nCnt].pAnchorPos != nullptr)
		{
			delete[] m_EnemyMoveType[nCnt].pAnchorPos;
			m_EnemyMoveType[nCnt].pAnchorPos = nullptr;
		}
	}
}

//*****************************************************************************
// 更新処理
//*****************************************************************************
void CEnemyManager::Update()
{
	//ゲーム上で生きているエネミーの数カウントを初期化
	m_nAliveEnemyCnt = 0;

	for (int nCnt = 0; nCnt < ENEMY_MAX; nCnt++)
	{//エネミーの更新
		if (m_pEnemy[nCnt] == nullptr)
		{
			continue;
		}
		m_pEnemy[nCnt]->Update();

		if (m_pEnemy[nCnt] == nullptr)
		{
			continue;
		}

		if (m_pEnemy[nCnt]->IsUnused())
		{//終了条件処理
			if (m_pEnemy[nCnt]->GetEnemyType() >= BOSS_01 
				&& m_pEnemy[nCnt]->EnemyBossEffect())
			{
				CManager *pManager = GetManager();
				CGame * pGame = (CGame*)pManager->GetGameObject();
				pGame->BossDied();
			}

			if (m_pEnemy[nCnt] != nullptr)
			{
				m_pEnemy[nCnt]->Uninit();
				delete m_pEnemy[nCnt];
				m_pEnemy[nCnt] = nullptr;
			}
			continue;
		}

		//ゲーム上で生きているエネミーの数カウント
		m_nAliveEnemyCnt++;
	}

	if (m_nInterval > 0)
	{//インターバルがある時、このIFより下の処理をスキップ
		m_nInterval--;
		return;
	}

	if (m_nAliveEnemyCnt > 0)
	{//生きているエネミーがいる時、このIFより下の処理をスキップ
		return;
	}

	if (m_nGroupNum > m_nGroupMax)
	{
		return;
	}


	//エネミーの生成
	for (int nCnt = 0; nCnt < m_GroupData[m_nGroupNum].nEnemyMax; nCnt++)
	{
		if (m_pEnemy[nCnt] != nullptr)
		{
			assert(false);
		}

		//インスタンの生成
		CreateEnemy(nCnt, m_GroupData[m_nGroupNum].pEnemyMoveType[nCnt], m_GroupData[m_nGroupNum].pEnemyType[nCnt], m_GroupData[m_nGroupNum].pAddPos[nCnt]);
	}

	//現在のグループにインクリメント
	m_nGroupNum++;
}

//*****************************************************************************
// 描画処理
//*****************************************************************************
void CEnemyManager::Draw()
{
	for (int nCnt = 0; nCnt < ENEMY_MAX; nCnt++)
	{
		if (m_pEnemy[nCnt] != nullptr)
		{
			m_pEnemy[nCnt]->Draw();
		}
	}
}

//*****************************************************************************
// エネミーの生成
//*****************************************************************************
void CEnemyManager::CreateEnemy(int nNum, int nMoveType, EnemyType type, D3DXVECTOR3 addpos)
{
	if (m_pEnemy[nNum] != nullptr)
	{//NULLチェック
		assert(false);
	}

	CManager *pManager = GetManager();
	CGame *pGame = (CGame*)pManager->GetGameObject();

	//インスタンの生成
	switch (type)
	{
	case ENEMY_BASE:
		m_pEnemy[nNum] = new CEnemyBase;
		break;
	case ENEMY_01:
		m_pEnemy[nNum] = new CEnemy01;
		break;
	case ENEMY_02:
		m_pEnemy[nNum] = new CEnemy02;
		break;
	case ENEMY_03:
		m_pEnemy[nNum] = new CEnemy03;
		break;
	case ENEMY_04:
		m_pEnemy[nNum] = new CEnemy04;
		break;
	case ENEMY_05:
		m_pEnemy[nNum] = new CEnemy05;
		break;
	case ENEMY_06:
		m_pEnemy[nNum] = new CEnemy06;
		break;
	case BOSS_01:
		m_pEnemy[nNum] = new CEnemyBoss01;
		pGame->SetWarning();
		break;
	case BOSS_02:
		m_pEnemy[nNum] = new CEnemyBoss02;
		pGame->SetWarning();
		break;
	case BOSS_03:
		m_pEnemy[nNum] = new CEnemyBoss03;
		pGame->SetWarning();
		break;
	case BOSS_04:
		m_pEnemy[nNum] = new CEnemyBoss04;
		pGame->SetWarning();
		break;
	case BOSS_05:
		m_pEnemy[nNum] = new CEnemyBoss05;
		pGame->SetWarning();
		break;
	case BOSS_06:
		m_pEnemy[nNum] = new CEnemyBoss06;
		pGame->SetWarning();
		break;
	case MAX_TYPE:
	default:
		assert(false);
		break;
	}

	//初期化
	if (FAILED(m_pEnemy[nNum]->Init()))
	{
		assert(false);
	}


	//テクスチャ番号設定
	m_pEnemy[nNum]->SetTextIndex(m_nEnemyTextIndex[type]);
	//アンカーポイント情報の設定
	m_pEnemy[nNum]->SetEnemyData(m_EnemyMoveType[nMoveType]);
	//エネミーのタイプの設定
	m_pEnemy[nNum]->SetEnemyType(type);
	//エネミーのバレットの設定
	m_pEnemy[nNum]->SetBulletText(m_nBulletTextIndex);

	//初期POSセット
	m_pEnemy[nNum]->SetEnemyAddPos(addpos);
	m_pEnemy[nNum]->SetPos(m_EnemyMoveType[nMoveType].pAnchorPos[0] + addpos);
	m_pEnemy[nNum]->SetPolygon();
	m_pEnemy[nNum]->CalculatingUpToNextMovePoint();

	//ID登録
	m_pEnemy[nNum]->SetID(nNum);
}

//*****************************************************************************
// 当たり判定
//*****************************************************************************
bool CEnemyManager::Collision(D3DXVECTOR3 pos, float radius)
{
	for (int nCnt = 0;nCnt < ENEMY_MAX;nCnt++)
	{
		if (m_pEnemy[nCnt] == nullptr)
		{
			continue;
		}

		if (m_pEnemy[nCnt]->GetDied())
		{
			continue;
		}

		if (m_pEnemy[nCnt]->Collision(pos, radius))
		{
			return true;
		}
	}

	return false;
}

//*****************************************************************************
// エネミーの動きの見本登録
//*****************************************************************************
void CEnemyManager::SetEnemyMoveType(int nPosNumMax, D3DXVECTOR3 * pAnchorPos)
{
	if (m_nEnemyMoveTypeMax > ENEMY_MOVE_SOURCE_MAX)
	{
		assert(false);
	}

	if (m_EnemyMoveType[m_nEnemyMoveTypeMax].pAnchorPos != nullptr)
	{
		assert(false);
	}

	//posポインタの確保
	m_EnemyMoveType[m_nEnemyMoveTypeMax].pAnchorPos = new D3DXVECTOR3[nPosNumMax];
	//これから登録するPOSの数
	m_EnemyMoveType[m_nEnemyMoveTypeMax].nPosNumMax = nPosNumMax;

	for (int nCnt = 0; nCnt < nPosNumMax; nCnt++)
	{
		m_EnemyMoveType[m_nEnemyMoveTypeMax].pAnchorPos[nCnt] = pAnchorPos[nCnt];
	}

	m_nEnemyMoveTypeMax++;
}

//*****************************************************************************
// エネミーグループの登録
//*****************************************************************************
void CEnemyManager::SetGroupData(int nEnemyMax, int * pEnemyMove ,int * pEnemyType , D3DXVECTOR3 *pInitPos)
{
	if (m_nGroupMax > ENEMY_GROUP_MAX)
	{
		assert(false);
	}

	if (m_GroupData[m_nGroupMax].pEnemyMoveType != nullptr)
	{
		assert(false);
	}

	//intポインタの確保
	m_GroupData[m_nGroupMax].pEnemyMoveType = new int[nEnemyMax];
	m_GroupData[m_nGroupMax].pEnemyType = new EnemyType[nEnemyMax];
	m_GroupData[m_nGroupMax].pAddPos = new D3DXVECTOR3[nEnemyMax];

	//これから登録するエネミーの数
	m_GroupData[m_nGroupMax].nEnemyMax = nEnemyMax;

	for (int nCnt = 0; nCnt < nEnemyMax; nCnt++)
	{
		m_GroupData[m_nGroupMax].pEnemyMoveType[nCnt] = pEnemyMove[nCnt];
		m_GroupData[m_nGroupMax].pEnemyType[nCnt] = (EnemyType)pEnemyType[nCnt];
		m_GroupData[m_nGroupMax].pAddPos[nCnt] = pInitPos[nCnt] - m_EnemyMoveType[pEnemyMove[nCnt]].pAnchorPos[0];
	}

	m_nGroupMax++;
}

//*****************************************************************************
// エネミーのID指定での破棄
//*****************************************************************************
void CEnemyManager::UninitEnemyId(const int nId)
{
	if (m_pEnemy[nId] != nullptr)
	{
		m_pEnemy[nId]->Uninit();
		delete m_pEnemy[nId];
		m_pEnemy[nId] = nullptr;
	}
}
