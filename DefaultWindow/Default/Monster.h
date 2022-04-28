#pragma once
#include "Obj.h"
//hong modify
#include "CPattern.h" 

class CMonster :public CObj
{
public:

	CMonster();
	CMonster(MOBTYPE eType );
	virtual~CMonster();

public:

	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
	virtual void OnTriggerEnter(CObj* _Object) override;
public:
	void SetBulletList(list<CObj*>* _pBullet);
	void SetItemList(list<CObj*>* _pItem);	//서진 추가

// 서진 추가
public :
	int	Item_Percent();
	void CreateItem();
private:
	MOBTYPE		m_eType;
	CPattern* m_pPattern;	
	list<CObj*>* m_pItemList;
	POINT m_Posin;
	POINT m_Posin2;		//추격몬스터포신
	float m_fDiagonal;
	float m_TempAngle;
	int m_iPatternNum;
};

