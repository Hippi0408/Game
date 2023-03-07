//=============================================================================
//
// 3dobject.cpp
// Author : koduna hirohito
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "3dobject.h"
#include "manager.h"

C3DObject::ModelPattern C3DObject::m_ModelPattern[MODEL_PATTERN_MAX] = {};
//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
C3DObject::C3DObject()
{
	ZeroMemory(&m_Model, sizeof(m_Model));
	m_fSize = 1.0f;
}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
C3DObject::~C3DObject()
{
}

//*****************************************************************************
// ������
//*****************************************************************************
HRESULT C3DObject::Init()
{
	ZeroMemory(&m_Model, sizeof(m_Model));
	m_fSize = 1.0f;

	return S_OK;
}

//*****************************************************************************
// �I������
//*****************************************************************************
void C3DObject::Uninit()
{
}

//*****************************************************************************
// �X�V����
//*****************************************************************************
void C3DObject::Update()
{

}

//*****************************************************************************
// �`�揈��
//*****************************************************************************
void C3DObject::Draw()
{
	CManager *pManager = GetManager();

	LPDIRECT3DDEVICE9 pD3DDevice = nullptr;

	pD3DDevice = pManager->GetDeviceManager();


	D3DXMATRIX mtxRoot;					//�匳�̐e�̃��[���h�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans,mtxScaling;		//�v�Z�p�̃}�g���b�N�X
	D3DMATERIAL9 matDef;			//���݂̃}�e���A���ۑ�
	D3DXMATERIAL *pMat;				//�}�e���A���f�[�^�ւ̃|�C���^

	//���[���h�}�g���b�N�X�̏������i�匳�̐e�j
	D3DXMatrixIdentity(&mtxRoot);

	//�T�C�Y�̕ύX
	D3DXMatrixScaling(&mtxScaling,m_fSize, m_fSize, m_fSize);
	D3DXMatrixMultiply(&mtxRoot, &mtxRoot, &mtxScaling);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_Model.rot.y, m_Model.rot.x, m_Model.rot.z);
	D3DXMatrixMultiply(&mtxRoot, &mtxRoot, &mtxRot);

	//�ʒu�̔��f
	D3DXMatrixTranslation(&mtxTrans, m_Model.pos.x, m_Model.pos.y, m_Model.pos.z);
	D3DXMatrixMultiply(&mtxRoot, &mtxRoot, &mtxTrans);

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_Model.mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, 0.0f, 0.0f, 0.0f);

	D3DXMatrixMultiply(&m_Model.mtxWorld, &m_Model.mtxWorld, &mtxRot);

	//�ʒu�̔��f
	D3DXMatrixTranslation(&mtxTrans, m_Model.posChildren.x, m_Model.posChildren.y, m_Model.posChildren.z);
	D3DXMatrixMultiply(&m_Model.mtxWorld, &m_Model.mtxWorld, &mtxTrans);


	//���f���̃}�g���b�N�X�@���@�e�̃��[���h�}�g���b�N�X
	D3DXMatrixMultiply(&m_Model.mtxWorld, &m_Model.mtxWorld, &mtxRoot);


	//���[���h�}�g���b�N�X�̐ݒ�
	pD3DDevice->SetTransform(D3DTS_WORLD, &m_Model.mtxWorld);

	//���݂̃}�e���A����ۑ�
	pD3DDevice->GetMaterial(&matDef);

	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)m_ModelPattern[m_Model.nPattn].pBuffMatModel->GetBufferPointer();

	//�e�N�X�`���̐ݒ�
	pD3DDevice->SetTexture(0, NULL);

	for (int nCntMat = 0; nCntMat < (int)m_ModelPattern[m_Model.nPattn].nNumMatModel; nCntMat++)
	{
		//�}�e���A���̐ݒ�
		pD3DDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		// �e�N�X�`���̐ݒ�
		pD3DDevice->SetTexture(0, m_ModelPattern[m_Model.nPattn].pTexture[nCntMat]);

		//���f���p�[�c�̕`��
		m_ModelPattern[m_Model.nPattn].pMeshModel->DrawSubset(nCntMat);
	}

	//�ۑ����Ă����}�e���A����߂�
	pD3DDevice->SetMaterial(&matDef);

}

//*****************************************************************************
// �RD�I�u�W�F�N�g�̔z�u
//*****************************************************************************
void C3DObject::Set3DObject(int nPattn, D3DXVECTOR3 pos)
{
	int nNumVix;		//���_��
	DWORD sizeFVF;		//���_�t�H�[�}�b�g�̃T�C�Y
	BYTE *pVtxBuff;		//���_�o�b�t�@�ւ̃|�C���^

	m_Model.pos = pos;
	m_Model.nPattn = nPattn;

	//���f���̃T�C�Y�̔�r�p�����l
	m_Model.vtxMax = D3DXVECTOR3(-FLT_MAX, -FLT_MAX, -FLT_MAX);
	m_Model.vtxMin = D3DXVECTOR3(FLT_MAX, FLT_MAX, FLT_MAX);

	//���_���̎擾
	nNumVix = m_ModelPattern[m_Model.nPattn].pMeshModel->GetNumVertices();

	//���_�t�H�[�}�b�g�擾
	sizeFVF = D3DXGetFVFVertexSize(m_ModelPattern[m_Model.nPattn].pMeshModel->GetFVF());

	//���_���b�N
	m_ModelPattern[m_Model.nPattn].pMeshModel->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	//���ׂĂ̒��_POS�̎擾
	for (int nCntVtx = 0; nCntVtx < nNumVix; nCntVtx++)
	{
		//���_���W�̑��
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

		if (m_Model.vtxMax.x < vtx.x)
		{//X
			m_Model.vtxMax.x = vtx.x;
		}
		if (m_Model.vtxMin.x > vtx.x)
		{
			m_Model.vtxMin.x = vtx.x;
		}

		if (m_Model.vtxMax.y < vtx.y)
		{//Y
			m_Model.vtxMax.y = vtx.y;
		}
		if (m_Model.vtxMin.y > vtx.y)
		{
			m_Model.vtxMin.y = vtx.y;
		}

		if (m_Model.vtxMax.z < vtx.z)
		{//Z
			m_Model.vtxMax.z = vtx.z;
		}
		if (m_Model.vtxMin.z > vtx.z)
		{
			m_Model.vtxMin.z = vtx.z;
		}

		//���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
		pVtxBuff += sizeFVF;
	}

	//���_�A�����b�N
	m_ModelPattern[m_Model.nPattn].pMeshModel->UnlockVertexBuffer();
}

//*****************************************************************************
// ���f���̃Z�b�g
//*****************************************************************************
void C3DObject::SetModel(ModelPattern *pModel)
{
	for (int nCnt = 0; nCnt < MODEL_PATTERN_MAX; nCnt++)
	{
		if (!m_ModelPattern[nCnt].bUse)
		{
			m_ModelPattern[nCnt] = *pModel;
			m_ModelPattern[nCnt].bUse = true;
			break;
		}
	}
}

//*****************************************************************************
// ���f���̑S�I������
//*****************************************************************************
void C3DObject::UninitAllModel()
{
	for (int nCnt = 0; nCnt < MODEL_PATTERN_MAX; nCnt++)
	{
		for (int i = 0; i < (int)m_ModelPattern[nCnt].nNumMatModel; i++)
		{
			if (m_ModelPattern[nCnt].pTexture[i] != nullptr)
			{// �e�N�X�`���̉��
				m_ModelPattern[nCnt].pTexture[i]->Release();
				m_ModelPattern[nCnt].pTexture[i] = nullptr;
			}
		}

		//���b�V���̔j��
		if (m_ModelPattern[nCnt].pMeshModel != nullptr)
		{
			m_ModelPattern[nCnt].pMeshModel->Release();
			m_ModelPattern[nCnt].pMeshModel = nullptr;
		}

		//�}�e���A���̔j��
		if (m_ModelPattern[nCnt].pBuffMatModel != nullptr)
		{
			m_ModelPattern[nCnt].pBuffMatModel->Release();
			m_ModelPattern[nCnt].pBuffMatModel = nullptr;
		}

	}

	ZeroMemory(&m_ModelPattern, sizeof(m_ModelPattern));
}

//*****************************************************************************
// ���f���̃T�C�Y
//*****************************************************************************
D3DXVECTOR3 C3DObject::GetSize()
{
	D3DXVECTOR3 size;

	D3DXVECTOR3 minpos, maxpos;

	minpos = m_Model.pos + m_Model.vtxMin;

	maxpos = m_Model.pos + m_Model.vtxMax;

	size = maxpos - minpos;
	
	return size;
}