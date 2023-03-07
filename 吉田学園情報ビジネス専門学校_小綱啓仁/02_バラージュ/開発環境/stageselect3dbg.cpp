//=============================================================================
//
// 処理 [game3dbg.cpp]
// Author : KOZUNA HIROHITO

//
//=============================================================================

//-----------------------------------------------------------------------------
//インクルードファイル
//-----------------------------------------------------------------------------
#include "stageselect3dbg.h"
#include "3dpolygon.h"
#include "3dobject.h"
#include "read.h"
#include "input.h"
#include "texture.h"

const D3DXVECTOR3 CStageSelect3DBG::STANDARD_3DBG_MODEL = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
const float CStageSelect3DBG::PLANET_BETWEEN_DISTANCE = 200.0f;

//*****************************************************************************
//コンストラクタ
//*****************************************************************************
CStageSelect3DBG::CStageSelect3DBG()
{
	for (int nCnt = 0; nCnt < StageNum_MAX; nCnt++)
	{
		m_pBgModel[nCnt] = nullptr;
		m_Rotation[nCnt] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//自転
		m_RotationMove[nCnt] = D3DXVECTOR3(0.0f, -0.0025f, 0.0f);		//自転速度
	}
	m_BgObjSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Move = D3DXVECTOR3(0.0f, 0.0f, -0.2f);
	m_ObjPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_DestObjPos = m_ObjPos;
	m_pBG = nullptr;
}

//*****************************************************************************
//デストラクタ
//*****************************************************************************
CStageSelect3DBG::~CStageSelect3DBG()
{
}

//*****************************************************************************
//初期化
//*****************************************************************************
HRESULT CStageSelect3DBG::Init(void)
{
	

	m_pRead = new CRead;
	m_pRead->ReadModel(StageSelectModel);

	D3DXVECTOR3 NestPos = STANDARD_3DBG_MODEL;

	for (int nCnt = 0; nCnt < StageNum_MAX; nCnt++)
	{
		m_pBgModel[nCnt] = new C3DObject;

		if (FAILED(m_pBgModel[nCnt]->Init()))
		{
			return -1;
		}
		NestPos.x = m_ObjPos.x + PLANET_BETWEEN_DISTANCE * nCnt;
		m_pBgModel[nCnt]->SetRot(m_Rotation[nCnt]);
		m_pBgModel[nCnt]->Set3DObject(nCnt, NestPos);
	}

	//BG3D
	m_pBG = new C3DPolygon;
	if (FAILED(m_pBG->Init()))
	{
		return -1;
	}
	int nIndex = CTexture::LoadTexture("data/TEXTURE/galaxy.png");
	m_pBG->SetPos(D3DXVECTOR3(-30.0f, -20.0f, 500.0f));
	m_pBG->SetRot(D3DXVECTOR3(D3DXToRadian(-70), D3DXToRadian(0), D3DXToRadian(0)));
	m_pBG->SetTextIndex(nIndex);
	m_pBG->SetDiagonalLine(800.0f, 800.0f);
	m_pBG->SetPolygon();

	return S_OK;
}

//*****************************************************************************
//終了処理
//*****************************************************************************
void CStageSelect3DBG::Uninit(void)
{
	for (int nCnt = 0; nCnt < StageNum_MAX; nCnt++)
	{
		if (m_pBgModel[nCnt] != nullptr)
		{
			m_pBgModel[nCnt]->Uninit();
			delete m_pBgModel[nCnt];
			m_pBgModel[nCnt] = nullptr;
		}
	}

	//外部ファイル
	if (m_pRead != nullptr)
	{
		delete m_pRead;
		m_pRead = nullptr;
	}

	//背景ポリゴン
	if (m_pBG != nullptr)
	{
		delete m_pBG;
		m_pBG = nullptr;
	}

	C3DObject::UninitAllModel();
}

//*****************************************************************************
//更新処理
//*****************************************************************************
void CStageSelect3DBG::Update(void)
{
	if (m_ObjPos.x < m_DestObjPos.x)
	{
		m_ObjPos.x += 5.0f;
	}
	else if (m_ObjPos.x > m_DestObjPos.x)
	{
		m_ObjPos.x -= 5.0f;
	}

	D3DXVECTOR3 NestPos = m_ObjPos;

	for (int nCnt = 0; nCnt < StageNum_MAX; nCnt++)
	{
		NestPos.x = m_ObjPos.x + PLANET_BETWEEN_DISTANCE * nCnt;
		m_pBgModel[nCnt]->AddRot(m_RotationMove[nCnt]);
		m_pBgModel[nCnt]->SetPos(NestPos);
	}
}

//*****************************************************************************
//描画処理
//*****************************************************************************
void CStageSelect3DBG::Draw()
{
	for (int nCnt = 0; nCnt < StageNum_MAX; nCnt++)
	{
		if (m_pBgModel[nCnt] != nullptr)
		{
			m_pBgModel[nCnt]->Draw();
		}
	}

	//背景ポリゴン
	if (m_pBG != nullptr)
	{
		m_pBG->Draw();
	}
}

void CStageSelect3DBG::AddPos(float fAdd)
{
	m_ObjPos.x += fAdd;
	m_DestObjPos = m_ObjPos;

	D3DXVECTOR3 NestPos = m_ObjPos;

	for (int nCnt = 0; nCnt < StageNum_MAX; nCnt++)
	{
		NestPos.x = m_ObjPos.x + PLANET_BETWEEN_DISTANCE * nCnt;
		m_pBgModel[nCnt]->AddRot(m_RotationMove[nCnt]);
		m_pBgModel[nCnt]->SetPos(NestPos);
	}
}

void CStageSelect3DBG::SetPos(D3DXVECTOR3 pos)
{
	m_ObjPos = pos;
	m_DestObjPos = m_ObjPos;

	D3DXVECTOR3 NestPos = m_ObjPos;

	for (int nCnt = 0; nCnt < StageNum_MAX; nCnt++)
	{
		NestPos.x = m_ObjPos.x + PLANET_BETWEEN_DISTANCE * nCnt;
		m_pBgModel[nCnt]->AddRot(m_RotationMove[nCnt]);
		m_pBgModel[nCnt]->SetPos(NestPos);
	}
}
