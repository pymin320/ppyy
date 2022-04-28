#pragma once
#include "Obj.h"
class CBullet :
	public CObj
{
public:
	CBullet();
	virtual ~CBullet();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;

	virtual		void	Late_Update(void);
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
	virtual void OnTriggerEnter(CObj* _Object) override;
public:
	void SetDirection(const POINT& _direction);//방향설정
	void SetSpeed(float _speed) { m_fSpeed = _speed; }


private :
	POINT m_Direction;
};

