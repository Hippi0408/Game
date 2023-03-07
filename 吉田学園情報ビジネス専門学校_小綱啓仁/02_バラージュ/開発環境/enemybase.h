//=============================================================================
//
// enemybase.h
// Author : koduna hirohito
//
//=============================================================================
#ifndef _ENEMYBASE_H_			//このマクロ定義がされなかったら
#define _ENEMYBASE_H_			//2重インクルード防止のマクロ定義

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "2dpolygon.h"
#include "enemydata.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CRead;
enum EnemyType;
struct SEnemyData;
struct Bullet;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CEnemyBase : public C2DPolygon
{
private:
	static const float ENEMY_BASE_SIZE;
	static const float ENEMY_BASE_MOVE;
	static const int ENEMY_ATTACK_CNT = 30;

public:
	CEnemyBase();
	virtual ~CEnemyBase() override;

	virtual HRESULT Init() override;
	virtual void Uninit() override;
	virtual void Update() override;
	virtual void Draw() override;
	virtual bool IsUnused() override;
	virtual void EnemyMove();
	virtual void EnemyRot();
	virtual void EnemyEffect();

	virtual bool Collision(D3DXVECTOR3 pos, float radius) override;

	void Damage(const int nDamage) { m_nLife -= nDamage; }
	bool CalculatingUpToNextMovePoint(void);
	void SetID(int nId) { m_nId = nId; }
	void SetEnemyType(EnemyType Type);
	void SetBulletText(int nTextIndex) { m_nBulletTextIndex = nTextIndex; }
	int GetBulletText() { return m_nBulletTextIndex; }
	void SetEnemyAddPos(D3DXVECTOR3 addpos) { m_AddPos = addpos; }
	void SetEnemyMove(float fMove) { m_fMove = fMove; }
	float GetEnemyMove() { return m_fMove; }
	bool GetDied() { return m_bDied; }
	void DiedEnemy() { m_bDied = true; }
	EnemyType GetEnemyType() { return m_EnemyType; }

	// アンカーポイントデータなどの設定
	void SetEnemyData(SEnemyData AnchorData) { m_AnchorData = AnchorData; }
	//攻撃処理
	virtual void EnemyAttack();

	virtual bool EnemyBossEffect() { return true; }

protected:
	SEnemyData m_AnchorData;// アンカーポイントデータなどの情報(これは本物のコピーなので破棄禁止)
	int m_nBulletCoolTime;
	int m_nLife;
	int m_nId;
private:
	bool m_bDied;
	int m_nBulletTextIndex;
	float m_fMove;
	D3DXVECTOR3 m_AddPos;
	EnemyType m_EnemyType;
};

#endif