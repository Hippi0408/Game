//=============================================================================
//
// player.cpp
// Author : koduna hirohito
//
//=============================================================================

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "player.h"
#include "main.h"
#include "input.h"
#include "manager.h"
#include "texture.h"
#include "bulletmanager.h"
#include "statgauge.h"
#include "manager.h"
#include "effect.h"
#include "subunit01.h"
#include "subunit02.h"
#include "subunit03.h"
#include "enemymanager .h"
#include "explosion.h"
#include "counter.h"
#include "sound.h"

// ポリゴンの幅
const float CPlayer::SIZE_PLAYER = 96.0f;
const float CPlayer::PLAYER_CENTER_SIZE = 20.0f;
// プレイヤーのMOVE
const float CPlayer::PLAYER_MOVE = 5.0f;
const float CPlayer::PLAYER_BOOST_MOVE = 12.0f;

// プレイヤーの中心のカラー
const D3DXCOLOR CPlayer::PLAYER_CENTER_COLOR[PLAYER_TYPE] = 
{
	D3DXCOLOR(1.0f,1.0f,1.0f,1.0f),
	D3DXCOLOR(1.0f,0.6f,0.7f,1.0f),
	D3DXCOLOR(0.5f,1.0f,0.0f,1.0f)
};

//*****************************************************************************
// コンストラクタ
//*****************************************************************************
CPlayer::CPlayer()
{
	m_nBulletTextIndex = 0;
	m_nEffectTextIndex = 0;
	m_nBulletCoolTime = 0;
	m_nInvincibleTime = 0;
	m_nBoostCnt = 0;
	m_bBoost = false;
	m_pLife = nullptr;
	m_pStamina = nullptr;
	m_pCenter = nullptr;
	m_pSubunit = nullptr;
	m_BoostVector = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
CPlayer::~CPlayer()
{
}

//*****************************************************************************
// 初期化
//*****************************************************************************
HRESULT CPlayer::Init()
{
	CManager *pManager = GetManager();

	m_nAirframe = pManager->GetAirframe();

	if (FAILED(C2DPolygon::Init()))
	{
		return -1;
	}

	SetPos(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f));
	SetDiagonalLine(SIZE_PLAYER, SIZE_PLAYER);
	SetFadeSpeed(0.1f);

	int nTexIndex;
	
	switch (m_nAirframe)
	{
	case 0:
		nTexIndex = CTexture::LoadTexture("data/TEXTURE/自機1.png");
		m_BulletCol = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		break;
	case 1:
		nTexIndex = CTexture::LoadTexture("data/TEXTURE/自機2.png");
		m_BulletCol = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);
		break;
	case 2:
		nTexIndex = CTexture::LoadTexture("data/TEXTURE/自機3.png");
		m_BulletCol = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
		break;
	default:
		break;
	}
	SetTextIndex(nTexIndex);

	m_nBulletTextIndex = CTexture::LoadTexture("data/TEXTURE/bullet.png");

	m_nEffectTextIndex = CTexture::LoadTexture("data/TEXTURE/effect.jpg");
	
	SetPolygon();

	CStatGauge::SStatGauge StatGauge;

	StatGauge.pos = D3DXVECTOR3(50.0f, 170.0f, 0.0f);
	StatGauge.rot = D3DXVECTOR3(0.0f, 0.0f, -D3DX_PI * 0.5f);
	StatGauge.color = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);
	StatGauge.fXSize = 25.0f;
	StatGauge.fYSize = 350.0f;
	StatGauge.nValueMax = 200;
	StatGauge.nRecoveryCntMaqx = 5;
	StatGauge.nRecovery = 1;

	m_pLife = new CStatGauge;
	if (FAILED(m_pLife->Init()))
	{
		return -1;
	}
	m_pLife->CreateStatBar(StatGauge);

	StatGauge.pos = D3DXVECTOR3(50.0f, 195.0f, 0.0f);
	StatGauge.rot = D3DXVECTOR3(0.0f, 0.0f, -D3DX_PI * 0.5f);
	StatGauge.color = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
	StatGauge.fXSize = 15.0f;
	StatGauge.fYSize = 350.0f;
	StatGauge.nValueMax = 100;
	StatGauge.nRecoveryCntMaqx = 10;
	StatGauge.nRecovery = 2;

	m_pStamina = new CStatGauge;
	if (FAILED(m_pStamina->Init()))
	{
		return -1;
	}
	m_pStamina->CreateStatBar(StatGauge);


	m_pCenter = new C2DPolygon;
	if (FAILED(m_pCenter->Init()))
	{
		return -1;
	}
	m_pCenter->SetPos(GetPos());
	nTexIndex = CTexture::LoadTexture("data/TEXTURE/自機中心.png");
	m_pCenter->SetTextIndex(nTexIndex);
	m_pCenter->SetDiagonalLine(PLAYER_CENTER_SIZE, PLAYER_CENTER_SIZE);
	m_pCenter->SetColor(PLAYER_CENTER_COLOR[0]);
	m_pCenter->SetPolygon();


	switch (m_nAirframe)
	{
	case 0:
		m_pSubunit = new CSubunit01;
		break;
	case 1:
		m_pSubunit = new CSubunit02;
		break;
	case 2:
		m_pSubunit = new CSubunit03;
		break;
	default:
		break;
	}
	
	if (FAILED(m_pSubunit->Init(GetPos())))
	{
		return -1;
	}

	return S_OK;
}

//*****************************************************************************
// 終了処理
//*****************************************************************************
void CPlayer::Uninit()
{
	if (m_pLife != nullptr)
	{
		m_pLife->Uninit();
		delete m_pLife;
		m_pLife = nullptr;
	}

	if (m_pStamina != nullptr)
	{
		m_pStamina->Uninit();
		delete m_pStamina;
		m_pStamina = nullptr;
	}

	if (m_pCenter != nullptr)
	{
		m_pCenter->Uninit();
		delete m_pCenter;
		m_pCenter = nullptr;
	}

	if (m_pSubunit != nullptr)
	{
		m_pSubunit->Uninit();
		delete m_pSubunit;
		m_pSubunit = nullptr;
	}
}

//*****************************************************************************
// 更新処理
//*****************************************************************************
void CPlayer::Update()
{
	if (m_pLife != nullptr)
	{
		if (m_pLife->GetGaugeState(CStatGauge::BreakTime))
		{
			m_pSubunit->BreakSubunit();
			CManager * pManager = GetManager();
			pManager->NextMode(TYPE_RESULT);
			return;
		}
		else if (m_pLife->ValueCheck())
		{
			m_pSubunit->BreakSubunit();
			CManager * pManager = GetManager();
			pManager->NextMode(TYPE_RESULT);
			//サウンド再生
			PlaySound(SOUND_LABEL_SE_EXPLOSION);
		}

		m_pLife->Update();

	}

	m_nBulletCoolTime++;
	CInput *pInput = CInput::GetKey();
	D3DXVECTOR3 vector = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	if (pInput->Press(KEY_LEFT))
	{
		vector.x -= 1.0f;
	}
	if (pInput->Press(KEY_RIGHT))
	{
		vector.x += 1.0f;
	}
	if (pInput->Press(KEY_UP))
	{
		vector.y -= 1.0f;
	}
	if (pInput->Press(KEY_DOWN))
	{
		vector.y += 1.0f;
	}

	D3DXVECTOR3 vectorjoy = pInput->VectorMoveJoyStick(0);
	D3DXVECTOR3 vectorcross1 = pInput->VectorMoveKey(0);
	D3DXVECTOR3 vectorcross2 = pInput->VectorMoveKey(1);

	if (vectorjoy.x != 0.0f || vectorjoy.y != 0.0f)
	{
		vector = vectorjoy;
	}
	else if (vectorcross1.x != 0.0f || vectorcross1.y != 0.0f)
	{
		vector = vectorcross1;
	}
	else if (vectorcross2.x != 0.0f || vectorcross2.y != 0.0f)
	{
		vector = vectorcross2;
	}


	if (pInput->Press(KEY_SHIFT) && !m_bBoost 
		&& m_pStamina->ValueCheck(20)
		&& !m_pStamina->GetGaugeState(CStatGauge::BreakTime))
	{
		if (vector.x == 0.0f && vector.y == 0.0f)
		{
			vector = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
		}
		m_pStamina->SetStatGauge(-20);
		m_bBoost = true;
		m_BoostVector = vector;
		m_nBoostCnt = 0;
		CCounter::AddCounter(-50);
	}

	if (m_bBoost)
	{
		vector = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		D3DXVec3Normalize(&m_BoostVector, &m_BoostVector);
		AddPos(m_BoostVector * PLAYER_BOOST_MOVE);

		if (m_nBoostCnt % 2)
		{
			CEffect::Effect effect;
			effect.fAttenuation = -0.05f;
			effect.fSizeX = SIZE_PLAYER;
			effect.fSizeY = SIZE_PLAYER;
			effect.nLife = 150;
			effect.nTextIndex = GetTextIndex();
			effect.pos = GetPos();
			effect.Color = m_BulletCol;

			CEffect::CreateEffect(effect);
		}

		m_nBoostCnt++;
	}
	else
	{
		D3DXVec3Normalize(&vector, &vector);
		AddPos(vector * PLAYER_MOVE);
	}

	if (m_nBoostCnt > BOOST_CNT)
	{
		m_bBoost = false;
		m_nBoostCnt = 0;
		m_BoostVector = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	D3DXVECTOR3 pos = GetPos();

	if (pos.y <= SCREEN_HEIGHT * 0.5f - SCREEN_GAME_HEIGHT * 0.5f)
	{
		pos.y = SCREEN_HEIGHT * 0.5f - SCREEN_GAME_HEIGHT * 0.5f;
	}
	else if (pos.y >= SCREEN_HEIGHT * 0.5f + SCREEN_GAME_HEIGHT * 0.5f)
	{
		pos.y = SCREEN_HEIGHT * 0.5f + SCREEN_GAME_HEIGHT * 0.5f;
	}

	if (pos.x <= SCREEN_WIDTH * 0.5f - SCREEN_GAME_WIDTH * 0.5f)
	{
		pos.x = SCREEN_WIDTH * 0.5f - SCREEN_GAME_WIDTH * 0.5f;
	}
	else if (pos.x >= SCREEN_WIDTH * 0.5f + SCREEN_GAME_WIDTH * 0.5f)
	{
		pos.x = SCREEN_WIDTH * 0.5f + SCREEN_GAME_WIDTH * 0.5f;
	}

	SetPos(pos);

	if (pInput->Press(KEY_SHOT) && m_nBulletCoolTime >= 10 && !m_bBoost && !m_pLife->ValueCheck())
	{
		m_nBulletCoolTime = 0;
		ShootBullet(D3DXVECTOR3(0.0f, -1.0f, 0.0f), 15.0f);
		m_pSubunit->SetBullet(m_nBulletTextIndex, pos);
	}

	if (m_nInvincibleTime > 0)
	{
		m_nInvincibleTime--;
	}
	else if (!m_bBoost)
	{
		if (CEnemyManager::Collision(pos, GetActualRadius()) && !m_pLife->ValueCheck())
		{
			CExplosion::CreateExplosion(pos);
			m_pLife->SetStatGauge(-30);
			CCounter::AddCounter(-50);
			m_nInvincibleTime = 10;
		}
		
	}

	C2DPolygon::Update();

	

	if (m_pStamina != nullptr)
	{
		m_pStamina->Update();
	}

	if (m_pCenter != nullptr)
	{
		m_pCenter->SetPos(pos);
		m_pCenter->Update();
	}

	if (m_pSubunit != nullptr)
	{
		m_pSubunit->Update(pos);
	}

	CEffect::Effect effect;
	effect.fAttenuation = -0.2f;
	effect.fSizeX = 25.0f;
	effect.fSizeY = 30.0f;
	effect.nLife = 7;
	effect.fScaleDown = -3.0f;
	effect.nTextIndex = 0;
	effect.pos = GetPos();
	effect.pos.y += 35.0f;
	effect.Color = D3DXCOLOR(0.6f, 0.3f, 0.3f, 1.0f);
	effect.move = D3DXVECTOR3(0.0f,5.0f,0.0f);
	effect.bAddColor = true;

	CEffect::CreateEffect(effect);
	CEffect::CreateEffect(effect);
	CEffect::CreateEffect(effect);
	CEffect::CreateEffect(effect);

}

//*****************************************************************************
// 描画処理
//*****************************************************************************
void CPlayer::Draw()
{
	if (m_pLife->GetGaugeState(CStatGauge::BreakTime))
	{
		return;
	}

	C2DPolygon::Draw();

	if (m_pSubunit != nullptr)
	{
		m_pSubunit->Draw();
	}

	if (m_pCenter != nullptr)
	{
		m_pCenter->Draw();
	}
}

void CPlayer::ShootBullet(D3DXVECTOR3 Vector, float fMove)
{
	Bullet bulletUp, bulletDown;
	bulletUp.fMove = fMove;
	bulletUp.fSize = 40.0f;
	bulletUp.nTextIndex = m_nBulletTextIndex;
	bulletUp.pos = GetPos();
	bulletUp.Type = BULLET_PLAYER;
	bulletUp.col = m_BulletCol;
	bulletUp.Vector = Vector;
	bulletDown = bulletUp;
	bulletDown.Vector *= -1.0f;

	switch (m_nAirframe)
	{
	case 0:
		CBulletManager::ShotBullet(bulletUp, BULLET_MOVE_00, 7, 20.0f);
		CBulletManager::ShotBullet(bulletDown, BULLET_MOVE_00, 2, 10.0f);
		break;
	case 1:
		CBulletManager::ShotBullet(bulletUp, BULLET_MOVE_00, 7, 20.0f);
		CBulletManager::ShotBullet(bulletDown, BULLET_MOVE_00, 5, 20.0f);
		break;
	case 2:
		CBulletManager::ShotBullet(bulletDown, BULLET_MOVE_00, 3, 10.0f);
		break;
	default:
		break;
	}
}

//*****************************************************************************
// 当たり判定
//*****************************************************************************
bool CPlayer::HetPlayer(D3DXVECTOR3 pos, float radius)
{
	if (Collision(pos, radius))
	{
		if (m_pLife != nullptr)
		{
			m_pLife->SetStatGauge(-10);
			//サウンド再生
			PlaySound(SOUND_LABEL_SE_PLAYER_DAMAGE);
			CCounter::AddCounter(-1);
		}
		return true;
	}
	return false;
}

bool CPlayer::Collision(D3DXVECTOR3 pos, float radius)
{
	if (m_nInvincibleTime > 0 || m_pLife->GetGaugeState(CStatGauge::BreakTime))
	{
		return false;
	}

	D3DXVECTOR3 mypos = GetPos();

	float fActualRadius = m_pCenter->GetActualRadius();

	//２この物体の半径同士の和
	float fDiff = fActualRadius + radius;

	//計算用変数
	float fCalculationX, fCalculationZ;

	//Xの差分
	fCalculationX = pos.x - mypos.x;
	//Yの差分
	fCalculationZ = pos.y - mypos.y;

	//現在の２点の距離
	float fLength = sqrtf(fCalculationX * fCalculationX + fCalculationZ * fCalculationZ);

	//２この物体の半径同士の和より現在の２点の距離が小さいかどうか
	if (fDiff >= fLength)
	{
		if (!m_bBoost)
		{
			//当たった
			return true;
		}
	}

	//当たってない
	return false;
}



//*****************************************************************************
// 使ってないが書いて置く処理
//*****************************************************************************
void CPlayer::SetUp(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move)
{

}

bool CPlayer::IsUnused()
{
	return false;
}


