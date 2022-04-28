#pragma once
#include "Bullet.h"
class CBulletBomb : public CObj
{
//현재 포신에서 y축 +n만큼 이동후에 360도방향으로 총알이 발사되는클래스
public:
	CBulletBomb();
	virtual ~CBulletBomb();
public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
public:
	void SetBulletList(list<CObj*>* _BulletList)
	{
		m_BulletList = _BulletList;
	}
private:
	DWORD m_BombTimer = 1000;
	DWORD m_Time = GetTickCount();
	list<CObj*>* m_BulletList;
};

