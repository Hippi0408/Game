//=============================================================================
//
// enemymanager .h
// Author : koduna hirohito
//
//=============================================================================
#ifndef _ENEMY_MANAGER_H_			//���̃}�N����`������Ȃ�������
#define _ENEMY_MANAGER_H_			//2�d�C���N���[�h�h�~�̃}�N����`

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "main.h"
#include "enemydata.h"
//*****************************************************************************
// �O���錾
//*****************************************************************************
class CEnemyBase;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CEnemyManager
{
private:
	// �G�l�~�[�̍ő吔
	static const int ENEMY_MAX = 64;

	// �G�l�~�[�̓����̌��{�̍ő吔
	static const int ENEMY_MOVE_SOURCE_MAX = 30;

	// �G�l�~�[�O���[�v�̍ő吔
	static const int ENEMY_GROUP_MAX = 20;

	//�Q�[���J�n���A�ŏ��̃O���[�v���o��܂ł̊�
	static const int FIRST_INTERVAL = 60;

public:
	CEnemyManager();
	~CEnemyManager();

	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();

	void CreateEnemy(int nNum,int nMoveType,EnemyType type, D3DXVECTOR3 addpos);
	static bool Collision(D3DXVECTOR3 pos, float radius);

	void SetEnemyMoveType(int nPosNumMax, D3DXVECTOR3 *pAnchorPos);

	void SetGroupData(int nEnemyMax, int * pEnemyMove, int * pEnemyType, D3DXVECTOR3 *pInitPos);
	static void UninitEnemyId(const int nId);

	static int GetBulletTextIndex() { return m_nBulletTextIndex; }

private:
	static int m_nBulletTextIndex;
	static CEnemyBase *m_pEnemy[ENEMY_MAX];
	int m_nEnemyTextIndex[MAX_TYPE];
	
	//�O���[�v���o��܂ł̃C���^�[�o��
	int m_nInterval;

	//�Q�[����Ő����Ă���G�l�~�[�̐�
	int m_nAliveEnemyCnt;

	//�G�l�~�[�O���[�v���
	int m_nGroupNum = 0;				//���ݐ������̓G�O���[�v�̐�
	int m_nGroupMax;					//�o�^�G�O���[�v�̐�
	SEnemyGroupData m_GroupData[ENEMY_GROUP_MAX];		//�O���[�v�̑S�f�[�^

	int m_nEnemyMoveTypeMax; //�G�l�~�[�̓o�^���������̐�
	SEnemyData m_EnemyMoveType[ENEMY_MOVE_SOURCE_MAX];	//�G�l�~�[�̓����̌�
};

#endif