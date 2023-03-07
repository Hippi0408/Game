//=============================================================================
//
// rankinginput.cpp
// Author : koduna hirohito
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "rankinginput.h"
#include "beeline.h"
#include "input.h"
#include "result.h"
#include "manager.h"
#include "ranking.h"
#include "sound.h"

const float CRankingInput::SIZE_SET_MAME = 60.0f;
const float CRankingInput::SIZE_SET_SELECT_MAME = CRankingInput::SIZE_SET_MAME * 2.0f;
//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
CRankingInput::CRankingInput()
{
	m_pPLName = nullptr;

	ZeroMemory(m_pSetName,sizeof(m_pSetName));

	m_Pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_nCurrentValue = 0;//�I�𒆂̐��l
	m_nSetNameNum = 0;
	m_bChange = false;
	m_bUp = false;
	m_bSetEnd = false;
	m_nFpsCnt = 0;
	for (int nCnt = 0; nCnt < CName::MAX_NAME_LENGTH; nCnt++)
	{
		m_aPLNameIndex[nCnt] = -1;
	}
}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
CRankingInput::~CRankingInput()
{

}

//*****************************************************************************
// ������
//*****************************************************************************
HRESULT CRankingInput::Init(D3DXVECTOR3 pos)
{
	m_Pos = pos;

	m_pPLName = new CName;
	if (FAILED(m_pPLName->Init()))
	{
		return -1;
	}
	m_pPLName->SetSize(SIZE_SET_SELECT_MAME);
	m_pPLName->SetPos(pos);

	int nTex = m_pPLName->GetTextureIndex();

	float fTopPosY = pos.y - SIZE_SET_MAME * SET_PL_MAME_HALF;

	for (int nCnt = 0; nCnt < SET_PL_MAME; nCnt++)
	{
		if (m_pSetName[nCnt] != nullptr)
		{
			continue;
		}

		m_pSetName[nCnt] = new CBeeline;
		if (FAILED(m_pSetName[nCnt]->Init()))
		{
			return -1;
		}

		if (SET_PL_MAME_HALF > nCnt)
		{
			m_pSetName[nCnt]->SetPos(D3DXVECTOR3(pos.x, pos.y + SIZE_SET_MAME * nCnt, 0.0f));
		}
		else
		{
			int nCntNum = nCnt % SET_PL_MAME_HALF;
			m_pSetName[nCnt]->SetPos(D3DXVECTOR3(pos.x, fTopPosY + SIZE_SET_MAME * nCntNum, 0.0f));
		}

		if (nCnt == 0)
		{
			m_pSetName[nCnt]->SetSize(SIZE_SET_SELECT_MAME);
		}
		else
		{
			m_pSetName[nCnt]->SetSize(SIZE_SET_MAME);

		}
		m_pSetName[nCnt]->SetTextureIndex(nTex);
		m_pSetName[nCnt]->SetBeeline(nCnt);
	}

	//�}�l�[�W���[�̃A�h���X
	CManager *pManager = GetManager();
	//���U���g�̃A�h���X
	CResult *pResult = (CResult*)pManager->GetGameObject();
	//�����L���O�̃A�h���X
	CRanking *pRanking = pResult->GetRanking();

	m_bSetEnd = pRanking->PLNewRanking();

	return S_OK;
}

//*****************************************************************************
// �I������
//*****************************************************************************
void CRankingInput::Uninit()
{
	for (int nCnt = 0; nCnt < SET_PL_MAME; nCnt++)
	{
		if (m_pSetName[nCnt] == nullptr)
		{
			continue;
		}

		m_pSetName[nCnt]->Uninit();

		delete m_pSetName[nCnt];
		m_pSetName[nCnt] = nullptr;
	}


	if (m_pPLName != nullptr)
	{
		m_pPLName->Uninit();

		delete m_pPLName;
		m_pPLName = nullptr;
	}
}

//*****************************************************************************
// �X�V����
//*****************************************************************************
bool CRankingInput::Update()
{
	CInput *pInput = CInput::GetKey();
	//�}�l�[�W���[�̃A�h���X
	CManager *pManager = GetManager();
	//���U���g�̃A�h���X
	CResult *pResult = (CResult*)pManager->GetGameObject();
	//�����L���O�̃A�h���X
	CRanking *pRanking = pResult->GetRanking();


	if (m_bSetEnd)
	{//�ŏI����
		if (pInput->Trigger(KEY_DECISION))
		{
			//�T�E���h�Đ�
			PlaySound(SOUND_LABEL_SE_DETERMINATION);
			pRanking->SetPLNewData(&m_aPLNameIndex[0]);
			pRanking->SaveRanking();
			pManager->SetScore(0);
			return true;
		}

	}

	if (pInput->Trigger(KEY_BACK) && !m_bChange && m_nSetNameNum > 0)
	{//�ꕶ���߂�
		if (m_nSetNameNum >= CName::MAX_NAME_LENGTH)
		{
			m_Pos.x -= SIZE_SET_SELECT_MAME * CName::NAME_SIZE_ADJUSTMENT;
			m_pPLName->BreakBeeline();
			m_nSetNameNum--;
		}
		//�T�E���h�Đ�
		PlaySound(SOUND_LABEL_SE_BACK);
		m_Pos.x -= SIZE_SET_SELECT_MAME * CName::NAME_SIZE_ADJUSTMENT;
		m_pPLName->BreakBeeline();
		m_nSetNameNum--;
		m_aPLNameIndex[m_nSetNameNum] = -1;
		m_bSetEnd = false;
	}

	if (m_bSetEnd)
	{//�l�[���̑ł����݂��I������炱���肵���̍X�V�������X�L�b�v
		return false;
	}
	
	if (pInput->Trigger(KEY_DECISION) && !m_bChange)
	{//�����̌���
		
		if (m_nCurrentValue == CName::MAX_NAME_INDEX - 1 && m_nSetNameNum == 0)
		{//�����Ȃ�END���o���Ȃ��悤�ɂ��鏈��
			return false;
		}

		//�T�E���h�Đ�
		PlaySound(SOUND_LABEL_SE_DETERMINATION);
		m_aPLNameIndex[m_nSetNameNum] = m_nCurrentValue;
		m_pPLName->SetName(m_nCurrentValue);
		m_Pos.x += SIZE_SET_SELECT_MAME * CName::NAME_SIZE_ADJUSTMENT;

		if (m_nCurrentValue == CName::MAX_NAME_INDEX - 1)
		{
			m_bSetEnd = true;
			m_aPLNameIndex[m_nSetNameNum] = -1;
		}
		m_nSetNameNum++;

	}

	if (pInput->Press(KEY_UP) && !m_bChange)
	{//�����̕ύX��
	 //�T�E���h�Đ�
		PlaySound(SOUND_LABEL_SE_UP_DOWN);
		m_nCurrentValue++;
		m_bChange = true;
		m_bUp = true;
	}
	else if (pInput->Press(KEY_DOWN) && !m_bChange)
	{//�����̕ύX��
	 //�T�E���h�Đ�
		PlaySound(SOUND_LABEL_SE_UP_DOWN);
		m_nCurrentValue--;
		m_bChange = true;
	}

	if (m_nCurrentValue >= SET_PL_MAME)
	{//�I�𕶎��̏���ݒ�
		m_nCurrentValue = 0;
	}
	else if (m_nCurrentValue < 0)
	{//�I�𕶎��̉����ݒ�
		m_nCurrentValue = SET_PL_MAME - 1;
	}

	//�����̕ύX�̈ړ���
	float fMove = 0.0f;

	if (m_bChange)
	{//�ύX���������ۂ̈ړ��ʂ̐ݒ�
		fMove = SIZE_SET_MAME / CHANGE_CNT;

		if (m_bUp)
		{
			fMove *= -1.0f;
		}
	}

	for (int nCnt = 0; nCnt < SET_PL_MAME; nCnt++)
	{//�����̍X�V
		if (m_pSetName[nCnt] == nullptr)
		{//NULL�`�F�b�N
			continue;
		}
		//�����̃X�N���[���ړ�
		m_pSetName[nCnt]->AddPos(D3DXVECTOR3(0.0f, fMove, 0.0f));

		if (nCnt == m_nCurrentValue)
		{//�I�𒆂̕����̃T�C�Y��傫������
			m_pSetName[nCnt]->SetSize(SIZE_SET_SELECT_MAME);
		}
		else
		{//�I�𒆂̕����ȊO��ʏ�T�C�Y�̕ύX
			m_pSetName[nCnt]->SetSize(SIZE_SET_MAME);

		}
		//�����`��|���S����GETPOS
		D3DXVECTOR3 CheckPos = m_pSetName[nCnt]->GetPos();

		if (CheckPos.y >= m_Pos.y + SIZE_SET_MAME * SET_PL_MAME_HALF)
		{//���ȏ㉺�ɍs�������Ɉړ�
			D3DXVECTOR3 pos = D3DXVECTOR3(m_Pos.x, m_Pos.y - SIZE_SET_MAME * SET_PL_MAME_HALF, 0.0f);
			m_pSetName[nCnt]->SetPos(pos);
		}
		else if (CheckPos.y <= m_Pos.y - SIZE_SET_MAME * SET_PL_MAME_HALF)
		{//���ȏ��ɍs�����牺�Ɉړ�
			D3DXVECTOR3 pos = D3DXVECTOR3(m_Pos.x, m_Pos.y + SIZE_SET_MAME * SET_PL_MAME_HALF, 0.0f);
			m_pSetName[nCnt]->SetPos(pos);
		}

		if (CheckPos.x != m_Pos.x)
		{//�ݒ肷�镶����X���̕ύX�����鎞�ύX����
			D3DXVECTOR3 pos = D3DXVECTOR3(m_Pos.x, CheckPos.y, 0.0f);
			m_pSetName[nCnt]->SetPos(pos);
		}
		
	}

	if (m_nSetNameNum >= CName::MAX_NAME_LENGTH - 1 && !m_bSetEnd)
	{//�l�[���̐ݒ肪�I��
		m_bSetEnd = true;
		m_pPLName->SetName(CName::MAX_NAME_INDEX - 1);
		m_Pos.x += SIZE_SET_SELECT_MAME * CName::NAME_SIZE_ADJUSTMENT;
		m_nSetNameNum++;
	}

	if (!m_bChange)
	{//�����̃X�N���[���ړ����Ȃ��Ƃ������艺�̍X�V���X�L�b�v����
		return false;
	}

	//�I�𒆂̕�����ύX
	m_nFpsCnt++;


	if (m_nFpsCnt >= CHANGE_CNT)
	{//�����̃X�N���[���ړ��̃t���[���`�F�b�N
		m_bChange = false;
		m_bUp = false;
		m_nFpsCnt = 0;
	}

	return false;
}

//*****************************************************************************
// �`�揈��
//*****************************************************************************
void CRankingInput::Draw()
{
	if (m_pPLName != nullptr)
	{
		m_pPLName->Draw();
	}

	if (m_bSetEnd)
	{
		return;
	}

	for (int nCnt = 0; nCnt < SET_PL_MAME; nCnt++)
	{
		if (m_pSetName[nCnt] == nullptr || nCnt == m_nCurrentValue)
		{
			continue;
		}

		D3DXVECTOR3 pos = m_pSetName[nCnt]->GetPos();
		if (pos.y >= m_Pos.y - SIZE_SET_MAME * SELECT_PL_MAME_HALF - SIZE_SET_MAME / 2.0f
			&& pos.y <= m_Pos.y + SIZE_SET_MAME * SELECT_PL_MAME_HALF + SIZE_SET_MAME / 2.0f)
		{
			m_pSetName[nCnt]->Draw();
		}
	}

	if (m_pSetName[m_nCurrentValue] != nullptr)
	{
		m_pSetName[m_nCurrentValue]->Draw();
	}
	
}