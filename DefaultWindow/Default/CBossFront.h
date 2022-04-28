#pragma once
#include "Obj.h"
class CBossFront :
    public CObj
{
public:
	 CBossFront();
	virtual ~CBossFront();

	virtual		void	Initialize(void);
	virtual		int		Update(void);
	virtual		void	Late_Update(void);
	virtual		void	Render(HDC hDC);
	virtual		void	Release(void);
	bool		Dead();
private:
	POINT		m_tPie;			//중간 반원
	POINT		m_tPosin;
	DWORD		m_BossTime;
	//RECT		m_PosinRect;
	/*typedef list<CObj*>		BULLETLIST;
	BULLETLIST* m_pBullet;*/
	int m_Hp;
	int m_fDiagonal;
};

