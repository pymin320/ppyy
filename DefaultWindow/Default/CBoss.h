#pragma once
#include "Obj.h"
#include "Bullet.h"
#include "CBossFront.h"
#include "AbstractFactory.h"
#include "CPattern.h" 


class CBoss :
    public CObj
{
public:
	CBoss();
	virtual ~CBoss();

	virtual		void	Initialize(void);
	virtual		int		Update(void);
	virtual		void	Late_Update(void);
	virtual		void	Render(HDC hDC);
	virtual		void	Release(void);
	CObj* Get_BossList() { return m_pBossFront; }

	void	Set_BossList(list<CObj*>* pBoss) { m_pBossList = pBoss; }


	void SetBulletList(list<CObj*>* _pBullet);

private:
	POINT		m_tPosin;		//������ ����
	RECT		m_pRect;
	POINT		m_tPosin2;		//���� ����
	RECT		m_pRect2;

	POINT		m_tPie;			//�߰� �ݿ�
	RECT		m_pRect3;

	DWORD		m_BossTime;
	CObj*		m_pBossFront;
	list<CObj*>* m_pBossList;

	typedef list<CObj*>		BULLETLIST;
	BULLETLIST* m_pBullet;

	int m_Hp;
};

