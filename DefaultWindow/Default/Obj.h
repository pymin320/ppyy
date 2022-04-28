#pragma once

#include "Include.h"

class CObj
{
public:
	CObj();
	virtual ~CObj();

public:
	void		Set_Pos(float _fX, float _fY)
	{
		m_tInfo.fX = _fX;
		m_tInfo.fY = _fY;
	}
	void		Set_Dir(DIRECTION eDir) { m_eDir = eDir; }
	void		Set_Dead() { m_bDead = true; }
	void		Set_Angle(float _fAngle) { m_fAngle = _fAngle; }
	void		Set_Speed(float _fSpeed) { m_fSpeed = _fSpeed; }
	void		Set_Target(CObj* _pTarget) { m_pTarget = _pTarget; }


	const INFO&		Get_Info(void) const { return m_tInfo; }
	const RECT&		Get_Rect(void) const { return m_tRect; }
	void Side(string _Side) { m_Side = _Side; }

public:
	virtual		void	Initialize(void)	PURE;
	virtual		int		Update(void)		PURE;
	virtual		void	Late_Update(void)	PURE;
	virtual		void	Render(HDC hDC)		PURE;
	virtual		void	Release(void)		PURE;
	
	virtual		void	OnTriggerEnter(CObj* _Object) {};
	const string	Get_Side(void) const { return m_Side; }
	void SetColliderList(list<CObj*>* _ColList) { m_ColList = _ColList; }
protected:
	void		Update_Rect(void);
	
protected:
	INFO		m_tInfo;
	RECT		m_tRect;
	string		m_Side;

	float		m_fSpeed;
	float		m_ySpeed;
	float		m_fAngle;
	list<CObj*>* m_ColList;

	DIRECTION	m_eDir;
	bool		m_bDead;

	CObj* m_pTarget;
	RECT		m_ColliRect{};
	//POINT		m_Posin;
};

