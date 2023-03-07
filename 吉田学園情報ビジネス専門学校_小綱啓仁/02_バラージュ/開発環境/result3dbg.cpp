//=============================================================================
//
// ���� [result3dbg.cpp]
// Author : KOZUNA HIROHITO

//
//=============================================================================

//-----------------------------------------------------------------------------
//�C���N���[�h�t�@�C��
//-----------------------------------------------------------------------------
#include "result3dbg.h"
#include "3dpolygon.h"
#include "3dobject.h"
#include "read.h"
#include "input.h"
#include "texture.h"
#include "manager.h"

const D3DXVECTOR3 CResult3DBG::STANDARD_3DBG_MODEL = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//*****************************************************************************
//�R���X�g���N�^
//*****************************************************************************
CResult3DBG::CResult3DBG()
{

	m_pBgModel = nullptr;
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//���]
	m_RotationMove = D3DXVECTOR3(0.0f, -0.0025f, 0.0f);		//���]���x
	m_pBG = nullptr;
}

//*****************************************************************************
//�f�X�g���N�^
//*****************************************************************************
CResult3DBG::~CResult3DBG()
{
}

//*****************************************************************************
//������
//*****************************************************************************
HRESULT CResult3DBG::Init(void)
{
	CManager *pManager = GetManager();

	m_pRead = new CRead;
	m_pRead->ReadModel(StageSelectModel);

	m_pBgModel = new C3DObject;

	if (FAILED(m_pBgModel->Init()))
	{
		return -1;
	}
	m_pBgModel->SetRot(m_Rotation);
	m_pBgModel->Set3DObject(pManager->GetStage(), STANDARD_3DBG_MODEL);


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
//�I������
//*****************************************************************************
void CResult3DBG::Uninit(void)
{

	if (m_pBgModel != nullptr)
	{
		m_pBgModel->Uninit();
		delete m_pBgModel;
		m_pBgModel = nullptr;
	}


	//�O���t�@�C��
	if (m_pRead != nullptr)
	{
		delete m_pRead;
		m_pRead = nullptr;
	}

	//�w�i�|���S��
	if (m_pBG != nullptr)
	{
		delete m_pBG;
		m_pBG = nullptr;
	}

	C3DObject::UninitAllModel();
}

//*****************************************************************************
//�X�V����
//*****************************************************************************
void CResult3DBG::Update(void)
{
	m_pBgModel->AddRot(m_RotationMove);
}

//*****************************************************************************
//�`�揈��
//*****************************************************************************
void CResult3DBG::Draw()
{

	if (m_pBgModel != nullptr)
	{
		m_pBgModel->Draw();
	}


	//�w�i�|���S��
	if (m_pBG != nullptr)
	{
		m_pBG->Draw();
	}
}
