#pragma once
#include "Bullet.h"

class CPattern
{
public:
	CPattern();
	~CPattern();
public:
	void Initialize();
	void Attack(POINT& _Posin, float _fAngle);
public:
	void Set_BulletList(list<CObj*>* pBullet);
	void Set_Angle(float &_fAngle) { m_fAngle = _fAngle; }
	void Update(POINT& _Posin, int i = 1);
private:
	list<CObj*>* m_pBullet;
	DWORD m_Time = GetTickCount();
	DWORD m_DelayTime;

	DWORD m_tempTIme;
	float m_fAngle;
	bool m_bIsEnd = true;//패턴이 끝낫냐
	int m_tempCount = 0;
};

