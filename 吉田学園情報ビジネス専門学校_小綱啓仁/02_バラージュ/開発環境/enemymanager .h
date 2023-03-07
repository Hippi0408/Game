//=============================================================================
//
// enemymanager .h
// Author : koduna hirohito
//
//=============================================================================
#ifndef _ENEMY_MANAGER_H_			//このマクロ定義がされなかったら
#define _ENEMY_MANAGER_H_			//2重インクルード防止のマクロ定義

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "main.h"
#include "enemydata.h"
//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CEnemyBase;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CEnemyManager
{
private:
	// エネミーの最大数
	static const int ENEMY_MAX = 64;

	// エネミーの動きの見本の最大数
	static const int ENEMY_MOVE_SOURCE_MAX = 30;

	// エネミーグループの最大数
	static const int ENEMY_GROUP_MAX = 20;

	//ゲーム開始時、最初のグループが出るまでの間
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
	
	//グループが出るまでのインターバル
	int m_nInterval;

	//ゲーム上で生きているエネミーの数
	int m_nAliveEnemyCnt;

	//エネミーグループ情報
	int m_nGroupNum = 0;				//現在生成中の敵グループの数
	int m_nGroupMax;					//登録敵グループの数
	SEnemyGroupData m_GroupData[ENEMY_GROUP_MAX];		//グループの全データ

	int m_nEnemyMoveTypeMax; //エネミーの登録した動きの数
	SEnemyData m_EnemyMoveType[ENEMY_MOVE_SOURCE_MAX];	//エネミーの動きの元
};

#endif