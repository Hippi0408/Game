//=============================================================================
//
// BulletSpecial01.h
// Author : koduna hirohito
//
//=============================================================================
#ifndef _BULLET_SPECIAL01_H_			//���̃}�N����`������Ȃ�������
#define _BULLET_SPECIAL01_H_			//2�d�C���N���[�h�h�~�̃}�N����`

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "bulletbase.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CBulletSpecial01 : public CBulletBase
{
private:
	static const int DAMAGE_COOL_TIME = 60;
	static const int BULLET_LIFE = 5;
public:

	CBulletSpecial01();//�R���X�g���N�^
	~CBulletSpecial01() override;//�f�X�g���N�^

	bool IsUnused() override;//�I������
	void BulletRot() override;//�e�̌���
	void BulletMove() override;//�e�̓���
private:
	int m_nDamageCoolTime;
	int m_nLife;
};

#endif